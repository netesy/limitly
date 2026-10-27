// Private standalone-AOT ownership helpers. No public object/header fields.
#include "memory.hh"
#include "region_instances.hh"
#include "reference_flags.hh"
#include "aot_value_kind.hh"
#include "numeric_conversion.hh"
#include "numeric_semantics.hh"
#include "atomic_field.hh"
#include "../runtime/hash_engine.hh"
#include "../runtime/os_info.hh"
#include "aot_ffi_values.hh"
#if !defined(__wasi__)
#include "../runtime/software_graphics.hh"
#endif
#include <optional>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <map>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <functional>
#if defined(_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <windows.h>
#include <tlhelp32.h>
#endif

namespace {
using Word = uint64_t;
constexpr Word object_kind = static_cast<Word>(LM::Memory::AOTValueKind::Object);
constexpr Word boolean_kind = static_cast<Word>(LM::Memory::AOTValueKind::Boolean);

// Standalone-AOT stdout writer. The self-contained PE entry point (_start) calls
// main directly and never runs the C-runtime startup, so on Windows the UCRT
// `stdout` FILE* is left NULL and std::fwrite silently writes nothing. Writing
// through the OS console handle keeps print/output working without depending on
// CRT stdio initialization. POSIX keeps the normal buffered stream.
void lymar_stdout_write(const void* data, size_t len) {
    if (!data || len == 0) return;
#if defined(_WIN32)
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!handle || handle == INVALID_HANDLE_VALUE) return;
    const char* bytes = static_cast<const char*>(data);
    size_t offset = 0;
    while (offset < len) {
        DWORD chunk = static_cast<DWORD>(len - offset);
        DWORD written = 0;
        if (!WriteFile(handle, bytes + offset, chunk, &written, nullptr) || written == 0) break;
        offset += written;
    }
#else
    std::fwrite(data, 1, len, stdout);
    std::fflush(stdout);
#endif
}
#if !defined(__wasi__)
struct GraphicsValue {Word word,kind;};
struct GraphicsBase {
    virtual ~GraphicsBase()=default;
    virtual LM::Backend::VM::ResourceType getType() const=0;
    virtual GraphicsValue call(LM::Backend::VM::ResourceOperation,const std::vector<GraphicsValue>&,void*)=0;
};
struct NativeGraphicsAccess {
    using Base=GraphicsBase; using Value=GraphicsValue; using List=Word;
    static Value boolean(bool value) {return {value?Word(1):Word(0),boolean_kind};}
    static Value nil() {return {2,object_kind};}
    static void* list(Value value);
    static int64_t integer(Value value) {return static_cast<int64_t>(lymar_aot_to_integer(value.word,value.kind));}
    static double floating(Value value) {return lymar_aot_to_float(value.word,value.kind);}
    static const char* string(Value value);
    static size_t length(List* value) {return lymar_aot_ffi_list_size(reinterpret_cast<Word>(value));}
    static Value item(List* value,size_t index) {
        auto pointer=reinterpret_cast<Word>(value);
        return {lymar_aot_ffi_list_item(pointer,index),lymar_aot_ffi_list_kind(pointer,index)};
    }
    static List* new_list();
    static void append(List*,Value);
    static Value pointer(List* value) {return {reinterpret_cast<Word>(value),object_kind};}
    static Value number(int64_t value) {return {static_cast<Word>(value),0};}
    static Value make_integer(int64_t value) {return number(value);}
};
using NativeGraphics=LM::Runtime::SoftwareGraphicsResource<NativeGraphicsAccess>;
#endif
struct Allocation {
    size_t size;
    Word owner;
    std::unordered_map<size_t, Word> edges;
    void (*finalizer)(Word) = nullptr;
    bool finalized = false;
    bool float_box = false;
    bool raw_memory = false;
    bool dictionary = false;
};
struct Region {
    Word parent;
    Word lexical;
    size_t depth;
    std::unordered_set<Word> members;
};
struct Files {
    uint64_t next = 2;
    std::unordered_map<uint64_t, FILE*> handles;
    // Stateless service handles (ResourceType::OS, ResourceType::PROCESS) mapped
    // to their resource type. They own nothing, so only the kind is recorded.
    std::unordered_map<uint64_t, uint64_t> services;
    std::map<Word,LM::Runtime::HashEngine> hashes;
    std::map<Word, std::pair<void*, size_t>> mems;
#if !defined(__wasi__)
    std::map<Word,std::unique_ptr<NativeGraphics>> graphics;
#endif
    // Release OS-facing resources held by the file/service tables. Driven
    // explicitly from SharedHeap::shutdown() rather than a destructor because
    // the SharedHeap singleton is intentionally process-lifetime (leaked) so it
    // outlives every thread_local Heap whose exit-time teardown still needs it.
    void close() {
        for (auto [id, file] : handles) if (file) std::fclose(file);
        for (auto [id, buf] : mems) if (buf.first) std::free(buf.first);
    }
};
// Shared metadata is synchronized; invocation state and the active region are
// thread-local. Region identities remain unique across recursive workers.
struct ConcurrentRegions : LM::Memory::RegionInstances<Region> {
    ConcurrentRegions() : RegionInstances(Region{0,0,0,{}}) {}
    void erase(Word id) {
        auto position = std::lower_bound(entries.begin(), entries.end(), id,
            [](const auto& entry, Word value) { return entry.first < value; });
        if (position == entries.end() || position->first != id) throw std::runtime_error("Inactive region retirement");
        entries.erase(position);
    }
};
struct ReferenceOwner { std::thread::id thread; Word region; };
struct SchedulerConfiguration { Word cores, timeout, config; };
struct SharedHeap {
    std::recursive_mutex mutex;
    std::thread::id owner = std::this_thread::get_id();
    LM::Memory::DefaultAllocator allocator;
    LM::Memory::LifetimeRegistry lifetimes;
    Word next = 1;
    std::unordered_map<Word, Allocation> allocations;
    std::unordered_map<Word, std::vector<Word>> page_map;
    ConcurrentRegions regions;
    // Ordered map: value-kind shadow needs range queries (forget_kinds, copy
    // snapshot) which are O(log n + k) via lower_bound. unordered_map forced
    // full O(n) scans and was more fragile under memory corruption (a corrupted
    // bucket_count turned its internal hash % bucket_count into a div-by-zero).
    std::map<Word,Word> shadow;
    std::map<Word,ReferenceOwner> reference_owners;
    Files files;
    std::map<Word,SchedulerConfiguration> schedulers;
    std::unordered_set<Word> closed_channels;
    std::condition_variable_any work_available;
    // Deterministic exit teardown, run once on the owner thread from ~Heap after
    // every region has unwound. Because the singleton is leaked (see
    // shared_heap()), no destructor fires at process exit, so file streams and
    // native graphics are released here instead.
    void shutdown() {
        files.close();
#if !defined(__wasi__)
        files.graphics.clear();
#endif
    }
};
// Deliberately leaked process-lifetime singleton. The per-thread Heap's
// exit-time destructor (~Heap) unwinds still-open regions and finalizes
// globals through these tables (allocations, regions, allocator). A
// function-local static would be destroyed during process exit BEFORE the
// thread_local ~Heap runs, leaving ~Heap reading a freed ConcurrentRegions --
// a use-after-free that surfaced as std::out_of_range("Inactive region
// identity") at exit for every AOT program. The OS reclaims this fixed-size
// control block at termination.
#if defined(_WIN32)
// TEMP DIAGNOSTIC (trait-list AV hunt): watcher-child mode. Self-attach
// DebugActiveProcess is policy-blocked (ERROR_PRIVILEGE_NOT_HELD), so a child
// process (same exe, LYMAR_PROBE_WATCH=<parent pid>:<parent slot addr>) runs a
// debug loop installing a hardware write-watchpoint on the parent's leaked
// SharedHeap* singleton slot, and blocks in a static ctor so parent main never
// runs in the child.
static const bool g_probe_watcher_mode = [] {
    const char* v = std::getenv("LYMAR_PROBE_WATCH");
    return v && *v;
}();
static unsigned long long g_probe_slot = 0;
static const char* probe_env_value(const char* key) {
    char buf[512];
    const DWORD n = GetEnvironmentVariableA(key, buf, sizeof(buf));
    if (!n || n >= sizeof(buf)) return nullptr;
    buf[n] = 0;
    // Duplicate through malloc: returned pointer must outlive this call.
    char* out = (char*)std::malloc(n + 1);
    if (out) std::memcpy(out, buf, n + 1);
    return out;
}
static unsigned long long probe_parent_slot_from_env() {
    const char* v = probe_env_value("LYMAR_PROBE_WATCH");
    if (!v) return 0;
    // Some CRT paths return "KEY=VALUE"; strip a leading key if present.
    if (const char* eq = strstr(v, "LYMAR_PROBE_WATCH=")) v = eq + 16;
    const char* colon = std::strchr(v, ':');
    if (!colon) return 0;
    ++colon;
    unsigned long long slot = 0;
    for (; *colon >= '0' && *colon <= '9'; ++colon) slot = slot * 10 + (*colon - '0');
    return slot;
}
static unsigned long long probe_parent_pid_from_env() {
    const char* v = probe_env_value("LYMAR_PROBE_WATCH");
    if (!v) return 0;
    if (const char* eq = strstr(v, "LYMAR_PROBE_WATCH=")) v = eq + 16;
    // Manual decimal parse (bypasses any CRT strtoul weirdness).
    unsigned long long pid = 0;
    for (; *v >= '0' && *v <= '9'; ++v) pid = pid * 10 + (*v - '0');
    return pid;
}
#endif
static unsigned long long probe_state_slot = 0; // address of shared_heap()'s state ptr (captured pre-guard)
SharedHeap& shared_heap() { static SharedHeap* state = new SharedHeap();
#if defined(_WIN32)
    if (!g_probe_watcher_mode && !probe_state_slot) probe_state_slot = (unsigned long long)(uintptr_t)&state;
#endif
    return *state; }
#if defined(_WIN32)
// TEMP DIAGNOSTIC (trait-list AV hunt): first-fault dump + post-init page
// guard on the .data page holding shared_heap()'s state pointer. ALL mutable
// probe state lives in a heap-allocated ctx and stack buffers because this
// TU's statics may share the guarded page (a handler write there is fatal).
struct ProbeCtx {
    volatile unsigned long long reports, allocs, arm_at, guard_page;
};
static ProbeCtx* probe_ctx = nullptr;
static void probe_emit(const char* text) {
    DWORD written;
    WriteFile(GetStdHandle(STD_ERROR_HANDLE), text, (DWORD)lstrlenA(text), &written, nullptr);
}
static LONG WINAPI probe_exception_filter(PEXCEPTION_POINTERS e) {
    if (!probe_ctx) return EXCEPTION_CONTINUE_SEARCH;
    if (++probe_ctx->reports > 12) return EXCEPTION_CONTINUE_SEARCH;
    char line[512];
    auto code = (unsigned long long)e->ExceptionRecord->ExceptionCode;
    auto rip = (unsigned long long)(uintptr_t)e->ExceptionRecord->ExceptionAddress;
    auto addr = (unsigned long long)(uintptr_t)e->ExceptionRecord->ExceptionInformation[1];
    auto access = (unsigned long long)e->ExceptionRecord->ExceptionInformation[0];
    HMODULE fault_mod = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR)(LPCVOID)(uintptr_t)rip, &fault_mod);
    char modname[260] = "?";
    if (fault_mod) GetModuleFileNameA(fault_mod, modname, 259);
    std::snprintf(line, sizeof(line),
        "[PROBE] FAULT code=0x%llx access=%llu rip=0x%llx fault=0x%llx mod=%s mod_rva=0x%llx\n",
        code, access, rip, addr, modname, fault_mod ? rip - (unsigned long long)(uintptr_t)fault_mod : 0ull);
    probe_emit(line);
    if (probe_state_slot) {
        probe_emit("[PROBE] data:");
        for (int i = -3; i <= 3; ++i) {
            unsigned long long value = 0; SIZE_T got = 0;
            if (ReadProcessMemory(GetCurrentProcess(), (LPCVOID)(uintptr_t)(probe_state_slot + i * 8), &value, 8, &got) && got == 8)
                std::snprintf(line, sizeof(line), " q=0x%llx", value);
            else std::snprintf(line, sizeof(line), " q=?");
            probe_emit(line);
        }
        probe_emit("\n");
    }
    auto rsp = (unsigned long long)(uintptr_t)e->ContextRecord->Rsp;
    unsigned printed = 0;
    for (unsigned slot = 0; slot < 512 && printed < 24; ++slot) {
        unsigned long long value = 0;
        if (!ReadProcessMemory(GetCurrentProcess(), (LPCVOID)(uintptr_t)(rsp + slot * 8), &value, 8, nullptr) || !value) continue;
        HMODULE mod = nullptr;
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCWSTR)(LPCVOID)(uintptr_t)value, &mod) || !mod) continue;
        char name[260] = "?";
        GetModuleFileNameA(mod, name, 259);
        auto* base = (unsigned char*)(uintptr_t)mod;
        auto size = ((PIMAGE_NT_HEADERS)(base + ((PIMAGE_DOS_HEADER)base)->e_lfanew))->OptionalHeader.SizeOfImage;
        auto rva = value - (unsigned long long)(uintptr_t)mod;
        if (rva >= size) continue; // data pointer inside module, not code range
        std::snprintf(line, sizeof(line), "[PROBE] st[%u]=%s+0x%llx\n",
            slot, strrchr(name, '\\') ? strrchr(name, '\\') + 1 : name, rva);
        probe_emit(line);
        ++printed;
    }
    // Write trips are no longer page-trapped (hardware watchpoints below).
    TerminateProcess(GetCurrentProcess(), 4242);
    return EXCEPTION_CONTINUE_SEARCH;
}
static struct ProbeExceptionInstall { ProbeExceptionInstall() {
    probe_ctx = (ProbeCtx*)std::calloc(1, sizeof(ProbeCtx));
    probe_ctx->arm_at = 2000; // arm once the runtime is fully initialized
    AddVectoredExceptionHandler(1, probe_exception_filter);
    probe_emit("[PROBE] handler installed\n");
} } probe_exception_install;
// Watcher: a hardware write-watchpoint on the exact 8 bytes of the parent's
// shared_heap() state pointer. Reports the faulting RIP of every write.
// Arm Dr0 write-breakpoint on one (debugger-suspended) thread.
static void probe_arm_thread(DWORD pid, DWORD tid, unsigned long long slot, unsigned& armed_threads) {
    if (!slot || armed_threads >= 64) return;
    HANDLE t = OpenThread(THREAD_ALL_ACCESS, FALSE, tid);
    if (!t) return;
    CONTEXT ctx; ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (GetThreadContext(t, &ctx)) {
        ctx.Dr0 = (DWORD64)slot;
        ctx.Dr6 = 0; ctx.Dr7 = 0;
        ctx.Dr7 |= 0x1ull;          // L0 local
        ctx.Dr7 &= ~(3ull << 16);    // RW0 = 00 -> write access
        ctx.Dr7 |= 3ull << 18;       // LEN0 = 8 bytes
        SetThreadContext(t, &ctx);
        ++armed_threads;
    }
    CloseHandle(t);
}
static void probe_debug_loop(DWORD target_pid, unsigned long long slot) {
    if (!DebugActiveProcess(target_pid)) {
        char line[128];
        snprintf(line, sizeof(line), "[PROBE] attach pid=%lu failed err=%lu\n", target_pid, GetLastError());
        probe_emit(line);
        return;
    }
    DebugSetProcessKillOnExit(FALSE);
    DEBUG_EVENT ev;
    unsigned hits = 0, armed_threads = 0;
    // Attach does not deliver BREAKPOINT for already-existing threads; enumerate
    // and arm them while the initial break suspends the target.
    {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, target_pid);
        if (snap != INVALID_HANDLE_VALUE) {
            THREADENTRY32 te; te.dwSize = sizeof(te);
            if (Thread32First(snap, &te)) {
                do if (te.th32OwnerProcessID == target_pid)
                    probe_arm_thread(target_pid, te.th32ThreadID, slot, armed_threads);
                while (Thread32Next(snap, &te));
            }
            CloseHandle(snap);
        }
    }
    char line[256];
    snprintf(line, sizeof(line), "[PROBE] attached armed=%u slot=0x%llx\n", armed_threads, slot);
    probe_emit(line);
    while (WaitForDebugEvent(&ev, INFINITE)) {
        DWORD status = DBG_CONTINUE;
        if (ev.dwDebugEventCode == CREATE_THREAD_DEBUG_EVENT) {
            snprintf(line, sizeof(line), "[PROBE] new-thread %lu\n", ev.dwThreadId);
            probe_emit(line);
        }
        if (ev.dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
            auto& rec = ev.u.Exception.ExceptionRecord;
            if (rec.ExceptionCode == EXCEPTION_BREAKPOINT) {
                // Thread is suspended here: install Dr0 write-breakpoint.
                probe_arm_thread(target_pid, ev.dwThreadId, slot, armed_threads);
            } else if (rec.ExceptionCode == EXCEPTION_SINGLE_STEP && hits < 12) {
                ++hits;
                HMODULE mod = nullptr;
                GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                    (LPCWSTR)(LPCVOID)(uintptr_t)rec.ExceptionAddress, &mod);
                char name[260] = "?";
                if (mod) GetModuleFileNameA(mod, name, 259);
                snprintf(line, sizeof(line), "[PROBE] WRITE-HIT rip=%s+0x%llx thread=%lu\n",
                    strrchr(name, '\\') ? strrchr(name, '\\') + 1 : name, mod ? (unsigned long long)((char*)rec.ExceptionAddress - (char*)mod) : 0ull,
                    ev.dwThreadId);
                probe_emit(line);
            } else status = DBG_EXCEPTION_NOT_HANDLED;
            if (rec.ExceptionCode != EXCEPTION_BREAKPOINT && rec.ExceptionCode != EXCEPTION_SINGLE_STEP && hits < 12) {
                snprintf(line, sizeof(line), "[PROBE] exc 0x%lx rip=%p first=%lu\n", rec.ExceptionCode,
                    rec.ExceptionAddress, ev.u.Exception.dwFirstChance);
                probe_emit(line);
            }
        } else if (ev.dwDebugEventCode == OUTPUT_DEBUG_STRING_EVENT || ev.dwDebugEventCode == RIP_EVENT)
            status = DBG_EXCEPTION_NOT_HANDLED;
        ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, status);
        if (ev.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
            snprintf(line, sizeof(line), "[PROBE] target exited code=0x%lx\n", ev.u.ExitProcess.dwExitCode);
            probe_emit(line);
            break;
        }
    }
    snprintf(line, sizeof(line), "[PROBE] loop done hits=%u\n", hits);
    probe_emit(line);
}
// Watcher child: static ctor blocks here, so the exe's main never runs and the
// child exists purely to pump debug events for its parent. stderr is inherited.
static struct ProbeWatcherInit {
    ProbeWatcherInit() {
        if (!g_probe_watcher_mode) return;
        const char* v = probe_env_value("LYMAR_PROBE_WATCH");
        unsigned long long parent = 0, slot = 0;
        if (v) {
            while (*v && (*v < '0' || *v > '9')) ++v;   // tolerate "KEY=" prefix
            for (; *v >= '0' && *v <= '9'; ++v) parent = parent * 10 + (*v - '0');
            if (*v == ':') { ++v; for (; *v >= '0' && *v <= '9'; ++v) slot = slot * 10 + (*v - '0'); }
        }
        char line[256];
        snprintf(line, sizeof(line), "[PROBE] watcher up parent=%llu slot=0x%llx\n", parent, slot);
        probe_emit(line);
        if (parent && slot) probe_debug_loop((DWORD)parent, slot);
        ExitProcess(0);
    }
} probe_watcher_init;
static void probe_arm_guard() {
    if (!probe_ctx || !probe_state_slot) return;
    // Self-contained AOT exes skip CRT startup, so GetModuleFileName* fails
    // (PEB ProcessParameters NULL). Read the image path from the PEB loader
    // list instead.
    char exe_path[1024] = "?";
    {
        HMODULE main_mod = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCWSTR)(LPCVOID)(uintptr_t)&probe_state_slot, &main_mod);
        if (main_mod) {
            wchar_t wpath[1024];
            const DWORD wn = GetModuleFileNameW(main_mod, wpath, 1023);
            if (wn) {
                int need = WideCharToMultiByte(CP_UTF8, 0, wpath, (int)wn, exe_path, sizeof(exe_path) - 1, nullptr, nullptr);
                if (need > 0) exe_path[need] = 0;
            }
        }
    }
    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "\"%s\"", exe_path);
    char envv[96];
    snprintf(envv, sizeof(envv), "LYMAR_PROBE_WATCH=%lu:%llu", GetCurrentProcessId(), probe_state_slot);
    SetEnvironmentVariableA("LYMAR_PROBE_WATCH", envv);
    STARTUPINFOA si; PROCESS_INFORMATION pi;
    std::memset(&si, 0, sizeof(si)); si.cb = sizeof(si);
    HANDLE err = GetStdHandle(STD_ERROR_HANDLE);
    SetHandleInformation(err, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    si.hStdError = err; si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.dwFlags = STARTF_USESTDHANDLES;
    if (CreateProcessA(nullptr, cmd, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
        char line[128];
        snprintf(line, sizeof(line), "[PROBE] watcher spawned pid=%lu\n", pi.dwProcessId);
        probe_emit(line);
        CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
    } else {
        char line[256];
        snprintf(line, sizeof(line), "[PROBE] spawn failed err=%lu cmd=[%s]\n", GetLastError(), cmd);
        probe_emit(line);
        std::memset(&si, 0, sizeof(si)); si.cb = sizeof(si);
        if (CreateProcessA(nullptr, cmd, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi)) {
            snprintf(line, sizeof(line), "[PROBE] watcher spawned(new console) pid=%lu\n", pi.dwProcessId);
            probe_emit(line);
            CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
        } else {
            snprintf(line, sizeof(line), "[PROBE] spawn2 failed err=%lu\n", GetLastError());
            probe_emit(line);
        }
    }
}
#else
[[maybe_unused]] static void probe_arm_guard() {
    static unsigned long long probe_state_slot_guard_placeholder = 0;
    (void)probe_state_slot_guard_placeholder;
}
#endif
thread_local unsigned runtime_lock_depth = 0;
struct RuntimeGuard {
    RuntimeGuard() { shared_heap().mutex.lock(); ++runtime_lock_depth; }
    ~RuntimeGuard() { --runtime_lock_depth; shared_heap().mutex.unlock(); }
};
struct RuntimeSuspend {
    unsigned depth = runtime_lock_depth;
    RuntimeSuspend() { while(runtime_lock_depth) { --runtime_lock_depth; shared_heap().mutex.unlock(); } }
    ~RuntimeSuspend() { while(runtime_lock_depth < depth) {shared_heap().mutex.lock(); ++runtime_lock_depth;} }
};
struct Heap {
    LM::Memory::DefaultAllocator& allocator = shared_heap().allocator;
    LM::Memory::LifetimeRegistry& lifetimes = shared_heap().lifetimes;
    struct Invocation {
        Word region = 0;
        std::vector<Word> args;
        std::unordered_set<Word> slots;
        std::vector<std::pair<Word, Word>> staged_params;
    };
    Word active = 0, base = 0;
    Word& next = shared_heap().next;
    bool worker = false;
    char worker_error[1024] = {};
    std::atomic<bool>* cancellation = nullptr;
    std::chrono::steady_clock::time_point deadline;
    bool timed = false, timed_out = false;
    std::unordered_map<Word, Allocation>& allocations = shared_heap().allocations;
    std::unordered_map<Word, std::vector<Word>>& page_map = shared_heap().page_map;
    ConcurrentRegions& regions = shared_heap().regions;
    std::map<Word, Word>& shadow = shared_heap().shadow;
    std::vector<Invocation> invocations;
    std::vector<Word> pending_args;
    Word return_pointer = 0;
    Files& files = shared_heap().files;

    void forget_kinds(Word address, Word size, bool overlapping = false) {
        if (!size) return;
        // An entry at key p spans [p, p+8); it overlaps the target range when
        // p + 8 > address, i.e. p >= address - 7. Only widen the lower bound
        // when the caller explicitly wants partial-overlap removal.
        Word lo = (overlapping && address >= sizeof(Word) - 1) ? address - (sizeof(Word) - 1) : address;
        Word hi = address + size;
        auto it = shadow.lower_bound(lo);
        while (it != shadow.end() && it->first < hi)
            it = shadow.erase(it);
    }
    auto containing(Word address) {
        auto exact = allocations.find(address);
        if (exact != allocations.end()) return exact;
        Word page = address >> 12;
        auto page_it = page_map.find(page);
        if (page_it != page_map.end()) {
            for (Word start : page_it->second) {
                auto alloc_it = allocations.find(start);
                if (alloc_it != allocations.end() && address >= start && address - start < alloc_it->second.size) {
                    return alloc_it;
                }
            }
        }
        return allocations.end();
    }
    void promote(Word value, Word target) {
        std::vector<Word> pending{value};
        std::unordered_set<Word> seen;
        while (!pending.empty()) {
            auto found = containing(pending.back());
            pending.pop_back();
            if (found == allocations.end() || !seen.insert(found->first).second) continue;
            auto& allocation = found->second;
            if (regions.at(allocation.owner).depth <= regions.at(target).depth) continue;
            regions.at(allocation.owner).members.erase(found->first);
            regions.at(target).members.insert(found->first);
            allocation.owner = target;
            for (auto [offset, child] : allocation.edges) pending.push_back(child);
        }
    }
    void finalize(Word pointer) {
        auto found = allocations.find(pointer);
        if (found == allocations.end() || found->second.finalized) return;
        found->second.finalized = true;
        auto callback = found->second.finalizer;
        if (callback) {
            struct RestoreWorkerState {
                Heap& heap; char error[1024]; std::atomic<bool>* cancellation; bool timed;
                explicit RestoreWorkerState(Heap& value):heap(value),cancellation(value.cancellation),timed(value.timed) {
                    std::memcpy(error,heap.worker_error,sizeof(error));heap.worker_error[0]=0;heap.cancellation=nullptr;heap.timed=false;
                }
                ~RestoreWorkerState() {
                    heap.cancellation=cancellation;heap.timed=timed;
                    if(error[0]) std::memcpy(heap.worker_error,error,sizeof(error));
                }
            } restore(*this);
            RuntimeSuspend suspend;callback(pointer);
        }
    }
    void release(Word pointer) {
        auto found = allocations.find(pointer);
        if (found == allocations.end()) throw std::runtime_error("AOT free of unowned allocation");
        regions.at(found->second.owner).members.erase(pointer);
        forget_kinds(pointer, found->second.size);
        lifetimes.revoke(pointer);
        shared_heap().schedulers.erase(pointer);
        shared_heap().closed_channels.erase(pointer);
        Word size = found->second.size;
        Word start_page = pointer >> 12;
        Word end_page = (pointer + std::max<Word>(1, size) - 1) >> 12;
        for (Word page = start_page; page <= end_page; ++page) {
            auto page_it = page_map.find(page);
            if (page_it != page_map.end()) {
                std::erase(page_it->second, pointer);
                if (page_it->second.empty()) page_map.erase(page_it);
            }
        }
        allocations.erase(found);
        allocator.deallocate(reinterpret_cast<void*>(pointer));
    }
    void cleanup(Word region) {
        // Fields and children remain alive throughout destructor execution.
        for (;;) {
            std::vector<Word> objects;
            for (auto object : regions.at(region).members)
                if (!allocations.at(object).finalized) objects.push_back(object);
            if (objects.empty()) break;
            for (auto object : objects) finalize(object);
        }
        for (auto position=shared_heap().reference_owners.begin(); position!=shared_heap().reference_owners.end();)
            if(position->second.region==region) position=shared_heap().reference_owners.erase(position); else ++position;
        lifetimes.end_region(region);
        while (!regions.at(region).members.empty()) release(*regions.at(region).members.begin());
    }
    ~Heap() {
        RuntimeGuard lock;
        try {
            while (active != base) {
                auto parent = regions.at(active).parent;
                cleanup(active);
                regions.erase(active);
                active = parent;
            }
            if (std::this_thread::get_id() == shared_heap().owner) {
                cleanup(0);
                // Finalize globals first (cleanup above), then release the
                // process-level file/graphics resources the leaked singleton
                // would otherwise never free via a destructor.
                shared_heap().shutdown();
            }
        } catch (...) { std::terminate(); }
    }
};
Heap& heap() { static thread_local Heap value; return value; }
Files& files() { return heap().files; }
Word read_word(Word address, size_t offset = 0) {
    Word value;
    std::memcpy(&value, reinterpret_cast<void*>(address + offset), sizeof(value));
    return value;
}
const char* string_data(Word value) {
    auto found=heap().allocations.find(value);
    if(found==heap().allocations.end() || found->second.raw_memory || found->second.dictionary || found->second.size<25 || (read_word(value)&0xffffffff)!=11 || read_word(value,8)>found->second.size-25) return nullptr;
    return reinterpret_cast<const char*>(value + 24);
}
std::optional<__int128> integer_number(Word value, Word kind) {
    if (!kind) return static_cast<int64_t>(value);
    if (kind != object_kind || value <= 4096) return {};
    auto found=heap().allocations.find(value);
    if(found==heap().allocations.end() || found->second.raw_memory || found->second.dictionary || found->second.size<16) return {};
    auto type = read_word(value) & 0xffffffff;
    if ((type==7 || type==8) && found->second.size<32) return {};
    if (type == 5) return static_cast<int64_t>(read_word(value, 8));
    if (type == 6) return read_word(value, 8);
    if (type == 7 || type == 8) {
        __int128 number; std::memcpy(&number, reinterpret_cast<void*>(value + 16), sizeof(number)); return number;
    }
    return {};
}
std::string integer_text(__int128 number) {
    bool negative = number < 0;
    auto magnitude = negative ? 0 - static_cast<unsigned __int128>(number) : static_cast<unsigned __int128>(number);
    std::string text;
    do { text.push_back('0' + magnitude % 10); magnitude /= 10; } while (magnitude);
    if (negative) text.push_back('-');
    std::reverse(text.begin(), text.end()); return text;
}
}

extern "C" {
uint64_t lymar_aot_alloc(uint64_t size);
uint64_t lymar_aot_box_float(double number);
void lymar_aot_edge(uint64_t address, uint64_t child, uint64_t kind);
double lymar_aot_to_float(uint64_t value, uint64_t kind);
// Frame operations require a live, correctly shaped receiver before addressing
// its fields. This is backend-private layout validation, not frontend inference.
uint64_t lymar_aot_frame_field_address(uint64_t pointer, uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    auto frame = h.allocations.find(pointer);
    if (frame == h.allocations.end() || frame->second.size < 40 || (read_word(pointer) & 0xffffffff) != 15)
        throw std::runtime_error("Invalid or expired frame receiver");
    auto count = read_word(pointer, 24);
    if (index >= count) throw std::runtime_error("Invalid frame field index");
    auto fields = read_word(pointer, 16);
    auto array = h.allocations.find(fields);
    if (array == h.allocations.end() || count > array->second.size / sizeof(Word))
        throw std::runtime_error("Invalid frame fields allocation");
    h.return_pointer = 1;
    return fields + index * sizeof(Word);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_frame_matches(uint64_t pointer, uint64_t expected, uint64_t length) {
    RuntimeGuard guard;
    auto& h = heap();
    auto frame = h.allocations.find(pointer);
    if (frame == h.allocations.end() || frame->second.size < 40 || (read_word(pointer) & 0xffffffff) != 15)
        throw std::runtime_error("Invalid or expired method receiver");
    auto name = read_word(pointer, 8);
    auto string = h.allocations.find(name);
    if (string == h.allocations.end() || string->second.size < 24 || (read_word(name) & 0xffffffff) != 11 ||
        read_word(name, 8) > string->second.size - 24)
        throw std::runtime_error("Invalid frame name");
    return read_word(name, 8) == length && std::memcmp(reinterpret_cast<void*>(name + 24), reinterpret_cast<void*>(expected + 24), length) == 0;
}
uint64_t lymar_aot_atomic_load(uint64_t pointer, uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    auto result = LM::Memory::atomic_field_load(reinterpret_cast<Word*>(address));
    auto found = heap().shadow.find(address);
    heap().return_pointer = found == heap().shadow.end() ? 0 : found->second;
    return result;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_atomic_store(uint64_t pointer, uint64_t index, uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    // Publish ownership/kind before publishing the field value.
    std::lock_guard lock(LM::Memory::atomic_field_mutex(reinterpret_cast<void*>(address)));
    lymar_aot_edge(address, value, kind);
    std::atomic_ref<Word>(*reinterpret_cast<Word*>(address)).store(value, std::memory_order_seq_cst);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_atomic_update(uint64_t pointer, uint64_t index, uint64_t value, uint64_t kind, uint64_t subtract) {
    try {
    RuntimeGuard runtime_guard;

    auto address = lymar_aot_frame_field_address(pointer, index);
    LM::Memory::atomic_field_update(reinterpret_cast<Word*>(address), [&](Word old) {
        auto found = heap().shadow.find(address);
        Word old_kind = found == heap().shadow.end() ? 0 : found->second;
        Word result = 2, result_kind = object_kind;
        auto left = integer_number(old, old_kind), right = integer_number(value, kind);
        if (left && right) {
            __int128 number;
            if (LM::Memory::add_integer(*left, *right, number, subtract != 0)) {
                if (number >= INT64_MIN && number <= INT64_MAX) { result = static_cast<Word>(number); result_kind = 0; }
                else { result = lymar_aot_alloc(32); *reinterpret_cast<Word*>(result) = 7;
                    std::memcpy(reinterpret_cast<void*>(result + 16), &number, sizeof(number)); }
            }
        } else {
            auto is_float = [](Word word, Word mode) { return mode == object_kind && word > 4096 && (read_word(word) & 0xffffffff) == 9; };
            if ((left || is_float(old, old_kind)) && (right || is_float(value, kind))) {
                auto a = lymar_aot_to_float(old, old_kind), b = lymar_aot_to_float(value, kind);
                result = lymar_aot_box_float(subtract ? a - b : a + b);
            } else if (!subtract && old_kind == object_kind && kind == object_kind && old > 4096 && value > 4096 &&
                       (read_word(old) & 0xffffffff) == 11 && (read_word(value) & 0xffffffff) == 11) {
                auto a = read_word(old, 8), b = read_word(value, 8);
                if (b > UINT64_MAX - 25 || a > UINT64_MAX - b - 25) throw std::overflow_error("Atomic string length overflow");
                result = lymar_aot_alloc(25 + a + b);
                *reinterpret_cast<Word*>(result) = 11; *reinterpret_cast<Word*>(result + 8) = a + b;
                *reinterpret_cast<Word*>(result + 16) = a + b;
                std::memcpy(reinterpret_cast<void*>(result + 24), reinterpret_cast<void*>(old + 24), a);
                std::memcpy(reinterpret_cast<void*>(result + 24 + a), reinterpret_cast<void*>(value + 24), b);
                *reinterpret_cast<char*>(result + 24 + a + b) = 0;
            }
        }
        lymar_aot_edge(address, result, result_kind);
        return result;
    });

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_builtin_arity_error() {
    try {
    RuntimeGuard runtime_guard;
 throw std::runtime_error("Builtin argument count mismatch");
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_ref_create(uint64_t pointer, uint64_t writable) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    h.return_pointer = 0;
    if ((pointer == 0 || pointer == 2) && (writable & LM::Memory::ReferenceNullable)) return 0;
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT borrow of unowned object");
    h.lifetimes.adopt(pointer);
    h.return_pointer = 0;
    auto token = h.lifetimes.borrow(pointer, (writable & LM::Memory::ReferenceWritable) != 0, h.active);
    shared_heap().reference_owners[token] = {std::this_thread::get_id(),h.active};
    return token;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Provenance distinguishes actual nil/pointers from raw scalar words that
// happen to equal the nil representation (notably integers zero and two).
uint64_t lymar_aot_nil() {
    try {
    RuntimeGuard runtime_guard;
 return 2;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_nil(uint64_t value, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    return is_pointer == object_kind && (value == 0 || value == 2);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_object(uint64_t value, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    return is_pointer == object_kind && value != 0 && value != 2;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Erased native integers are untagged, so pointer shape cannot validate a
// string receiver. The existing kind sidecar is authoritative at this boundary.
uint64_t lymar_aot_string_receiver(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (!lymar_aot_is_object(value, kind)) return 0;
    return (read_word(value) & 0xffffffff) == 11 ? value : 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_callable_receiver(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (!lymar_aot_is_object(value, kind)) return 0;
    auto type = read_word(value) & 0xffffffff;
    if (type == 11) return value; // canonical function-name string
    auto& h = heap();
    auto tuple = h.allocations.find(value);
    if (type != 3 || tuple == h.allocations.end() || tuple->second.size < 32 || !read_word(value,16)) return 0;
    auto elements = read_word(value,8);
    auto array = h.allocations.find(elements);
    if (array == h.allocations.end() || array->second.size < 8) return 0;
    auto origin = h.shadow.find(elements);
    auto name = read_word(elements);
    if (origin == h.shadow.end() || !lymar_aot_is_object(name,origin->second) ||
        (read_word(name) & 0xffffffff) != 11) return 0;
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_string_index(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (kind == 0) return value;
    if (!lymar_aot_is_object(value, kind)) return 0;
    auto type = read_word(value) & 0xffffffff;
    if (type >= 5 && type <= 8) return read_word(value + 8);
    if (type == 9) {
        double number;
        std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
        return static_cast<uint64_t>(LM::Memory::truncate_i64(number));
    }
    return 0; // as_i64 does not parse strings or convert booleans.

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_boolean(uint64_t value) {
    try {
    RuntimeGuard runtime_guard;
 return value;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_is_print_object(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    return lymar_aot_is_object(value, kind) && (read_word(value) & 0xffffffff) != 9;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
double lymar_aot_to_float(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (auto integer = integer_number(value, kind)) return static_cast<double>(*integer);
    if (!kind) return static_cast<double>(static_cast<int64_t>(value));
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0.0;
    if ((read_word(value) & 0xffffffff) == 9) {
        double number;
        std::memcpy(&number, reinterpret_cast<void*>(value + 8), sizeof(number));
        return number;
    }
    if (auto* text = string_data(value)) { try { return std::stod(text); } catch (...) {} }
    return 0.0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0.0;
    }
}
uint64_t lymar_aot_to_integer(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (auto integer = integer_number(value, kind)) return static_cast<Word>(*integer);
    if (!kind) return value;
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0;
    if (auto* text = string_data(value)) {
        try { return static_cast<uint64_t>(std::stoll(text)); }
        catch (...) { return static_cast<unsigned char>(text[0]); }
    }
    return static_cast<uint64_t>(LM::Memory::truncate_i64(lymar_aot_to_float(value, kind)));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_to_integer(double number) {
    try {
    RuntimeGuard runtime_guard;

    return static_cast<uint64_t>(LM::Memory::truncate_i64(number));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_to_boolean(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (lymar_aot_is_nil(value, kind)) return 0;
    if (kind != object_kind) return value != 0;
    if ((read_word(value) & 0xffffffff) == 9) return lymar_aot_to_float(value, kind) != 0.0;
    return 1;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
int64_t lymar_aot_numeric_compare(uint64_t left, uint64_t right, uint64_t left_kind, uint64_t right_kind) {
    if (!left_kind && !right_kind) {
        int64_t a = static_cast<int64_t>(left), b = static_cast<int64_t>(right);
        return a < b ? -1 : a > b ? 1 : 0;
    }
    RuntimeGuard guard;
    auto classify = [&](Word value, Word kind) -> Word {
        if (kind != object_kind || lymar_aot_is_nil(value, kind)) return 0;
        auto found = heap().containing(value);
        if (found == heap().allocations.end())
            throw std::runtime_error("Invalid or expired comparison operand");
        if (found->first != value || found->second.raw_memory || found->second.dictionary) return 0;
        if (found->second.size < 8) throw std::runtime_error("Invalid comparison allocation");
        auto type = read_word(value) & 0xffffffff;
        if (type >= 5 && type <= 9 && found->second.size < (type == 7 || type == 8 ? 32 : 16))
            throw std::runtime_error("Invalid numeric allocation");
        return type;
    };
    auto ltype = classify(left, left_kind), rtype = classify(right, right_kind);
    bool lnumeric = left_kind == 0 || (ltype >= 5 && ltype <= 9);
    bool rnumeric = right_kind == 0 || (rtype >= 5 && rtype <= 9);
    if (lnumeric && rnumeric) {
        if (ltype == 9 || rtype == 9) {
            auto a = lymar_aot_to_float(left, left_kind), b = lymar_aot_to_float(right, right_kind);
            return a < b ? -1 : a > b ? 1 : 0;
        }
        auto a = *integer_number(left, left_kind), b = *integer_number(right, right_kind);
        return a < b ? -1 : a > b ? 1 : 0;
    }
    // Match the VM's tagged ordering for nonnumeric immediates. Object
    // ordering remains identity ordering, as in numeric_compare in the VM.
    auto tagged = [&](Word value, Word kind) -> Word {
        if (kind == 0) return (value << 3) | 1;
        if (kind == boolean_kind) return value ? 18 : 10;
        if (lymar_aot_is_nil(value, kind)) return 2;
        return value;
    };
    auto a = tagged(left, left_kind), b = tagged(right, right_kind);
    return a < b ? -1 : a > b ? 1 : 0;
}
void lymar_aot_print_integer(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    char text[64];
    const char* output = text;
    size_t length;
    if (lymar_aot_is_nil(value, kind)) { output = "nil"; length = 3; }
    else if (kind == boolean_kind) { output = value ? "true" : "false"; length = value ? 4 : 5; }
    else if (auto integer = integer_number(value, kind)) {
        auto number = integer_text(*integer); lymar_stdout_write(number.data(), number.size()); return;
    }
    else if (kind == object_kind && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value, kind)));
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    lymar_stdout_write(output, length);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_print_float(double value) {
    try {
    RuntimeGuard runtime_guard;

    char text[64];
    const auto length = std::snprintf(text, sizeof(text), "%.6g", value);
    lymar_stdout_write(text, static_cast<size_t>(length));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_value_equal(uint64_t left, uint64_t right, uint64_t left_kind, uint64_t right_kind) {
    try {
    RuntimeGuard runtime_guard;

    const bool left_nil = lymar_aot_is_nil(left, left_kind), right_nil = lymar_aot_is_nil(right, right_kind);
    if (left_nil || right_nil) return left_nil && right_nil;
    if (left_kind == boolean_kind || right_kind == boolean_kind)
        return left_kind == right_kind && left == right;
    if (left == right && left_kind == right_kind) return 1;
    const Word left_type = left_kind == object_kind ? read_word(left) & 0xffffffff : UINT64_MAX;
    const Word right_type = right_kind == object_kind ? read_word(right) & 0xffffffff : UINT64_MAX;
    if (auto left_integer = integer_number(left, left_kind))
        if (auto right_integer = integer_number(right, right_kind)) return *left_integer == *right_integer;
    if ((integer_number(left, left_kind) || left_type == 9) && (integer_number(right, right_kind) || right_type == 9))
        return left_type == 9 || right_type == 9
            ? lymar_aot_to_float(left, left_kind) == lymar_aot_to_float(right, right_kind) : left == right;
    if (left_type == 11 && right_type == 11) {
        auto size = read_word(left, 8);
        return size == read_word(right, 8) && std::memcmp(reinterpret_cast<void*>(left + 24), reinterpret_cast<void*>(right + 24), size) == 0;
    }
    if (!left_kind && right_type == 11)
        return read_word(right, 8) == 1 && static_cast<uint8_t>(left) == *reinterpret_cast<uint8_t*>(right + 24);
    if (!right_kind && left_type == 11)
        return read_word(left, 8) == 1 && static_cast<uint8_t>(right) == *reinterpret_cast<uint8_t*>(left + 24);
    // Preserve the existing native enum representation and payload equality.
    if (left_type == 0x454e554d && right_type == 0x454e554d)
        return read_word(left, 8) == read_word(right, 8) && read_word(left, 16) == read_word(right, 16);
    return 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_create_checked(uint64_t pointer, uint64_t mode, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    if (is_pointer != object_kind) throw std::runtime_error("Borrow requires a managed object");
    return lymar_aot_ref_create(pointer, mode);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_resolve(uint64_t token, uint64_t writable) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (writable & ~(LM::Memory::ReferenceWritable | LM::Memory::ReferenceNullable)) throw std::runtime_error("Invalid AOT reference mode");
    h.return_pointer = 1;
    if (!token && (writable & LM::Memory::ReferenceNullable)) return 2;
    if ((writable & LM::Memory::ReferenceWritable) && h.worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
        throw std::runtime_error("Worker cannot write through a captured reference");
    return h.lifetimes.resolve(token, (writable & LM::Memory::ReferenceWritable) != 0);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_ref_move(uint64_t token, uint64_t lexical, uint64_t caller) {
    try {
    RuntimeGuard runtime_guard;

    if (lexical & ~LM::Memory::ReferenceMoveMask) throw std::runtime_error("Invalid AOT reference move mode");
    auto& h = heap();
    h.return_pointer = 0;
    if (!token && (lexical & LM::Memory::ReferenceMoveNullable)) return 0;
    if (h.worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
        throw std::runtime_error("Worker cannot move a captured reference");
    lexical = static_cast<uint32_t>(lexical & LM::Memory::ReferenceRegionMask);
    auto pointer = h.lifetimes.resolve(token);
    auto target = caller;
    if (lexical) {
        target = h.active;
        while (target && h.regions.at(target).lexical != lexical) target = h.regions.at(target).parent;
        if (!target) throw std::runtime_error("AOT reference move target is not active");
    }
    if (h.regions.at(h.allocations.at(pointer).owner).depth > h.regions.at(target).depth)
        throw std::runtime_error("AOT reference promotion requires owner promotion");
    auto origin = h.lifetimes.reference_region(token);
    if (h.regions.at(origin).depth < h.regions.at(target).depth) target = origin;
    h.return_pointer = 0;
    auto owner = shared_heap().reference_owners.at(token).thread;
    auto moved = h.lifetimes.move_reference(token, target);
    shared_heap().reference_owners.erase(token);
    shared_heap().reference_owners[moved] = {owner,target};
    return moved;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_ref_release(uint64_t token) {
    try {
    RuntimeGuard runtime_guard;
 if (heap().worker && shared_heap().reference_owners.at(token).thread != std::this_thread::get_id())
     throw std::runtime_error("Worker cannot release a captured reference");
 heap().lifetimes.end_borrow(token); shared_heap().reference_owners.erase(token);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_ref_release_nullable(uint64_t token) {
    try {
    RuntimeGuard runtime_guard;

    if (token) lymar_aot_ref_release(token);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_consume(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (!h.allocations.count(pointer)) throw std::runtime_error("AOT consume of unowned object");
    h.lifetimes.adopt(pointer);
    h.lifetimes.consume(pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}

uint64_t lymar_aot_call_enter() {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    h.invocations.push_back({h.active, std::move(h.pending_args), {}, {}});
    h.pending_args.clear();
    return h.active;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_arg_set(uint64_t index, uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& args = heap().pending_args;
    if (args.size() <= index) args.resize(index + 1);
    args[index] = pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_arg_kind(uint64_t index, uint64_t fallback) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    return h.invocations.empty() || index >= h.invocations.back().args.size() ? fallback : h.invocations.back().args[index];

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_arg_get(uint64_t index) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    return h.invocations.empty() || index >= h.invocations.back().args.size() ? 0 : h.invocations.back().args[index];

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_call_leave(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT invocation stack underflow");
    for (auto slot : h.invocations.back().slots) h.shadow.erase(slot);
    h.invocations.pop_back();
    h.return_pointer = pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_return_pointer() {
    try {
    RuntimeGuard runtime_guard;
 return heap().return_pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_param_push(uint64_t value, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT Param outside invocation");
    h.invocations.back().staged_params.emplace_back(value, is_pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_param_pop(uint64_t fallback, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.invocations.empty()) throw std::runtime_error("AOT ConstructError outside invocation");
    auto& params = h.invocations.back().staged_params;
    h.return_pointer = is_pointer;
    if (params.empty()) return fallback;
    auto [value, pointer] = params.back();
    params.pop_back();
    h.return_pointer = pointer;
    return value;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_slot_pointer(uint64_t address) {
    try {
    RuntimeGuard runtime_guard;

    auto& flags = heap().shadow;
    auto found = flags.find(address);
    auto result = found != flags.end() ? found->second : 0;
    return result;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_region_current() {
    try {
    RuntimeGuard runtime_guard;
 return heap().active;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_region_enter(uint64_t lexical) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.next == UINT64_MAX) throw std::overflow_error("AOT region identity exhausted");
    auto id = h.next++;
    h.regions.emplace(id, Region{h.active, lexical, h.regions.at(h.active).depth + 1, {}});
    h.active = id;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_region_exit(uint64_t lexical) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (!h.active || h.regions.at(h.active).lexical != lexical)
        throw std::runtime_error("AOT RegionExit mismatch");
    auto id = h.active;
    auto parent = h.regions.at(id).parent;
    h.cleanup(id);
    h.active = parent;
    h.regions.erase(id);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_region_move(uint64_t value, uint64_t lexical, uint64_t caller, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    auto target = caller;
    if (lexical) {
        target = h.active;
        while (target && h.regions.at(target).lexical != lexical) target = h.regions.at(target).parent;
        if (!target) throw std::runtime_error("AOT RegionMove target is not active");
    }
    // Validate the target even for an immediate value.
    h.regions.at(target);
    if (is_pointer == object_kind) h.promote(value, target);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_alloc(uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    // TEMP DIAGNOSTIC: periodic page-guard arming around the state slot.
#if defined(_WIN32)
    if (probe_ctx && ++probe_ctx->allocs == probe_ctx->arm_at) probe_arm_guard();
#endif

    if (size > SIZE_MAX) throw std::bad_alloc();
    auto pointer = reinterpret_cast<Word>(heap().allocator.allocate(std::max(size, Word(1))));
    if (!pointer) throw std::bad_alloc();
    std::memset(reinterpret_cast<void*>(pointer), 0, std::max(size, Word(1)));
    auto& h = heap();
    try {
        Word alloc_size = std::max(size, Word(1));
        h.allocations.emplace(pointer, Allocation{static_cast<size_t>(alloc_size), h.active, {}});
        Word start_page = pointer >> 12;
        Word end_page = (pointer + alloc_size - 1) >> 12;
        for (Word page = start_page; page <= end_page; ++page) {
            h.page_map[page].push_back(pointer);
        }
        h.regions.at(h.active).members.insert(pointer);
    } catch (...) {
        h.allocations.erase(pointer);
        h.allocator.deallocate(reinterpret_cast<void*>(pointer));
        throw;
    }
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_box_float(double number) {
    try {
    RuntimeGuard runtime_guard;

    auto pointer = lymar_aot_alloc(16);
    heap().allocations.at(pointer).float_box = true;
    const Word header = 9; // Existing TYPE_FLOAT header and payload offsets.
    std::memcpy(reinterpret_cast<void*>(pointer), &header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 8), &number, sizeof(number));
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_scalar_to_string(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (kind == object_kind && !lymar_aot_is_nil(value, kind) && (read_word(value) & 0xffffffff) == 11)
        return value;
    std::string wide_text;
    char text[64];
    const char* output = text;
    size_t length;
    if (lymar_aot_is_nil(value, kind)) { output = "nil"; length = 3; }
    else if (kind == boolean_kind) { output = value ? "true" : "false"; length = value ? 4 : 5; }
    else if (kind == object_kind && (read_word(value) & 0xffffffff) == 9)
        length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", lymar_aot_to_float(value, kind)));
    else if (auto integer = integer_number(value, kind)) { wide_text = integer_text(*integer); output = wide_text.c_str(); length = wide_text.size(); }
    else length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%lld", static_cast<long long>(value)));
    auto pointer = lymar_aot_alloc(24 + length + 1);
    Word header[] = {11, length, length};
    std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
    std::memcpy(reinterpret_cast<void*>(pointer + 24), output, length);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Erased scalar arguments must become strings before the generated formatter
// inspects object layouts. A float box is not a list, and a Boolean is not an
// integer. Compound objects retain their existing formatting path.
static uint64_t format_argument(uint64_t value, uint64_t kind, bool printable) {
    try {
        RuntimeGuard guard;
        auto& h = heap();
        std::unordered_set<Word> visiting;
        auto require = [&](Word pointer, Word bytes) {
            auto allocation = h.allocations.find(pointer);
            if (allocation == h.allocations.end() || bytes > allocation->second.size)
                throw std::runtime_error("Invalid or expired formatting receiver");
        };
        auto element_kind = [&](Word address) {
            auto found = h.shadow.find(address);
            return found == h.shadow.end() ? Word{0} : found->second;
        };
        std::function<std::string(Word, Word)> format = [&](Word word, Word mode) -> std::string {
            if (lymar_aot_is_nil(word, mode)) return "nil";
            if (mode == boolean_kind) return word ? "true" : "false";
            if (mode != object_kind) return integer_text(static_cast<int64_t>(word));
            require(word, 8);
            auto& allocation = h.allocations.at(word);
            auto type = read_word(word) & 0xffffffff;
            if (!allocation.dictionary && type == 11) {
                require(word, 24);
                auto length = read_word(word, 8);
                if (length > allocation.size - 24) throw std::runtime_error("Invalid string length");
                return std::string(reinterpret_cast<const char*>(word + 24), length);
            }
            if (!allocation.dictionary && type >= 5 && type <= 8) {
                require(word, type <= 6 ? 16 : 32);
                return integer_text(*integer_number(word, mode));
            }
            if (!allocation.dictionary && type == 9) {
                require(word, 16);
                char buffer[64];
                std::snprintf(buffer, sizeof(buffer), "%.6g", lymar_aot_to_float(word, mode));
                return buffer;
            }
            if (!visiting.insert(word).second) throw std::runtime_error("Cyclic value formatting");
            struct Visit { std::unordered_set<Word>& set; Word word; ~Visit() { set.erase(word); } } visit{visiting, word};
            require(word, 32);
            if (!allocation.dictionary && type == 0x454e554d) {
                auto name = format(read_word(word, 24), element_kind(word + 24));
                auto payload = read_word(word, 16), payload_kind = element_kind(word + 16);
                if (lymar_aot_is_nil(payload, payload_kind)) return name;
                return name + "(" + format(payload, payload_kind) + ")";
            }
            auto nested = [&](Word child, Word child_kind) {
                auto rendered = format(child, child_kind);
                auto found = h.allocations.find(child);
                if (printable && child_kind == object_kind && found != h.allocations.end() &&
                    !found->second.raw_memory && !found->second.dictionary &&
                    found->second.size >= 24 && (read_word(child) & 0xffffffff) == 11)
                    return std::string("\"") + rendered + "\"";
                return rendered;
            };
            Word elements, count;
            std::string text;
            if (allocation.dictionary) {
                count = read_word(word); auto capacity = read_word(word, 8);
                elements = read_word(word, 16); auto values = read_word(word, 24);
                if (count > capacity || capacity > UINT64_MAX / sizeof(Word)) throw std::runtime_error("Invalid dictionary length");
                require(elements, capacity * sizeof(Word)); require(values, capacity * sizeof(Word));
                std::vector<std::pair<std::string, std::string>> entries;
                for (Word index = 0; index < count; ++index) {
                    auto key = elements + index * sizeof(Word), value = values + index * sizeof(Word);
                    entries.emplace_back(nested(read_word(key), element_kind(key)), nested(read_word(value), element_kind(value)));
                }
                if (printable) std::sort(entries.begin(), entries.end());
                text = "{";
                for (size_t index = 0; index < entries.size(); ++index) {
                    if (index) text += ", ";
                    text += entries[index].first + ": " + entries[index].second;
                }
                return text + "}";
            }
            if (type == 1 || type == 3) {
                elements = read_word(word, 8); count = read_word(word, 16);
                text = type == 1 ? "[" : "(";
            } else if (type == 15) {
                require(word, 40); elements = read_word(word, 16); count = read_word(word, 24);
                text = format(read_word(word, 8), object_kind) + "{";
            } else throw std::runtime_error("Unsupported object formatting kind");
            if (count > UINT64_MAX / sizeof(Word)) throw std::runtime_error("Invalid aggregate length");
            require(elements, count * sizeof(Word));
            for (Word index = 0; index < count; ++index) {
                if (index) text += ", ";
                auto address = elements + index * sizeof(Word);
                text += nested(read_word(address), element_kind(address));
            }
            return text + (type == 1 ? "]" : type == 3 ? ")" : "}");
        };
        auto text = format(value, kind);
        auto pointer = lymar_aot_alloc(24 + text.size() + 1);
        Word header[] = {11, text.size(), text.size()};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        std::memcpy(reinterpret_cast<void*>(pointer + 24), text.c_str(), text.size() + 1);
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_format_argument(uint64_t value, uint64_t kind) {
    return format_argument(value, kind, false);
}
uint64_t lymar_aot_mark_dictionary(uint64_t pointer) {
    RuntimeGuard guard;
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || found->second.size != 32)
        throw std::runtime_error("Invalid dictionary allocation");
    found->second.dictionary = true;
    return pointer;
}
void lymar_aot_print_value(uint64_t value, uint64_t kind) {
    RuntimeGuard guard;
    auto string = format_argument(value, kind, true);
    lymar_stdout_write(reinterpret_cast<const void*>(string + 24), read_word(string, 8));
}
uint64_t lymar_aot_float_to_string(double value) {
    try {
        RuntimeGuard guard;
        char text[64];
        auto length = static_cast<size_t>(std::snprintf(text, sizeof(text), "%.6g", value));
        auto pointer = lymar_aot_alloc(24 + length + 1);
        Word header[] = {11, length, length};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        std::memcpy(reinterpret_cast<void*>(pointer + 24), text, length + 1);
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_float_bits_to_string(uint64_t bits) {
    double number;
    std::memcpy(&number, &bits, sizeof(number));
    return lymar_aot_float_to_string(number);
}
uint64_t lymar_aot_length(uint64_t pointer,uint64_t kind) {
    RuntimeGuard guard;
    if(lymar_aot_is_nil(pointer,kind)) return 0;
    if(kind!=object_kind) throw std::runtime_error("len: unsupported scalar type");
    auto found=heap().allocations.find(pointer);
    if(found==heap().allocations.end() || found->second.raw_memory || found->second.size<8)
        throw std::runtime_error("Invalid or expired length receiver");
    auto& record=found->second;
    if(record.dictionary) {
        if(record.size<32) throw std::runtime_error("Invalid dictionary header");
        auto count=read_word(pointer),capacity=read_word(pointer,8);
        for(Word offset:{Word(16),Word(24)}) {
            auto data=heap().allocations.find(read_word(pointer,offset));
            if(count>capacity || data==heap().allocations.end() || capacity>data->second.size/8)
                throw std::runtime_error("Invalid dictionary storage");
        }
        return count;
    }
    auto type=read_word(pointer)&0xffffffff;
    if(type==11) {
        if(!string_data(pointer)) throw std::runtime_error("Invalid string header");
        return read_word(pointer,8);
    }
    if(type==1) return lymar_aot_ffi_list_size(pointer);
    if(type==3) {
        if(record.size<32) throw std::runtime_error("Invalid tuple header");
        auto count=read_word(pointer,16);auto data=heap().allocations.find(read_word(pointer,8));
        if(data==heap().allocations.end() || count>data->second.size/8)
            throw std::runtime_error("Invalid tuple storage");
        return count;
    }
    if(type==15) {
        if(record.size<40) throw std::runtime_error("Invalid frame header");
        auto* name=string_data(read_word(pointer,8));
        // Preserve the VM's existing frame-length interpretation.
        if(name && std::strcmp(name,"LinkedList")==0 && read_word(pointer,24)>2) {
            auto address=lymar_aot_frame_field_address(pointer,2);
            return lymar_aot_to_integer(read_word(address),lymar_aot_slot_pointer(address));
        }
        return 0;
    }
    throw std::runtime_error("len: unsupported object type");
}
uint64_t lymar_aot_tuple_length(uint64_t pointer, uint64_t kind) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_is_object(pointer, kind)) return 0;
        auto record = heap().allocations.find(pointer);
        if (record == heap().allocations.end() || record->second.size < 32)
            throw std::runtime_error("Invalid or expired tuple receiver");
        return !record->second.dictionary && (read_word(pointer) & 0xffffffff) == 3 ? read_word(pointer, 16) : 0;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_string_hash(uint64_t value, uint64_t kind) {
    try {
        RuntimeGuard guard;
        if (!lymar_aot_string_receiver(value, kind))
            throw std::runtime_error("_builtin_string_hash_bytes expects str");
        Word hash = 5381, length = read_word(value, 8);
        auto* bytes = reinterpret_cast<const unsigned char*>(value + 24);
        for (Word index = 0; index < length; ++index) hash = (hash * 33 + bytes[index]) % 2147483647;
        return hash;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_list_slice(uint64_t value, uint64_t start, uint64_t end,
                              uint64_t kind, uint64_t start_kind, uint64_t end_kind) {
    try {
        RuntimeGuard guard;
        auto& h = heap();
        Word source = 0, count = 0;
        if (!lymar_aot_is_nil(value, kind)) {
            auto record = h.allocations.find(value);
            if (kind != object_kind || record == h.allocations.end() ||
                record->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
                throw std::runtime_error("_builtin_list_slice expects list");
            source = read_word(value, 8); count = read_word(value, 16);
            auto data = h.allocations.find(source);
            if (data == h.allocations.end() || count > data->second.size / sizeof(Word))
                throw std::runtime_error("Invalid list elements allocation");
        }
        auto first = static_cast<int64_t>(lymar_aot_string_index(start, start_kind));
        auto last = static_cast<int64_t>(lymar_aot_string_index(end, end_kind));
        Word begin = std::min(count, static_cast<Word>(std::max<int64_t>(0, first)));
        Word limit = std::min(count, static_cast<Word>(std::max<int64_t>(0, last)));
        Word length = limit > begin ? limit - begin : 0;
        auto pointer = lymar_aot_alloc(32);
        auto elements = lymar_aot_alloc(std::max<Word>(1, length) * sizeof(Word));
        Word header[] = {1, elements, length, std::max<Word>(1, length)};
        std::memcpy(reinterpret_cast<void*>(pointer), header, sizeof(header));
        lymar_aot_edge(pointer + 8, elements, object_kind);
        for (Word index = 0; index < length; ++index) {
            auto address = source + (begin + index) * sizeof(Word);
            auto copied = read_word(address);
            auto found = h.shadow.find(address);
            Word mode = found == h.shadow.end() ? 0 : found->second;
            std::memcpy(reinterpret_cast<void*>(elements + index * sizeof(Word)), &copied, sizeof(copied));
            lymar_aot_edge(elements + index * sizeof(Word), copied, mode);
        }
        h.return_pointer = object_kind;
        return pointer;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// LoadConst strings are copied into the current region, just as the VM copies
// managed constants into its tracked heap. Static linker storage is never freed.
uint64_t lymar_aot_copy_constant(uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    auto pointer = lymar_aot_alloc(size);
    std::memcpy(reinterpret_cast<void*>(pointer), reinterpret_cast<const void*>(source), size);
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_free(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;
    if (pointer && pointer != 2 && heap().allocations.count(pointer)) heap().release(pointer);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (!is_pointer && !h.shadow.erase(address)) return;
    auto container = h.containing(address);
    if (is_pointer) h.shadow[address] = is_pointer;
    else h.shadow.erase(address);
    if (container == h.allocations.end()) {
        if (!h.invocations.empty()) h.invocations.back().slots.insert(address);
        return;
    }
    auto offset = address - container->first;
    container->second.edges.erase(offset);
    if (is_pointer == object_kind && h.containing(child) != h.allocations.end()) {
        container->second.edges[offset] = child;
        h.promote(child, container->second.owner);
    }

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
// Raw access is explicitly unsafe in source. Preserve external/FFI addresses;
// use memcpy so valid byte-addressed unaligned accesses do not acquire C++ UB.
// Raw bytes do not transfer pointee ownership; managed stores publish edges separately.
uint64_t lymar_aot_channel_length(uint64_t value, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    if (kind != object_kind || lymar_aot_is_nil(value, kind)) return 0;
    auto& h = heap();
    auto found = h.allocations.find(value);
    if (found == h.allocations.end() || found->second.size < 32 || (read_word(value) & 0xffffffff) != 1)
        return 0; // A non-queue task value is a single invocation, not an iterator.
    return read_word(value, 16);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
static uint64_t raw_address(uint64_t value, uint64_t kind) {
    if (kind == boolean_kind || lymar_aot_is_nil(value, kind)) return 0;
    if (kind != 0 && kind != object_kind) throw std::runtime_error("Invalid raw pointer kind");
    return value;
}
uint64_t lymar_aot_memory_load_kind(uint64_t pointer, uint64_t element, uint64_t pointer_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    if (!pointer || element >= 8) return object_kind;
    return 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_memory_load(uint64_t pointer, uint64_t element, uint64_t pointer_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    if (element > 10) throw std::runtime_error("Invalid raw memory element kind");
    if (!pointer) return lymar_aot_nil();
    const auto* address = reinterpret_cast<const void*>(pointer);
    switch (element) {
#define LM_RAW_LOAD(ID, TYPE) case ID: { TYPE value; std::memcpy(&value, address, sizeof(value)); return static_cast<Word>(value); }
        LM_RAW_LOAD(0, int8_t) LM_RAW_LOAD(1, uint8_t)
        LM_RAW_LOAD(2, int16_t) LM_RAW_LOAD(3, uint16_t)
        LM_RAW_LOAD(4, int32_t) LM_RAW_LOAD(5, uint32_t)
        LM_RAW_LOAD(6, int64_t) LM_RAW_LOAD(7, uint64_t)
#undef LM_RAW_LOAD
        case 8: { float value; std::memcpy(&value, address, sizeof(value)); return lymar_aot_box_float(value); }
        case 9: { double value; std::memcpy(&value, address, sizeof(value)); return lymar_aot_box_float(value); }
        case 10: { Word value; std::memcpy(&value, address, sizeof(value)); return value; }
    }
    throw std::runtime_error("Invalid raw memory element kind");

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
// Raw stores use the VM's physical numeric conversion, not string parsing or
// arbitrary object-header heuristics. Raw buffers may themselves begin with 9.
static double raw_numeric_value(uint64_t value, uint64_t kind) {
    if (kind == 0) return static_cast<double>(static_cast<int64_t>(value));
    if (kind != object_kind) return 0.0;
    auto found = heap().allocations.find(value);
    if (found == heap().allocations.end() || !found->second.float_box || found->second.size < 16 ||
        (read_word(value) & 0xffffffff) != 9) return 0.0;
    double result; std::memcpy(&result, reinterpret_cast<void*>(value + 8), sizeof(result));
    return result;
}
static uint64_t raw_integer_value(uint64_t value, uint64_t kind) {
    return kind == 0 ? value : static_cast<Word>(static_cast<int64_t>(raw_numeric_value(value, kind)));
}
uint64_t lymar_aot_raw_alloc(uint64_t size, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    size = raw_integer_value(size, kind);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    auto pointer = lymar_aot_alloc(size);
    heap().allocations.at(pointer).raw_memory = true;
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_raw_free(uint64_t pointer, uint64_t kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, kind);
    auto found = heap().allocations.find(pointer);
    if (found != heap().allocations.end() && found->second.raw_memory) heap().release(pointer);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_memory_store(uint64_t pointer, uint64_t value, uint64_t element, uint64_t kind, uint64_t pointer_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    if (element > 10) throw std::runtime_error("Invalid raw memory element kind");
    if (!pointer) return;
    auto* address = reinterpret_cast<void*>(pointer);
    const Word integer = element < 8 ? raw_integer_value(value, kind) : value;
    size_t width = 0;
    switch (element) {
#define LM_RAW_STORE(ID, TYPE, VALUE) case ID: { TYPE stored = static_cast<TYPE>(VALUE); width = sizeof(stored); std::memcpy(address, &stored, width); break; }
        LM_RAW_STORE(0, int8_t, integer) LM_RAW_STORE(1, uint8_t, integer)
        LM_RAW_STORE(2, int16_t, integer) LM_RAW_STORE(3, uint16_t, integer)
        LM_RAW_STORE(4, int32_t, integer) LM_RAW_STORE(5, uint32_t, integer)
        LM_RAW_STORE(6, int64_t, integer) LM_RAW_STORE(7, uint64_t, integer)
        LM_RAW_STORE(8, float, raw_numeric_value(value, kind))
        LM_RAW_STORE(9, double, raw_numeric_value(value, kind))
        LM_RAW_STORE(10, Word, (kind == 0 || (kind == object_kind && !lymar_aot_is_nil(value, kind))) ? value : 0)
#undef LM_RAW_STORE
    }
    auto& h = heap();
    // At most fifteen byte-addressed word slots overlap an eight-byte write;
    // do not scan unrelated stack/object kind metadata on every raw store.
    h.forget_kinds(pointer, width, true);
    auto owner = h.containing(pointer);
    if (owner != h.allocations.end()) {
        auto start = pointer - owner->first;
        for (size_t offset = start >= sizeof(Word) - 1 ? start - (sizeof(Word) - 1) : 0;
             offset <= start || offset - start < width; ++offset) {
            owner->second.edges.erase(offset);
            if (offset == SIZE_MAX) break;
        }
    }
    // Physical raw-pointer bytes do not acquire ownership. The VM does not
    // promote pointees on MemoryStore; canonical managed stores publish edges
    // separately through lymar_aot_edge. Preserve destructor scope/order.

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_global_edge(uint64_t address, uint64_t child, uint64_t is_pointer) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (is_pointer) { h.shadow[address] = is_pointer; if (is_pointer == object_kind) h.promote(child, 0); }
    else h.shadow.erase(address);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_copy(uint64_t destination, uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    // Snapshot every value kind before memmove, including overlapping ranges.
    // std::map lower_bound gives an O(log n + k) range walk over only the
    // entries that actually live in [source, source + size).
    std::vector<std::pair<Word, Word>> kinds;
    Word src_end = source + size;
    for (auto it = h.shadow.lower_bound(source); it != h.shadow.end() && it->first + sizeof(Word) <= src_end; ++it)
        kinds.emplace_back(destination + (it->first - source), it->second);
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);
    h.forget_kinds(destination, size, true);
    auto dst = h.containing(destination);
    if (dst != h.allocations.end()) {
        auto start = destination - dst->first;
        std::erase_if(dst->second.edges, [&](auto edge) { return edge.first >= start ? edge.first - start < size : start - edge.first < sizeof(Word); });
    }
    for (auto [address, kind] : kinds) lymar_aot_edge(address, read_word(address), kind);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_copy(uint64_t destination, uint64_t source, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!destination || !source || static_cast<int64_t>(size) <= 0) return;
    auto& h = heap();
    // Raw byte copies carry no ownership contract. Managed aggregate copies
    // use lymar_aot_copy and explicitly preserve their edges/kinds instead.
    h.forget_kinds(destination, size, true);
    auto owner = h.containing(destination);
    if (owner != h.allocations.end()) {
        auto start = destination - owner->first;
        std::erase_if(owner->second.edges, [&](auto entry) {
            return entry.first >= start ? entry.first - start < size : start - entry.first < sizeof(Word);
        });
    }
    std::memmove(reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_fill(uint64_t destination, uint64_t value, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!destination || static_cast<int64_t>(size) <= 0) return;
    auto& h = heap();
    // Invalidate overlapping kinds/edges; byte filling must not retain a
    // pointer edge whose bytes have been replaced by unrelated data.
    h.forget_kinds(destination, size, true);
    auto owner = h.containing(destination);
    if (owner != h.allocations.end()) {
        auto start = destination - owner->first;
        std::erase_if(owner->second.edges, [&](auto entry) {
            return entry.first >= start ? entry.first - start < size : start - entry.first < sizeof(Word);
        });
    }
    std::memset(reinterpret_cast<void*>(destination), static_cast<unsigned char>(value), size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_raw_compare(uint64_t left, uint64_t right, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!left || !right || static_cast<int64_t>(size) <= 0) return 0;
    return static_cast<int64_t>(std::memcmp(reinterpret_cast<void*>(left), reinterpret_cast<void*>(right), size));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_resize(uint64_t pointer, uint64_t size) {
    try {
    RuntimeGuard runtime_guard;

    if (!pointer) return lymar_aot_alloc(size);
    if (!size) { lymar_aot_free(pointer); return 0; }
    auto& h = heap();
    auto original = h.allocations.at(pointer);
    auto replacement = lymar_aot_alloc(size);
    auto& allocation = h.allocations.at(replacement);
    h.regions.at(allocation.owner).members.erase(replacement);
    allocation.owner = original.owner;
    h.regions.at(allocation.owner).members.insert(replacement);
    allocation.finalizer = original.finalizer;
    allocation.float_box = original.float_box;
    allocation.raw_memory = original.raw_memory;
    lymar_aot_copy(replacement, pointer, std::min(size, Word(original.size)));
    lymar_aot_free(pointer);
    return replacement;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
uint64_t lymar_aot_raw_resize(uint64_t pointer, uint64_t size, uint64_t pointer_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    pointer = raw_address(pointer, pointer_kind);
    size = raw_integer_value(size, size_kind);
    if (static_cast<int64_t>(size) < 0) return lymar_aot_nil();
    if (!pointer) return lymar_aot_raw_alloc(size, 0);
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || !found->second.raw_memory) return lymar_aot_nil();
    if (!size) { heap().release(pointer); return lymar_aot_nil(); }
    return lymar_aot_resize(pointer, size);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_raw_copy_checked(uint64_t destination, uint64_t source, uint64_t size,
                               uint64_t destination_kind, uint64_t source_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    lymar_aot_raw_copy(raw_address(destination, destination_kind), raw_address(source, source_kind), raw_integer_value(size, size_kind));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_raw_fill_checked(uint64_t destination, uint64_t value, uint64_t size,
                               uint64_t destination_kind, uint64_t value_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    lymar_aot_raw_fill(raw_address(destination, destination_kind), raw_integer_value(value, value_kind), raw_integer_value(size, size_kind));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_raw_compare_checked(uint64_t left, uint64_t right, uint64_t size,
                                     uint64_t left_kind, uint64_t right_kind, uint64_t size_kind) {
    try {
    RuntimeGuard runtime_guard;

    return lymar_aot_raw_compare(raw_address(left, left_kind), raw_address(right, right_kind), raw_integer_value(size, size_kind));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_set_finalizer(uint64_t pointer, void (*callback)(uint64_t)) {
    try {
    RuntimeGuard runtime_guard;

    heap().allocations.at(pointer).finalizer = callback;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
void lymar_aot_finalize(uint64_t pointer) {
    try {
    RuntimeGuard runtime_guard;
 heap().finalize(pointer);
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
#if !defined(__wasi__)
void* NativeGraphicsAccess::list(Value value) {
    auto& allocations=heap().allocations;auto found=allocations.find(value.word);
    if(value.kind!=object_kind || found==allocations.end() || found->second.raw_memory ||
       found->second.dictionary || found->second.size<32 || read_word(value.word)!=1) return nullptr;
    lymar_aot_ffi_list_size(value.word);
    return reinterpret_cast<void*>(value.word);
}
const char* NativeGraphicsAccess::string(Value value) {
    return value.kind==object_kind?string_data(value.word):nullptr;
}
NativeGraphicsAccess::List* NativeGraphicsAccess::new_list() {
    auto pointer=lymar_aot_alloc(32),data=lymar_aot_alloc(32);
    Word header[4]={1,data,0,4};std::memcpy(reinterpret_cast<void*>(pointer),header,32);
    lymar_aot_edge(pointer+8,data,object_kind);
    return reinterpret_cast<List*>(pointer);
}
void NativeGraphicsAccess::append(List* list,Value value) {
    auto pointer=reinterpret_cast<Word>(list),count=lymar_aot_ffi_list_size(pointer);
    auto data=read_word(pointer,8),capacity=read_word(pointer,24);
    if(count==capacity) {
        if(capacity>UINT64_MAX/16) throw std::runtime_error("Graphics event list capacity overflow");
        auto next=std::max<Word>(4,capacity*2),replacement=lymar_aot_alloc(next*8);
        for(Word index=0;index<count;++index) {
            auto item=lymar_aot_ffi_list_item(pointer,index),kind=lymar_aot_ffi_list_kind(pointer,index);
            std::memcpy(reinterpret_cast<void*>(replacement+index*8),&item,8);
            lymar_aot_edge(replacement+index*8,item,kind);
        }
        std::memcpy(reinterpret_cast<void*>(pointer+8),&replacement,8);
        std::memcpy(reinterpret_cast<void*>(pointer+24),&next,8);
        lymar_aot_edge(pointer+8,replacement,object_kind);
        lymar_aot_free(data);data=replacement;
    }
    std::memcpy(reinterpret_cast<void*>(data+count*8),&value.word,8);
    lymar_aot_edge(data+count*8,value.word,value.kind);
    ++count;std::memcpy(reinterpret_cast<void*>(pointer+16),&count,8);
}
#endif
uint64_t lymar_aot_resource_create(uint64_t type, uint64_t) {
    try {
    RuntimeGuard runtime_guard;

    if (type == 9) return 0; // stdout
    if (type == 10) return 1; // stderr
    if (type == 18 || type == 4) { auto& f = files(); auto id = f.next++; f.handles.emplace(id, nullptr); return id; }
    if(type==16) {auto& f=files();auto id=f.next++;f.hashes.try_emplace(id);return id;}
    if(type==11) {auto& f=files();auto id=f.next++;f.mems.emplace(id, std::make_pair(nullptr, size_t(0)));return id;}
    // OS (18) and PROCESS (4) are stateless service handles. The facts they
    // report come from the process itself, so nothing is stored per handle.
    if(type==18||type==4) {auto& f=files();auto id=f.next++;f.services.emplace(id,type);return id;}
#if !defined(__wasi__)
    if(type==17) {auto& f=files();auto id=f.next++;f.graphics.emplace(id,std::make_unique<NativeGraphics>());return id;}
#endif
    if (type != 0) throw std::runtime_error("Standalone resource type is not implemented: " + std::to_string(type));
    auto& f = files();
    auto id = f.next++;
    f.handles.emplace(id, nullptr);
    return id;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_resource_destroy(uint64_t id) {
    try {
    RuntimeGuard runtime_guard;

    auto& f = files();
    if(f.hashes.erase(id)) return;
    if(f.services.erase(id)) return;
    if(auto mem=f.mems.find(id);mem!=f.mems.end()) { if(mem->second.first) std::free(mem->second.first); f.mems.erase(mem); return; }
#if !defined(__wasi__)
    if(f.graphics.erase(id)) return;
#endif
    auto found = f.handles.find(id);
    if (found == f.handles.end()) return;
    if (found->second) std::fclose(found->second);
    f.handles.erase(found);

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}
uint64_t lymar_aot_resource_call(uint64_t id, uint64_t operation, uint64_t count, uint64_t arguments) {
    try {
    RuntimeGuard runtime_guard;

    constexpr Word nil = 2;
    auto& h = heap();
    h.return_pointer = object_kind; // Default failure is nil.
    std::vector<Word> args;
    std::vector<Word> pointers;
    for (Word n = 0; n < count; ++n) {
        auto value = read_word(arguments, n * 8);
        Word pointer = lymar_aot_slot_pointer(arguments + n * 8);
        if (pointer == object_kind && value > 4096 && (read_word(value) & 0xffffffff) == 1) {
            auto data = read_word(value, 8), size = read_word(value, 16);
            for (Word i = 0; i < size; ++i) {
                args.push_back(read_word(data, i * 8));
                pointers.push_back(lymar_aot_slot_pointer(data + i * 8));
            }
        } else if (!lymar_aot_is_nil(value, pointer)) { args.push_back(value); pointers.push_back(pointer); }
    }
    auto arg_string = [&](size_t n) { return n < args.size() && pointers[n] == object_kind ? string_data(args[n]) : nullptr; };
    auto& f = files();
    auto service = f.services.find(id);
    if (service != f.services.end()) {
        // Shares LM::Runtime::OS with the RegisterVM resource handlers, so both
        // backends report identical values for the same operation.
        namespace os = LM::Runtime::OS;
        auto truth=[&](bool yes) {h.return_pointer=boolean_kind;return Word(yes?1:0);};
        auto number=[&](int64_t value) {h.return_pointer=0;return static_cast<Word>(value);};
        auto string_object=[&](const std::string& bytes) {
            auto object=lymar_aot_alloc(25+bytes.size());
            Word header[3]={11,bytes.size(),bytes.size()};
            std::memcpy(reinterpret_cast<void*>(object),header,24);
            std::memcpy(reinterpret_cast<void*>(object+24),bytes.c_str(),bytes.size()+1);
            return object;
        };
        auto text=[&](const std::string& bytes) {h.return_pointer=object_kind;return string_object(bytes);};
        auto absent=[&]() {h.return_pointer=object_kind;return nil;};
        auto strings=[&](const std::vector<std::string>& items) {
            // Same [str] layout the graphics event list uses: a 32-byte header
            // of {TYPE_LIST, data, count, capacity} plus the element slots.
            auto pointer=lymar_aot_alloc(32);
            auto capacity=std::max<Word>(1,items.size());
            auto data=lymar_aot_alloc(capacity*8);
            Word header[4]={1,data,0,capacity};
            std::memcpy(reinterpret_cast<void*>(pointer),header,32);
            lymar_aot_edge(pointer+8,data,object_kind);
            for (const auto& item : items) {
                auto object=string_object(item);
                // Elements are written back through the header: an allocation
                // above can relocate the payload, so no cached address is reused.
                auto slot_data=read_word(pointer,8);
                auto count=read_word(pointer,16);
                if (count>=capacity) break;
                std::memcpy(reinterpret_cast<void*>(slot_data+count*8),&object,8);
                lymar_aot_edge(slot_data+count*8,object,object_kind);
                ++count;
                std::memcpy(reinterpret_cast<void*>(pointer+16),&count,8);
            }
            h.return_pointer=object_kind;return pointer;
        };
        auto arg_text=[&](size_t n) { return n < args.size() && pointers[n] == object_kind ? std::string(arg_string(n)) : std::string(); };
        if (service->second == 18) {  // ResourceType::OS
            if (operation == 49) {  // ENV_GET: nil when the variable is unset.
                std::string value;
                if (!os::env_lookup(arg_text(0), value)) return absent();
                return text(value);
            }
            if (operation == 50) return truth(!arg_text(0).empty() && os::env_set(arg_text(0), arg_text(1)));  // ENV_SET
            if (operation == 51) return truth(!arg_text(0).empty() && os::env_unset(arg_text(0)));  // ENV_UNSET
            if (operation == 52) return strings(os::env_list());  // ENV_LIST
            if (operation == 53) { auto path=os::cwd(); return path.empty()?absent():text(path); }  // CWD
            if (operation == 54) return truth(!arg_text(0).empty() && os::chdir_to(arg_text(0)));  // CHDIR
            if (operation == 55) return text(os::home_dir());  // HOME_DIR
            if (operation == 56) return text(os::temp_dir());  // TEMP_DIR
            if (operation == 57) return text(os::exe_path());  // EXE_PATH
            if (operation == 58) return text(os::os_name());  // OS_NAME
            if (operation == 59) return text(os::arch());  // ARCH
            if (operation == 60) return text(os::hostname());  // HOSTNAME
            if (operation == 61) return number(os::num_cpu());  // NUM_CPU
            return absent();
        }
        if (service->second == 4) {  // ResourceType::PROCESS
            if (operation == 62) return strings(os::program_arguments());  // PROC_ARGS
            if (operation == 67) return text(os::command_name());  // PROC_COMMAND
            if (operation == 64) return number(os::pid());  // PROC_ID
            if (operation == 65) return number(os::rss_kb());  // PROC_RSS (kB, -1 unsupported)
            if (operation == 66) return number(os::peak_rss_kb());  // PROC_PEAK_RSS
            if (operation == 63) {  // PROC_EXIT: never returns.
                int64_t code = 0;
                if (!args.empty()) { auto value = integer_number(args[0], pointers[0]); if (value) code = *value; }
                os::terminate(static_cast<int>(code));
                return number(code);
            }
            if (operation == 9) {  // SPAWN: flattened argv, blocks, returns exit code.
                std::vector<std::string> argv;
                for (size_t n = 0; n < args.size(); ++n) { auto* text_value = arg_string(n); if (text_value) argv.emplace_back(text_value); }
                if (argv.empty()) return number(-1);
                return number(os::spawn_wait(argv));
            }
            return absent();
        }
        return absent();
    }
#if !defined(__wasi__)
    if(auto graphics=f.graphics.find(id);graphics!=f.graphics.end()) {
        std::vector<GraphicsValue> values;
        for(size_t index=0;index<args.size();++index) values.push_back({args[index],pointers[index]});
        auto returned=graphics->second->call(static_cast<LM::Backend::VM::ResourceOperation>(operation),values,nullptr);
        h.return_pointer=returned.kind;return returned.word;
    }
#endif
    if(auto hash=f.hashes.find(id);hash!=f.hashes.end()) {
        auto truth=[&](bool yes) {h.return_pointer=boolean_kind;return yes?Word(1):Word(0);};
        auto text=[&](const std::string& bytes) {auto object=lymar_aot_alloc(25+bytes.size());Word header[3]={11,bytes.size(),bytes.size()};std::memcpy(reinterpret_cast<void*>(object),header,24);std::memcpy(reinterpret_cast<void*>(object+24),bytes.c_str(),bytes.size()+1);h.return_pointer=object_kind;return object;};
        if(operation==0) {auto* algorithm=args.empty()?"sha256":arg_string(0);return truth(algorithm && hash->second.open(algorithm));}
        if(operation==3) {auto* bytes=arg_string(0);if(!bytes) return truth(false);hash->second.write(bytes,std::strlen(bytes));return truth(true);}
        if(operation==2) return text(hash->second.read());
        if(operation==35) {auto* algorithm=args.empty()?"sha256":arg_string(0);auto* key=arg_string(1);auto* bytes=arg_string(2);if(!algorithm || !key || !bytes) return nil;return text(LM::Runtime::compute_hmac(algorithm,key,bytes));}
        if(operation==1) return truth(true);
        return nil;
    }
    if(auto mem=f.mems.find(id);mem!=f.mems.end()) {
        auto& buf = mem->second;
        auto truth=[&](bool yes) {h.return_pointer=boolean_kind;return yes?Word(1):Word(0);};
        if(operation==0) { // OPEN: allocate / resize the byte buffer to the requested size.
            size_t n = buf.second;
            if (!args.empty()) { auto v = integer_number(args[0], pointers[0]); if (v) n = static_cast<size_t>(*v); }
            if (buf.first) std::free(buf.first);
            buf.first = n ? std::malloc(n) : nullptr;
            buf.second = buf.first ? n : 0;
            return truth(n == 0 || buf.first != nullptr);
        }
        if(operation==3) { // WRITE: copy string bytes into the buffer (bounded by capacity).
            auto* d = arg_string(0);
            if (!d || !buf.first) return truth(false);
            size_t l = std::min(std::strlen(d), buf.second);
            std::memcpy(buf.first, d, l);
            return truth(true);
        }
        if(operation==2) { // READ: return the buffer contents as a string.
            if (!buf.first || buf.second == 0) { h.return_pointer=object_kind; return nil; }
            auto object=lymar_aot_alloc(25+buf.second);
            Word header[3]={11,buf.second,buf.second};
            std::memcpy(reinterpret_cast<void*>(object),header,24);
            std::memcpy(reinterpret_cast<void*>(object+24),buf.first,buf.second);
            reinterpret_cast<char*>(object)[24+buf.second]='\0';
            h.return_pointer=object_kind;return object;
        }
        if(operation==1) { // CLOSE: release the buffer, keep the resource handle alive.
            if (buf.first) std::free(buf.first);
            buf = {nullptr, 0};
            return truth(true);
        }
        if(operation==48) { // SIZE: memory measurement - report allocated byte count.
            h.return_pointer=0;return static_cast<Word>(buf.second);
        }
        h.return_pointer=object_kind;return nil;
    }
    auto found = f.handles.find(id);
    if (id > 1 && found == f.handles.end()) return nil;
    FILE* stream = id == 0 ? stdout : id == 1 ? stderr : found->second;
    // These operations return booleans in the VM, even through the any API.
    h.return_pointer = (operation == 2 || operation == 47) ? object_kind : boolean_kind;
    if (operation == 2 && count == 1) {
        // Environment get
        const char* k = arg_string(0);
        if (k) {
            const char* v = std::getenv(k);
            if (v) {
                size_t len = std::strlen(v);
                Word obj = lymar_aot_alloc(25 + len);
                Word hdr[3] = {11, len, len};
                std::memcpy(reinterpret_cast<void*>(obj), hdr, 24);
                std::memcpy(reinterpret_cast<void*>(obj + 24), v, len + 1);
                h.return_pointer = object_kind;
                return obj;
            }
        }
        return nil;
    }
    if (operation == 3 && count == 2) {
        // Environment set
        const char* k = arg_string(0);
        const char* v = arg_string(1);
        if (k && v) {
#if defined(_WIN32)
            SetEnvironmentVariableA(k, v);
#else
            setenv(k, v, 1);
#endif
            return 1;
        }
        return 0;
    }
    if (operation == 13 || operation == 49 || operation == 50) {
        // CWD / RSS / PID
        if (operation == 49 || operation == 50) {
            h.return_pointer = 0;
            return 4096; // RSS in KB
        }
        try {
            std::string p = std::filesystem::current_path().string();
            Word obj = lymar_aot_alloc(25 + p.size());
            Word hdr[3] = {11, p.size(), p.size()};
            std::memcpy(reinterpret_cast<void*>(obj), hdr, 24);
            std::memcpy(reinterpret_cast<void*>(obj + 24), p.c_str(), p.size() + 1);
            h.return_pointer = object_kind;
            return obj;
        } catch (...) {
            return nil;
        }
    }
    if (operation == 0) {
        if (id <= 1) return 0;
        if (stream) std::fclose(stream);
        const auto* path = arg_string(0);
        const auto* mode = arg_string(1);
        found->second = path && mode ? std::fopen(path, mode) : nullptr;
        return found->second != nullptr;
    }
    if (operation == 1) { lymar_aot_resource_destroy(id); return 1; }
    if (operation == 10) return stream != nullptr;
    if (operation == 29) return stream && std::fflush(stream) == 0;
    if (operation == 3) {
        auto* data = arg_string(0);
        if (!stream || !data) return 0;
        auto length = read_word(args[0], 8);
        auto written = std::fwrite(data, 1, length, stream);
        return std::fflush(stream) == 0 && written == length;
    }
    if (operation == 2 || operation == 47) {
        if (!stream) return nil;
        std::vector<unsigned char> bytes;
        unsigned char buffer[4096];
        size_t length;
        while ((length = std::fread(buffer, 1, sizeof(buffer), stream)))
            bytes.insert(bytes.end(), buffer, buffer + length);
        if (std::ferror(stream)) return nil;
        Word result;
        if (operation == 2) {
            result = lymar_aot_alloc(24 + bytes.size() + 1);
            auto* header = reinterpret_cast<Word*>(result);
            header[0] = 11; header[1] = header[2] = bytes.size();
            if (!bytes.empty()) std::memcpy(reinterpret_cast<void*>(result + 24), bytes.data(), bytes.size());
        } else {
            result = lymar_aot_alloc(32);
            auto data = lymar_aot_alloc(std::max(size_t(1), bytes.size()) * 8);
            auto* header = reinterpret_cast<Word*>(result);
            header[0] = 1; header[1] = data; header[2] = bytes.size(); header[3] = std::max(size_t(1), bytes.size());
            lymar_aot_edge(result + 8, data, 1);
            auto* elements = reinterpret_cast<Word*>(data);
            for (size_t i = 0; i < bytes.size(); ++i) elements[i] = bytes[i];
        }
        h.return_pointer = 1;
        return result;
    }
    if (operation == 30 || operation == 32 || operation == 33 || operation == 34) {
        auto* path = arg_string(0);
        if (!path) return 0;
        std::error_code error;
        if (operation == 30) return std::filesystem::create_directories(path, error);
        if (operation == 33) return std::filesystem::exists(path, error);
        if (operation == 34) return std::filesystem::remove(path, error);
        auto* destination = arg_string(1);
        if (!destination) return 0;
        std::filesystem::rename(path, destination, error);
        return !error;
    }
    throw std::runtime_error("Standalone file operation is not implemented: " + std::to_string(operation));

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
[[noreturn]] void lymar_aot_exit(uint64_t status) { std::exit(static_cast<int>(status)); }
uint64_t lymar_aot_live_allocations() {
    try {
    RuntimeGuard runtime_guard;
 return heap().allocations.size();
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return 0;
    }
}
void lymar_aot_reset() {
    try {
    RuntimeGuard runtime_guard;

    auto& h = heap();
    if (h.active || !h.invocations.empty()) throw std::runtime_error("AOT reset with active invocation");
    h.cleanup(0);
    h.shadow.clear();
    h.lifetimes.reset();
    while (!h.files.handles.empty()) lymar_aot_resource_destroy(h.files.handles.begin()->first);
    h.pending_args.clear();
    h.return_pointer = 0;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error, sizeof(heap().worker_error), "%s", failure.what());
        return;
    }
}

// These are private standalone helpers for existing canonical concurrency ops.
// Generated code tests the worker error flag before using a failed result.
uint64_t lymar_aot_worker_failed() {
    auto& h = heap();
    if (!h.worker) return 0;
    if (h.timed && std::chrono::steady_clock::now() >= h.deadline && !h.worker_error[0]) {
        h.timed_out=true;
        std::snprintf(h.worker_error,sizeof(h.worker_error),"Concurrent block exceeded its timeout");
        if(h.cancellation) h.cancellation->store(true);
    }
    if (h.cancellation && h.cancellation->load(std::memory_order_acquire) && !h.worker_error[0])
        std::snprintf(h.worker_error, sizeof(h.worker_error), "Worker cancelled");
    return h.worker_error[0] != 0;
}
void lymar_aot_call_abort() {
    RuntimeGuard guard;
    auto& h = heap();
    if (h.invocations.empty()) return;
    const auto region = h.invocations.back().region;
    while (h.active != region) {
        auto current = h.active, parent = h.regions.at(current).parent;
        h.cleanup(current); h.regions.erase(current); h.active = parent;
    }
    for (auto slot : h.invocations.back().slots) h.shadow.erase(slot);
    h.invocations.pop_back(); h.pending_args.clear(); h.return_pointer = 0;
}
void lymar_aot_assert(uint64_t condition, uint64_t message) {
    if (condition == 1 || condition == 18) return;
    auto text = message > 4096 ? string_data(message) : nullptr;
    if (!heap().worker) {
        if(text) std::printf("%s\n",text); else std::printf("Assertion failed\n");
        std::fflush(stdout);
        std::exit(1);
    }
    if (!heap().worker_error[0])
        std::snprintf(heap().worker_error, sizeof(heap().worker_error), "Assertion failed: %s", text ? text : "assertion");
}

static void checked_queue(Word pointer) {
    auto found = heap().allocations.find(pointer);
    if (found == heap().allocations.end() || found->second.size < 32 || (read_word(pointer) & 0xffffffff) != 1)
        throw std::runtime_error("Invalid or expired channel");
    auto size = read_word(pointer,16), capacity = read_word(pointer,24), data = read_word(pointer,8);
    auto buffer = heap().allocations.find(data);
    if (size > capacity || buffer == heap().allocations.end() || capacity > buffer->second.size / 8)
        throw std::runtime_error("Invalid channel storage");
}
uint64_t lymar_aot_channel_new() {
    try {
    RuntimeGuard guard;
    auto pointer = lymar_aot_alloc(32), data = lymar_aot_alloc(128);
    *reinterpret_cast<Word*>(pointer) = 1;
    *reinterpret_cast<Word*>(pointer+8) = data;
    *reinterpret_cast<Word*>(pointer+24) = 16;
    lymar_aot_edge(pointer+8,data,object_kind);
    heap().return_pointer = object_kind;
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_channel_push(uint64_t pointer, uint64_t value, uint64_t kind) {
    try {
        RuntimeGuard guard; checked_queue(pointer);
        if (shared_heap().closed_channels.count(pointer)) throw std::runtime_error("Send to closed channel");
        auto length = read_word(pointer,16), capacity = read_word(pointer,24), data = read_word(pointer,8);
        if (length == capacity) {
            if (capacity > UINT64_MAX / 16) throw std::overflow_error("Channel capacity overflow");
            data = lymar_aot_resize(data, capacity * 16);
            *reinterpret_cast<Word*>(pointer+8) = data;
            *reinterpret_cast<Word*>(pointer+24) = capacity * 2;
            lymar_aot_edge(pointer+8,data,object_kind);
        }
        auto address = data + length * 8;
        lymar_aot_edge(address,value,kind);
        *reinterpret_cast<Word*>(address) = value;
        *reinterpret_cast<Word*>(pointer+16) = length + 1;
        shared_heap().work_available.notify_all();
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
    }
}
uint64_t lymar_aot_channel_pop(uint64_t pointer) {
    try {
        RuntimeGuard guard; checked_queue(pointer);
        auto length = read_word(pointer,16), data = read_word(pointer,8);
        if (!length) { heap().return_pointer = object_kind; return 2; }
        auto value = read_word(data), kind = heap().shadow.count(data) ? heap().shadow.at(data) : 0;
        for (Word index = 1; index < length; ++index) {
            auto old_address = data + index * 8, address = old_address - 8;
            auto element = read_word(old_address);
            auto mode = heap().shadow.count(old_address) ? heap().shadow.at(old_address) : 0;
            *reinterpret_cast<Word*>(address) = element;
            lymar_aot_edge(address,element,mode);
        }
        lymar_aot_edge(data+(length-1)*8,0,0);
        *reinterpret_cast<Word*>(pointer+16) = length-1;
        heap().return_pointer = kind;
        return value;
    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
uint64_t lymar_aot_channel_has_data(uint64_t pointer) {
    try { RuntimeGuard guard; checked_queue(pointer); heap().return_pointer=0; return read_word(pointer,16)!=0; }
    catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_channel_close(uint64_t pointer) {
    try { RuntimeGuard guard; checked_queue(pointer); shared_heap().closed_channels.insert(pointer); shared_heap().work_available.notify_all(); }
    catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
    }
}
uint64_t lymar_aot_scheduler_new(uint64_t cores, uint64_t timeout, uint64_t config) {
    try {
    RuntimeGuard guard;
    auto pointer = lymar_aot_channel_new();
    shared_heap().schedulers[pointer] = {std::max(Word(1),cores),timeout,config};
    return pointer;

    } catch (const std::exception& failure) {
        if (runtime_lock_depth && heap().worker) throw;
        if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.what());
        return 0;
    }
}
void lymar_aot_scheduler_run(uint64_t pointer) {
    RuntimeSuspend release_parent_lock;
    struct Job { Word context, item, kind; };
    std::vector<Job> jobs;
    std::vector<Word> streams;
    Word parent_region;
    SchedulerConfiguration configuration;
    {
        RuntimeGuard guard; checked_queue(pointer);
        configuration = shared_heap().schedulers.at(pointer); parent_region = heap().active;
        auto length = read_word(pointer,16), data = read_word(pointer,8);
        for (Word index=0; index<length; ++index) {
            auto context = read_word(data,index*8);
            auto found = heap().allocations.find(context);
            if (found == heap().allocations.end() || found->second.size < 64 || !read_word(context,32))
                throw std::runtime_error("Invalid native task context");
            if (read_word(context,24)==1) { checked_queue(read_word(context,8)); streams.push_back(context); }
            else jobs.push_back({context,read_word(context,8),heap().shadow.count(context+8)?heap().shadow.at(context+8):0});
        }
    }
    if (jobs.empty() && streams.empty()) return;
    const Word policy = (configuration.config >> 24) & 3;
    const Word timeout_policy = (configuration.config >> 26) & 3;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(configuration.timeout);
    std::atomic<bool> stop{false};
    std::mutex selection;
    size_t next=0, active_producers=0;
    std::string failure;
    std::vector<std::thread> workers;
    auto worker = [&] {
        auto& h = heap(); h.worker=true; h.base=h.active=parent_region; h.cancellation=&stop; h.deadline=deadline; h.timed=configuration.timeout && timeout_policy!=1;
        for (;;) {
            Job job{}; bool producer=false, pending=false;
            {
                std::lock_guard lock(selection);
                if (stop.load()) break;
                if (configuration.timeout && std::chrono::steady_clock::now() >= deadline && timeout_policy != 1) {
                    if (failure.empty() && timeout_policy != 2) failure="Concurrent block exceeded its timeout";
                    stop.store(true); break;
                }
                if (next < jobs.size()) { job=jobs[next++]; ++active_producers; producer=true; }
                else {
                    RuntimeGuard guard;
                    for (auto context : streams) {
                        auto queue = read_word(context,8);
                        if (read_word(queue,16)) { auto value=lymar_aot_channel_pop(queue); job={context,value,h.return_pointer}; break; }
                    }
                    pending = active_producers != 0;
                }
            }
            if (!job.context) {
                if (!pending) break;
                std::unique_lock lock(shared_heap().mutex);
                shared_heap().work_available.wait_for(lock,std::chrono::milliseconds(1));
                continue;
            }
            h.worker_error[0]=0;h.timed_out=false;
            h.pending_args={object_kind,job.kind,0};
            auto callback = reinterpret_cast<Word(*)(Word,Word)>(read_word(job.context,32));
            callback(job.context,job.item);
            const bool failed = h.worker_error[0]!=0;
            {
                RuntimeGuard guard;
                while (!h.invocations.empty()) lymar_aot_call_abort();
                while (h.active != parent_region) {
                    auto current=h.active, parent=h.regions.at(current).parent;
                    h.cleanup(current);h.regions.erase(current);h.active=parent;
                }
            }
            {
                std::lock_guard lock(selection);
                if (producer) --active_producers;
                if (failed && std::strcmp(h.worker_error,"Worker cancelled")!=0) {
                    if (h.timed_out) {
                        if (timeout_policy != 2 && failure.empty()) failure=h.worker_error;
                        stop.store(true);
                    } else {
                        if (policy != 2 && failure.empty()) failure=h.worker_error;
                        if (policy != 1) stop.store(true);
                    }
                }
                shared_heap().work_available.notify_all();
            }
        }
        h.cancellation=nullptr;
    };
    // Join every started worker even if thread creation fails. No detached work
    // may outlive captured regions, borrowed references or the scheduler.
    try {
        const auto count=std::min<Word>(configuration.cores,std::max(size_t(1),jobs.size()+streams.size()));
        for (Word index=0; index<count; ++index) workers.emplace_back(worker);
    } catch (...) {
        stop.store(true); for(auto& thread:workers) thread.join(); throw;
    }
    for(auto& thread:workers) thread.join();
    if (!failure.empty()) {
        if (heap().worker) {
            if (!heap().worker_error[0]) std::snprintf(heap().worker_error,sizeof(heap().worker_error),"%s",failure.c_str());
        } else { std::fprintf(stderr,"%s\n",failure.c_str()); std::exit(1); }
    }
}

// These adapters validate canonical native objects before any foreign access.
const char* lymar_aot_ffi_string(uint64_t value) {
    RuntimeGuard guard;
    lymar_aot_string_receiver(value, object_kind);
    auto& record=heap().allocations.at(value);
    auto length=read_word(value,8);
    if(length>=record.size-24 || reinterpret_cast<const char*>(value+24)[length]!=0)
        throw std::runtime_error("Invalid FFI string terminator");
    return reinterpret_cast<const char*>(value+24);
}
uint64_t lymar_aot_ffi_list_size(uint64_t value) {
    RuntimeGuard guard;
    auto found=heap().allocations.find(value);
    if(found==heap().allocations.end() || found->second.dictionary || found->second.size<32 || read_word(value)!=1)
        throw std::runtime_error("FFI arguments require a list");
    auto length=read_word(value,16), capacity=read_word(value,24), data=read_word(value,8);
    auto storage=heap().allocations.find(data);
    if(length>capacity || capacity>SIZE_MAX/8 || (length && (storage==heap().allocations.end() || storage->second.size<length*8)))
        throw std::runtime_error("Invalid FFI argument list storage");
    return length;
}
uint64_t lymar_aot_ffi_list_item(uint64_t value,uint64_t index) {
    RuntimeGuard guard;
    if(index>=lymar_aot_ffi_list_size(value)) throw std::runtime_error("FFI argument index out of bounds");
    return read_word(read_word(value,8),index*8);
}
uint64_t lymar_aot_ffi_list_kind(uint64_t value,uint64_t index) {
    RuntimeGuard guard;
    if(index>=lymar_aot_ffi_list_size(value)) throw std::runtime_error("FFI argument index out of bounds");
    auto found=heap().shadow.find(read_word(value,8)+index*8);
    return found==heap().shadow.end()?0:found->second;
}
uint64_t lymar_aot_ffi_pointer(uint64_t value,uint64_t kind) {
    RuntimeGuard guard;
    if(lymar_aot_is_nil(value,kind) || kind==boolean_kind) return 0;
    if(!kind) return value; // Explicit unsafe integer addresses remain supported.
    auto found=heap().containing(value);
    if(found==heap().allocations.end()) throw std::runtime_error("Expired foreign pointer");
    if(found->second.raw_memory) return value;
    if(found->first!=value) throw std::runtime_error("Invalid foreign object address");
    if(found->second.size>=16 && read_word(value)==13) return read_word(value,8);
    if(found->second.size>=40 && read_word(value)==15) {
        auto address=lymar_aot_frame_field_address(value,0);
        auto flag=heap().shadow.find(address);
        return lymar_aot_ffi_pointer(read_word(address),flag==heap().shadow.end()?0:flag->second);
    }
    if(found->second.size>=24 && read_word(value)==11) return value+24;
    throw std::runtime_error("Invalid foreign pointer object");
}
uint64_t lymar_aot_ffi_wrap(uint64_t pointer) {
    RuntimeGuard guard;
    if(!pointer) return lymar_aot_nil();
    auto value=lymar_aot_alloc(16); Word header[2]={13,pointer};
    std::memcpy(reinterpret_cast<void*>(value),header,sizeof(header)); return value;
}
void lymar_aot_ffi_invalidate(uint64_t pointer) {
    RuntimeGuard guard;
    for(auto& [value,record]:heap().allocations)
        if(!record.raw_memory && !record.dictionary && record.size==16 && read_word(value)==13 && read_word(value,8)==pointer) {
            Word zero=0;std::memcpy(reinterpret_cast<void*>(value+8),&zero,8);
        }
}
void lymar_aot_ffi_result_kind(uint64_t kind) { RuntimeGuard guard;heap().return_pointer=kind; }

uint64_t lymar_aot_ffi_kind(uint64_t, uint64_t kind) {return kind;}
uint64_t lymar_aot_ffi_infer_type(uint64_t value,uint64_t kind) {
    RuntimeGuard guard;
    if(kind!=object_kind || lymar_aot_is_nil(value,kind)) return 6;
    auto found=heap().allocations.find(value);
    if(found!=heap().allocations.end() && !found->second.raw_memory && !found->second.dictionary && found->second.size>=16) {
        auto type=read_word(value);
        if(type==9) return 9;
        if(type>=5 && type<=8) return 6;
    }
    return 10;
}

uint64_t lymar_aot_ffi_list_integer(uint64_t value,uint64_t index) {
    RuntimeGuard guard;
    return lymar_aot_to_integer(lymar_aot_ffi_list_item(value,index),lymar_aot_ffi_list_kind(value,index));
}

double lymar_aot_clock() {
    static const auto start_time = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - start_time;
    return diff.count();
}

uint64_t lymar_aot_time() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t lymar_aot_numeric_binary(uint64_t left,uint64_t right,uint64_t operation,uint64_t left_kind,uint64_t right_kind) {
    RuntimeGuard guard;
    auto& h=heap();
    auto number=[&](__int128 value) {
        if(value>=INT64_MIN && value<=INT64_MAX) {h.return_pointer=0;return static_cast<Word>(value);}
        auto object=lymar_aot_alloc(32);Word type=7;
        std::memcpy(reinterpret_cast<void*>(object),&type,8);std::memcpy(reinterpret_cast<void*>(object+16),&value,16);
        h.return_pointer=object_kind;return object;
    };
    auto a=integer_number(left,left_kind),b=integer_number(right,right_kind);
    if(a && b) {
        __int128 value=0;bool valid=false;
        if(operation<=1) valid=LM::Memory::add_integer(*a,*b,value,operation==1);
        else if(operation==2) valid=!__builtin_mul_overflow(*a,*b,&value);
        else throw std::runtime_error("Invalid numeric operation");
        if(valid) return number(value);
        h.return_pointer=object_kind;return lymar_aot_nil();
    }
    auto floating=[&](Word value,Word kind) {auto found=h.allocations.find(value);return kind==object_kind && found!=h.allocations.end() && !found->second.raw_memory && !found->second.dictionary && found->second.size>=16 && read_word(value)==9;};
    if((a || floating(left,left_kind)) && (b || floating(right,right_kind))) {
        auto x=lymar_aot_to_float(left,left_kind),y=lymar_aot_to_float(right,right_kind);
        auto value=lymar_aot_box_float(operation==0?x+y:operation==1?x-y:x*y);h.return_pointer=object_kind;return value;
    }
    if(operation==0 && left_kind==object_kind && right_kind==object_kind) {
        auto* x=string_data(left);auto* y=string_data(right);
        if(x && y) {
            auto nx=read_word(left,8),ny=read_word(right,8);
            if(nx>SIZE_MAX-25-ny) throw std::overflow_error("String concatenation size overflow");
            auto value=lymar_aot_alloc(25+nx+ny);Word header[3]={11,nx+ny,nx+ny};std::memcpy(reinterpret_cast<void*>(value),header,24);
            std::memcpy(reinterpret_cast<void*>(value+24),x,nx);std::memcpy(reinterpret_cast<void*>(value+24+nx),y,ny+1);h.return_pointer=object_kind;return value;
        }
        auto list=[&](Word value) {auto found=h.allocations.find(value);return found!=h.allocations.end() && !found->second.raw_memory && !found->second.dictionary && found->second.size>=32 && read_word(value)==1;};
        if(list(left) && list(right)) {
            auto nx=lymar_aot_ffi_list_size(left),ny=lymar_aot_ffi_list_size(right);
            if(nx>SIZE_MAX/8-ny) throw std::overflow_error("List concatenation size overflow");
            auto count=nx+ny,storage=lymar_aot_alloc(std::max<Word>(8,count*8)),value=lymar_aot_alloc(32);
            Word header[4]={1,storage,count,count};std::memcpy(reinterpret_cast<void*>(value),header,32);lymar_aot_edge(value+8,storage,object_kind);
            for(Word index=0;index<count;++index) {auto source=index<nx?left:right,position=index<nx?index:index-nx;auto word=lymar_aot_ffi_list_item(source,position),kind=lymar_aot_ffi_list_kind(source,position);std::memcpy(reinterpret_cast<void*>(storage+8*index),&word,8);lymar_aot_edge(storage+8*index,word,kind);}
            h.return_pointer=object_kind;return value;
        }
    }
    h.return_pointer=object_kind;return lymar_aot_nil();
}

}

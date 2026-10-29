#include <windows.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcessA(NULL, argv[1], NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed %lu\n", GetLastError());
        return 1;
    }
    DEBUG_EVENT de;
    while (WaitForDebugEvent(&de, INFINITE)) {
        if (de.dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
            DWORD code = de.u.Exception.ExceptionRecord.ExceptionCode;
            PVOID addr = de.u.Exception.ExceptionRecord.ExceptionAddress;
            if (code != 0x80000003 && code != 0x40010006) {
                printf("EXCEPTION 0x%08lX at address %p\n", code, addr);
                if (code == EXCEPTION_ACCESS_VIOLATION) {
                    printf("Access violation %s address %p\n",
                        de.u.Exception.ExceptionRecord.ExceptionInformation[0] == 0 ? "reading" : "writing",
                        (void*)de.u.Exception.ExceptionRecord.ExceptionInformation[1]);
                    HANDLE hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_SUSPEND_RESUME, FALSE, de.dwThreadId);
                    if (hThread) {
                        CONTEXT ctx;
                        ctx.ContextFlags = CONTEXT_FULL;
                        if (GetThreadContext(hThread, &ctx)) {
                            printf("RAX=%016llx RBX=%016llx RCX=%016llx RDX=%016llx\n", ctx.Rax, ctx.Rbx, ctx.Rcx, ctx.Rdx);
                            printf("RSI=%016llx RDI=%016llx RBP=%016llx RSP=%016llx\n", ctx.Rsi, ctx.Rdi, ctx.Rbp, ctx.Rsp);
                            printf("R8 =%016llx R9 =%016llx R10=%016llx R11=%016llx\n", ctx.R8, ctx.R9, ctx.R10, ctx.R11);
                            printf("R12=%016llx R13=%016llx R14=%016llx R15=%016llx RIP=%016llx\n", ctx.R12, ctx.R13, ctx.R14, ctx.R15, ctx.Rip);
                        }
                        CloseHandle(hThread);
                    }
                }
            }
            ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_EXCEPTION_NOT_HANDLED);
        } else if (de.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
            printf("Process exited with code %lu\n", de.u.ExitProcess.dwExitCode);
            ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
            break;
        } else {
            ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
        }
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

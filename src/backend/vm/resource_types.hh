#ifndef LYMAR_BACKEND_VM_RESOURCE_TYPES_H
#define LYMAR_BACKEND_VM_RESOURCE_TYPES_H

#include <cstdint>

namespace LM {
namespace Backend {
namespace VM {

// NOTE: This enum must stay in sync with the mirror in src/lir/lir.hh
enum class ResourceType : uint32_t {
    FILE = 0,
    SOCKET = 1,
    WINDOW = 2,
    SURFACE = 3,
    PROCESS = 4,
    CHANNEL = 5,
    TIMER = 6,
    TASK = 7,
    LIBRARY = 8,
    STDOUT = 9,
    STDERR = 10,
    MEMORY = 11,
    ENTROPY = 12,
    DNS_RESOLVER = 13,
    UDP_SOCKET = 14,
    WEBSOCKET = 15,
    HASH_ENGINE = 16,
    GRAPHICS = 17,
    // Ambient machine/environment services: variables, working directory,
    // well-known directories, platform identity. See src/runtime/os_info.hh.
    OS = 18
};

enum class ResourceOperation : uint32_t {
    OPEN = 0,
    CLOSE = 1,
    READ = 2,
    WRITE = 3,
    SEND = 4,
    RECEIVE = 5,
    CONNECT = 6,
    DRAW_RECT = 7,
    DRAW_TEXT = 8,
    SPAWN = 9,
    POLL = 10,
    PUSH = 11,
    POP = 12,
    GET_STATE = 13,
    SET_STATE = 14,
    COPY = 15,
    FILL = 16,
    COMPARE = 17,
    ADD_PTR = 18,
    SUB_PTR = 19,
    PTR_DIFF = 20,
    ALIGN_PTR = 21,
    IS_ALIGNED = 22,
    BIND = 23,
    LISTEN = 24,
    ACCEPT = 25,
    RESOLVE = 26,
    SEND_TO = 27,
    RECV_FROM = 28,
    FLUSH = 29,
    MKDIR = 30,
    READDIR = 31,
    RENAME = 32,
    EXISTS = 33,
    DELETE = 34,
    HMAC = 35,
    DRAW_TRIANGLE = 36,
    APPLY_PIPELINE = 37,
    APPLY_BINDINGS = 38,
    DRAW = 39,
    MAKE_BUFFER = 40,
    MAKE_IMAGE = 41,
    MAKE_PIPELINE = 42,
    MAKE_BINDINGS = 43,
    END_PASS = 44,
    MEASURE_TEXT = 45,
    GET_FONT_METRICS = 46,
    READ_BYTES = 47,
    SIZE = 48,
    // ResourceType::OS operations.
    ENV_GET = 49,
    ENV_SET = 50,
    ENV_UNSET = 51,
    ENV_LIST = 52,
    CWD = 53,
    CHDIR = 54,
    HOME_DIR = 55,
    TEMP_DIR = 56,
    EXE_PATH = 57,
    OS_NAME = 58,
    ARCH = 59,
    HOSTNAME = 60,
    NUM_CPU = 61,
    // ResourceType::PROCESS operations. Child processes reuse SPAWN = 9.
    PROC_ARGS = 62,
    PROC_EXIT = 63,
    PROC_ID = 64,
    PROC_RSS = 65,
    PROC_PEAK_RSS = 66,
    PROC_COMMAND = 67
};

} // namespace VM
} // namespace Backend
} // namespace LM

#endif // LYMAR_BACKEND_VM_RESOURCE_TYPES_H

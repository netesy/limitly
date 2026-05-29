#ifndef LIMITLY_BACKEND_VM_RESOURCE_TYPES_H
#define LIMITLY_BACKEND_VM_RESOURCE_TYPES_H

#include <cstdint>

namespace LM {
namespace Backend {
namespace VM {

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
    STDERR = 10
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
    SET_STATE = 14
};

} // namespace VM
} // namespace Backend
} // namespace LM

#endif // LIMITLY_BACKEND_VM_RESOURCE_TYPES_H

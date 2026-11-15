#ifndef ENUM_FIXTURE_H
#define ENUM_FIXTURE_H
#include <stdint.h>

typedef enum VkResult {
    VK_SUCCESS = 0,
    VK_NOT_READY = 1,
    VK_TIMEOUT = 2,
    VK_ERROR_OUT_OF_HOST_MEMORY = -1,
} VkResult;

typedef enum VkStructureType {
    VK_STRUCTURE_TYPE_APPLICATION_INFO = 0,
    VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO = 29,
} VkStructureType;

typedef enum VkBufferUsageFlagBits {
    VK_BUFFER_USAGE_TRANSFER_SRC_BIT = 0x00000001,
    VK_BUFFER_USAGE_STORAGE_BUFFER_BIT = 0x00000040,
    VK_BUFFER_USAGE_ALL = 0x7FFFFFFF,
} VkBufferUsageFlagBits;

enum AnonFlags {
    FLAG_A = 4,
    FLAG_B = FLAG_A | 8,
    FLAG_C = (1 << 10) + FLAG_A,
};

int32_t enum_answer(void);

#endif

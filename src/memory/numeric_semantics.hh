#pragma once
namespace LM::Memory {
inline bool add_integer(__int128 left, __int128 right, __int128& result, bool subtract = false) {
    return !(subtract ? __builtin_sub_overflow(left, right, &result) : __builtin_add_overflow(left, right, &result));
}
}

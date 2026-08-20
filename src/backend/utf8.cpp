#include "utf8.hh"

#ifdef __cplusplus
extern "C" {
#endif

bool utf8_decode_next(const char* data, uint64_t len, uint64_t* offset, uint32_t* codepoint, uint8_t* bytes_consumed) {
    if (!data || !offset || !codepoint || !bytes_consumed) return false;
    uint64_t idx = *offset;
    if (idx >= len) return false;

    const uint8_t* udata = (const uint8_t*)data;
    uint8_t b0 = udata[idx];

    // 1-byte ASCII (0x00..0x7F)
    if (b0 <= 0x7F) {
        *codepoint = b0;
        *bytes_consumed = 1;
        *offset = idx + 1;
        return true;
    }

    // Invalid lead bytes: continuation bytes 0x80..0xBF, or 0xC0..0xC1 (overlong), or 0xF5..0xFF (> 0x10FFFF)
    if (b0 < 0xC2 || b0 > 0xF4) {
        *codepoint = 0xFFFD;
        *bytes_consumed = 1;
        *offset = idx + 1;
        return true;
    }

    // 2-byte sequence (0xC2..0xDF)
    if (b0 >= 0xC2 && b0 <= 0xDF) {
        if (idx + 1 >= len) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }
        uint8_t b1 = udata[idx + 1];
        if ((b1 & 0xC0) != 0x80) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }
        uint32_t cp = ((b0 & 0x1F) << 6) | (b1 & 0x3F);
        *codepoint = cp;
        *bytes_consumed = 2;
        *offset = idx + 2;
        return true;
    }

    // 3-byte sequence (0xE0..0xEF)
    if (b0 >= 0xE0 && b0 <= 0xEF) {
        if (idx + 2 >= len) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }
        uint8_t b1 = udata[idx + 1];
        uint8_t b2 = udata[idx + 2];

        // Check continuation bytes
        if ((b1 & 0xC0) != 0x80 || (b2 & 0xC0) != 0x80) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }

        // Overlong check for 0xE0 (must be >= 0x0800, so b1 >= 0xA0)
        if (b0 == 0xE0 && b1 < 0xA0) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }

        // Surrogate check for 0xED (must be < 0x0D800, so b1 <= 0x9F)
        if (b0 == 0xED && b1 > 0x9F) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }

        uint32_t cp = ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
        *codepoint = cp;
        *bytes_consumed = 3;
        *offset = idx + 3;
        return true;
    }

    // 4-byte sequence (0xF0..0xF4)
    if (b0 >= 0xF0 && b0 <= 0xF4) {
        if (idx + 3 >= len) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }
        uint8_t b1 = udata[idx + 1];
        uint8_t b2 = udata[idx + 2];
        uint8_t b3 = udata[idx + 3];

        if ((b1 & 0xC0) != 0x80 || (b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }

        // Overlong check for 0xF0 (must be >= 0x10000, so b1 >= 0x90)
        if (b0 == 0xF0 && b1 < 0x90) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }

        // Out-of-range check for 0xF4 (must be <= 0x10FFFF, so b1 <= 0x8F)
        if (b0 == 0xF4 && b1 > 0x8F) {
            *codepoint = 0xFFFD;
            *bytes_consumed = 1;
            *offset = idx + 1;
            return true;
        }

        uint32_t cp = ((b0 & 0x07) << 18) | ((b1 & 0x3F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
        *codepoint = cp;
        *bytes_consumed = 4;
        *offset = idx + 4;
        return true;
    }

    *codepoint = 0xFFFD;
    *bytes_consumed = 1;
    *offset = idx + 1;
    return true;
}

bool utf8_validate(const char* data, uint64_t len) {
    if (!data) return false;
    uint64_t offset = 0;
    uint32_t cp = 0;
    uint8_t consumed = 0;

    while (offset < len) {
        uint64_t prev_offset = offset;
        if (!utf8_decode_next(data, len, &offset, &cp, &consumed)) break;
        if (cp == 0xFFFD && consumed == 1) {
            // Check if input was literally UTF-8 encoded U+FFFD (0xEF 0xBF 0xBD)
            if (prev_offset + 3 <= len &&
                (uint8_t)data[prev_offset] == 0xEF &&
                (uint8_t)data[prev_offset+1] == 0xBF &&
                (uint8_t)data[prev_offset+2] == 0xBD) {
                continue;
            }
            return false;
        }
    }
    return true;
}

uint8_t utf8_encode(uint32_t codepoint, char* out_buf) {
    if (!out_buf) return 0;
    uint8_t* buf = (uint8_t*)out_buf;

    if (codepoint <= 0x7F) {
        buf[0] = (uint8_t)codepoint;
        return 1;
    } else if (codepoint <= 0x7FF) {
        buf[0] = (uint8_t)(0xC0 | (codepoint >> 6));
        buf[1] = (uint8_t)(0x80 | (codepoint & 0x3F));
        return 2;
    } else if (codepoint <= 0xFFFF) {
        if (codepoint >= 0xD800 && codepoint <= 0xDFFF) return 0; // Surrogate prohibited
        buf[0] = (uint8_t)(0xE0 | (codepoint >> 12));
        buf[1] = (uint8_t)(0x80 | ((codepoint >> 6) & 0x3F));
        buf[2] = (uint8_t)(0x80 | (codepoint & 0x3F));
        return 3;
    } else if (codepoint <= 0x10FFFF) {
        buf[0] = (uint8_t)(0xF0 | (codepoint >> 18));
        buf[1] = (uint8_t)(0x80 | ((codepoint >> 12) & 0x3F));
        buf[2] = (uint8_t)(0x80 | ((codepoint >> 6) & 0x3F));
        buf[3] = (uint8_t)(0x80 | (codepoint & 0x3F));
        return 4;
    }
    return 0;
}

uint64_t utf8_codepoint_count(const char* data, uint64_t len) {
    if (!data) return 0;
    uint64_t offset = 0;
    uint64_t count = 0;
    uint32_t cp = 0;
    uint8_t consumed = 0;

    while (offset < len) {
        if (!utf8_decode_next(data, len, &offset, &cp, &consumed)) break;
        count++;
    }
    return count;
}

#ifdef __cplusplus
}
#endif

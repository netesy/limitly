#ifndef LIMITLY_BACKEND_UTF8_H
#define LIMITLY_BACKEND_UTF8_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Canonical UTF-8 Decoder & Encoder for Limitly

// Validates whether byte array [data, data+len) is strict valid UTF-8.
// Rejects overlong encodings, invalid continuation bytes, surrogates (0xD800..0xDFFF), and values > 0x10FFFF.
bool utf8_validate(const char* data, uint64_t len);

// Decodes next UTF-8 codepoint starting at *offset.
// On success, sets *codepoint to decoded codepoint, *bytes_consumed to sequence length (1..4), and advances *offset.
// On malformed sequence, sets *codepoint to 0xFFFD (replacement char), *bytes_consumed to 1, and advances *offset by 1.
// Returns false if *offset >= len (end of text).
bool utf8_decode_next(const char* data, uint64_t len, uint64_t* offset, uint32_t* codepoint, uint8_t* bytes_consumed);

// Encodes a single Unicode codepoint into out_buf (out_buf must have at least 4 bytes capacity).
// Returns number of bytes written (1..4), or 0 if codepoint is invalid.
uint8_t utf8_encode(uint32_t codepoint, char* out_buf);

// Counts the number of Unicode codepoints in [data, data+len).
uint64_t utf8_codepoint_count(const char* data, uint64_t len);

#ifdef __cplusplus
}
#endif

#endif // LIMITLY_BACKEND_UTF8_H

#include "resource_manager.hh"
#include "../channel.hh"
#include "../fiber.hh"
#include "../../runtime/runtime.h"
#include "../../runtime/runtime_value.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>
#include <sstream>

// For getrandom(2) on Linux. Fall back to /dev/urandom otherwise.
#ifdef __linux__
#include <sys/random.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#else
#include <unistd.h>
#endif

namespace LM {
namespace Backend {
namespace VM {

// ===================== Value extraction helpers =====================

const char* register_value_to_cstr(RegisterValue val) {
    if (!IS_PTR(val)) return nullptr;
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
    if (!h) return nullptr;
    if (h->type_id == TYPE_BOX) {
        LmBox* box = (LmBox*)h;
        if (box->type == LM_BOX_STRING) return (const char*)box->value.as_ptr;
    }
    return nullptr;
}

int64_t register_value_to_i64(RegisterValue val) {
    if (is_integer(val)) return as_i64(val);
    if (IS_PTR(val)) {
        ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
        if (!h) return 0;
        if (h->type_id == TYPE_I64) return ((ObjI64*)h)->value;
        if (h->type_id == TYPE_U64) return (int64_t)((ObjU64*)h)->value;
        if (h->type_id == TYPE_BOX) {
            LmBox* box = (LmBox*)h;
            if (box->type == LM_BOX_INT) return box->value.as_int;
        }
    }
    return 0;
}

void* register_value_to_ptr(RegisterValue val) {
    if (!IS_PTR(val)) {
        if (is_integer(val)) return (void*)(uintptr_t)as_i64(val);
        return nullptr;
    }
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(val);
    if (!h) return nullptr;
    if (h->type_id == TYPE_FOREIGN_PTR) return ((ObjForeignPtr*)h)->ptr;
    if (h->type_id == TYPE_BOX) {
        LmBox* box = (LmBox*)h;
        if (box->type == LM_BOX_NULLPTR) return box->value.as_ptr;
    }
    return (void*)h;
}

namespace {

// Build a heap-allocated string box from a C-string.
RegisterValue make_string_value(const char* s) {
    if (!s) return VAL_NIL;
    LmBox* box = lm_box_string(s);
    return box ? BOX_PTR(box) : VAL_NIL;
}

RegisterValue make_i64(int64_t v) {
    ObjI64* obj = (ObjI64*)lm_alloc(sizeof(ObjI64));
    if (!obj) return VAL_NIL;
    obj->header.type_id = TYPE_I64;
    obj->value = v;
    return BOX_PTR(&obj->header);
}

// ===================== SHA-256 Implementation =====================

class SHA256 {
public:
    SHA256() { reset(); }

    void reset() {
        state_[0] = 0x6a09e667; state_[1] = 0xbb67ae85;
        state_[2] = 0x3c6ef372; state_[3] = 0xa54ff53a;
        state_[4] = 0x510e527f; state_[5] = 0x9b05688c;
        state_[6] = 0x1f83d9ab; state_[7] = 0x5be0cd19;
        buflen_ = 0; totlen_ = 0;
    }

    void update(const uint8_t* data, size_t len) {
        totlen_ += len;
        size_t i = 0;
        while (i < len) {
            size_t space = 64 - buflen_;
            size_t chunk = (len - i < space) ? (len - i) : space;
            std::memcpy(buf_ + buflen_, data + i, chunk);
            buflen_ += chunk;
            i += chunk;
            if (buflen_ == 64) {
                transform(buf_);
                buflen_ = 0;
            }
        }
    }

    std::string digest() {
        uint64_t total_bits = totlen_ * 8;
        uint8_t pad = 0x80;
        update(&pad, 1);
        pad = 0;
        while (buflen_ != 56) update(&pad, 1);
        uint8_t len_be[8];
        for (int i = 7; i >= 0; i--) {
            len_be[i] = (uint8_t)(total_bits & 0xFF);
            total_bits >>= 8;
        }
        update(len_be, 8);

        std::string result;
        result.reserve(64);
        for (int i = 0; i < 8; i++) {
            char hex[9];
            std::snprintf(hex, sizeof(hex), "%08x", (unsigned)state_[i]);
            result += hex;
        }
        return result;
    }

private:
    static constexpr uint32_t K[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };

    static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
    static uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    static uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
    static uint32_t ep0(uint32_t x) { return rotr(x,2) ^ rotr(x,13) ^ rotr(x,22); }
    static uint32_t ep1(uint32_t x) { return rotr(x,6) ^ rotr(x,11) ^ rotr(x,25); }
    static uint32_t sig0(uint32_t x) { return rotr(x,7) ^ rotr(x,18) ^ (x >> 3); }
    static uint32_t sig1(uint32_t x) { return rotr(x,17) ^ rotr(x,19) ^ (x >> 10); }

    void transform(const uint8_t block[64]) {
        uint32_t W[64];
        for (int i = 0; i < 16; i++) {
            W[i] = ((uint32_t)block[i*4] << 24) | ((uint32_t)block[i*4+1] << 16) |
                    ((uint32_t)block[i*4+2] << 8) | (uint32_t)block[i*4+3];
        }
        for (int i = 16; i < 64; i++) {
            W[i] = sig1(W[i-2]) + W[i-7] + sig0(W[i-15]) + W[i-16];
        }
        uint32_t a = state_[0], b = state_[1], c = state_[2], d = state_[3];
        uint32_t e = state_[4], f = state_[5], g = state_[6], h = state_[7];
        for (int i = 0; i < 64; i++) {
            uint32_t t1 = h + ep1(e) + ch(e,f,g) + K[i] + W[i];
            uint32_t t2 = ep0(a) + maj(a,b,c);
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        state_[0] += a; state_[1] += b; state_[2] += c; state_[3] += d;
        state_[4] += e; state_[5] += f; state_[6] += g; state_[7] += h;
    }

    uint32_t state_[8];
    uint8_t buf_[64];
    size_t buflen_;
    uint64_t totlen_;
};

// ===================== SHA-1 Implementation =====================

class SHA1 {
public:
    SHA1() { reset(); }
    void reset() {
        h0_=0x67452301; h1_=0xEFCDAB89; h2_=0x98BADCFE; h3_=0x10325476; h4_=0xC3D2E1F0;
        buflen_=0; totlen_=0;
    }
    void update(const uint8_t* data, size_t len) {
        totlen_ += len;
        size_t i = 0;
        while (i < len) {
            size_t space = 64 - buflen_;
            size_t chunk = (len - i < space) ? (len - i) : space;
            std::memcpy(buf_ + buflen_, data + i, chunk);
            buflen_ += chunk; i += chunk;
            if (buflen_ == 64) { transform(buf_); buflen_ = 0; }
        }
    }
    std::string digest() {
        uint64_t total_bits = totlen_ * 8;
        uint8_t pad = 0x80; update(&pad, 1); pad = 0;
        while (buflen_ != 56) update(&pad, 1);
        uint8_t len_be[8];
        for (int i = 7; i >= 0; i--) { len_be[i] = (uint8_t)(total_bits & 0xFF); total_bits >>= 8; }
        update(len_be, 8);
        char hex[41];
        std::snprintf(hex, sizeof(hex), "%08x%08x%08x%08x%08x", h0_, h1_, h2_, h3_, h4_);
        return std::string(hex);
    }
private:
    static uint32_t rotl(uint32_t x, int n) { return (x << n) | (x >> (32 - n)); }
    static uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    static uint32_t parity(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
    static uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
    void transform(const uint8_t block[64]) {
        uint32_t W[80];
        for (int i = 0; i < 16; i++)
            W[i] = ((uint32_t)block[i*4]<<24)|((uint32_t)block[i*4+1]<<16)|((uint32_t)block[i*4+2]<<8)|(uint32_t)block[i*4+3];
        for (int i = 16; i < 80; i++) W[i] = rotl(W[i-3]^W[i-8]^W[i-14]^W[i-16], 1);
        uint32_t a=h0_, b=h1_, c=h2_, d=h3_, e=h4_;
        for (int i = 0; i < 80; i++) {
            uint32_t f, k;
            if (i < 20)      { f = ch(b,c,d);     k = 0x5A827999; }
            else if (i < 40) { f = parity(b,c,d); k = 0x6ED9EBA1; }
            else if (i < 60) { f = maj(b,c,d);    k = 0x8F1BBCDC; }
            else              { f = parity(b,c,d); k = 0xCA62C1D6; }
            uint32_t t = rotl(a,5) + f + e + k + W[i];
            e = d; d = c; c = rotl(b,30); b = a; a = t;
        }
        h0_+=a; h1_+=b; h2_+=c; h3_+=d; h4_+=e;
    }
    uint32_t h0_, h1_, h2_, h3_, h4_;
    uint8_t buf_[64]; size_t buflen_; uint64_t totlen_;
};

// ===================== MD5 Implementation =====================

class MD5 {
public:
    MD5() { reset(); }
    void reset() { a0_=0x67452301; b0_=0xEFCDAB89; c0_=0x98BADCFE; d0_=0x10325476; buflen_=0; totlen_=0; }
    void update(const uint8_t* data, size_t len) {
        totlen_ += len;
        size_t i = 0;
        while (i < len) {
            size_t space = 64 - buflen_;
            size_t chunk = (len - i < space) ? (len - i) : space;
            std::memcpy(buf_ + buflen_, data + i, chunk);
            buflen_ += chunk; i += chunk;
            if (buflen_ == 64) { transform(buf_); buflen_ = 0; }
        }
    }
    std::string digest() {
        uint64_t total_bits = totlen_ * 8;
        uint8_t pad = 0x80; update(&pad, 1); pad = 0;
        while (buflen_ != 56) update(&pad, 1);
        // MD5 uses little-endian length
        uint8_t len_le[8] = {};
        uint64_t tb = total_bits;
        for (int i = 0; i < 8; i++) { len_le[i] = (uint8_t)(tb & 0xFF); tb >>= 8; }
        update(len_le, 8);
        char hex[33];
        std::snprintf(hex, sizeof(hex), "%08x%08x%08x%08x", a0_, b0_, c0_, d0_);
        return std::string(hex);
    }
private:
    static uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); }
    static uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & ~z); }
    static uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
    static uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | ~z); }
    static uint32_t rotl(uint32_t x, int n) { return (x << n) | (x >> (32 - n)); }

    static uint32_t T(int i) {
        static const uint32_t K[64] = {
            0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
            0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
            0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
            0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
            0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
            0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
            0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
            0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
        };
        return K[i];
    }

    void transform(const uint8_t block[64]) {
        uint32_t M[16];
        for (int i = 0; i < 16; i++)
            M[i] = (uint32_t)block[i*4] | ((uint32_t)block[i*4+1]<<8) |
                    ((uint32_t)block[i*4+2]<<16) | ((uint32_t)block[i*4+3]<<24);
        uint32_t a=a0_, b=b0_, c=c0_, d=d0_;
        for (int i = 0; i < 64; i++) {
            uint32_t f, g;
            if (i < 16)      { f = F(b,c,d); g = (uint32_t)i; }
            else if (i < 32) { f = G(b,c,d); g = (5*i+1) % 16; }
            else if (i < 48) { f = H(b,c,d); g = (3*i+5) % 16; }
            else              { f = I(b,c,d); g = (7*i) % 16; }
            f = f + a + T(i) + M[g];
            a = d; d = c; c = b; b = b + rotl(f, (i < 16 ? (i%4+1) : (i < 32 ? ((i%4)*3+5)%7+1 : i < 48 ? ((i%4)*3+3)%7+1 : (i%4)+1)));
        }
        // Recalculate s values properly
        a = a0_; b = b0_; c = c0_; d = d0_;
        for (int i = 0; i < 64; i++) {
            uint32_t f, g;
            if (i < 16)      { f = F(b,c,d); g = (uint32_t)i; }
            else if (i < 32) { f = G(b,c,d); g = (5*i+1) % 16; }
            else if (i < 48) { f = H(b,c,d); g = (3*i+5) % 16; }
            else              { f = I(b,c,d); g = (7*i) % 16; }
            uint32_t temp = a + f + T(i) + M[g];
            a = d; d = c; c = b;
            static const int s[64] = {
                7,12,17,22, 7,12,17,22, 7,12,17,22, 7,12,17,22,
                5, 9,14,20, 5, 9,14,20, 5, 9,14,20, 5, 9,14,20,
                4,11,16,23, 4,11,16,23, 4,11,16,23, 4,11,16,23,
                6,10,15,21, 6,10,15,21, 6,10,15,21, 6,10,15,21
            };
            b = b + rotl(temp, s[i]);
        }
        a0_ += a; b0_ += b; c0_ += c; d0_ += d;
    }
    uint32_t a0_, b0_, c0_, d0_;
    uint8_t buf_[64]; size_t buflen_; uint64_t totlen_;
};

// ===================== SHA-512 Implementation =====================

class SHA512 {
public:
    SHA512() { reset(); }
    void reset() {
        state_[0]=0x6a09e667f3bcc908ULL; state_[1]=0xbb67ae8584caa73bULL;
        state_[2]=0x3c6ef372fe94f82bULL; state_[3]=0xa54ff53a5f1d36f1ULL;
        state_[4]=0x510e527fade682d1ULL; state_[5]=0x9b05688c2b3e6c1fULL;
        state_[6]=0x1f83d9abfb41bd6bULL; state_[7]=0x5be0cd19137e2179ULL;
        buflen_=0; totlen_=0;
    }
    void update(const uint8_t* data, size_t len) {
        totlen_ += len;
        size_t i = 0;
        while (i < len) {
            size_t space = 128 - buflen_;
            size_t chunk = (len - i < space) ? (len - i) : space;
            std::memcpy(buf_ + buflen_, data + i, chunk);
            buflen_ += chunk; i += chunk;
            if (buflen_ == 128) { transform(buf_); buflen_ = 0; }
        }
    }
    std::string digest() {
        // For simplicity, pad to 128-byte blocks
        uint64_t total_bits_hi = (totlen_ >> 61);
        uint64_t total_bits_lo = totlen_ * 8;
        uint8_t pad = 0x80; update(&pad, 1); pad = 0;
        while (buflen_ != 112) update(&pad, 1);
        uint8_t len_be[16];
        for (int i = 7; i >= 0; i--) { len_be[i] = (uint8_t)(total_bits_hi & 0xFF); total_bits_hi >>= 8; }
        for (int i = 15; i >= 8; i--) { len_be[i] = (uint8_t)(total_bits_lo & 0xFF); total_bits_lo >>= 8; }
        update(len_be, 16);
        std::string result;
        result.reserve(128);
        for (int i = 0; i < 8; i++) {
            char hex[17];
            std::snprintf(hex, sizeof(hex), "%016llx", (unsigned long long)state_[i]);
            result += hex;
        }
        return result;
    }
private:
    static constexpr uint64_t K[80] = {
        0x428a2f98d728ae22ULL,0x7137449123ef65cdULL,0xb5c0fbcfec4d3b2fULL,0xe9b5dba58189dbbcULL,
        0x3956c25bf348b538ULL,0x59f111f1b605d019ULL,0x923f82a4af194f9bULL,0xab1c5ed5da6d8118ULL,
        0xd807aa98a3030242ULL,0x12835b0145706fbeULL,0x243185be4ee4b28cULL,0x550c7dc3d5ffb4e2ULL,
        0x72be5d74f27b896fULL,0x80deb1fe3b1696b1ULL,0x9bdc06a725c71235ULL,0xc19bf174cf692694ULL,
        0xe49b69c19ef14ad2ULL,0xefbe4786384f25e3ULL,0x0fc19dc68b8cd5b5ULL,0x240ca1cc77ac9c65ULL,
        0x2de92c6f592b0275ULL,0x4a7484aa6ea6e483ULL,0x5cb0a9dcbd41fbd4ULL,0x76f988da831153b5ULL,
        0x983e5152ee66dfabULL,0xa831c66d2db43210ULL,0xb00327c898fb213fULL,0xbf597fc7beef0ee4ULL,
        0xc6e00bf33da88fc2ULL,0xd5a79147930aa725ULL,0x06ca6351e003826fULL,0x142929670a0e6e70ULL,
        0x27b70a8546d22ffcULL,0x2e1b21385c26c926ULL,0x4d2c6dfc5ac42aedULL,0x53380d139d95b3dfULL,
        0x650a73548baf63deULL,0x766a0abb3c77b2a8ULL,0x81c2c92e47edaee6ULL,0x92722c851482353bULL,
        0xa2bfe8a14cf10364ULL,0xa81a664bbc423001ULL,0xc24b8b70d0f89791ULL,0xc76c51a30654be30ULL,
        0xd192e819d6ef5218ULL,0xd69906245565a910ULL,0xf40e35855771202aULL,0x106aa07032bbd1b8ULL,
        0x19a4c116b8d2d0c8ULL,0x1e376c085141ab53ULL,0x2748774cdf8eeb99ULL,0x34b0bcb5e19b48a8ULL,
        0x391c0cb3c5c95a63ULL,0x4ed8aa4ae3418acbULL,0x5b9cca4f7763e373ULL,0x682e6ff3d6b2b8a3ULL,
        0x748f82ee5defb2fcULL,0x78a5636f43172f60ULL,0x84c87814a1f0ab72ULL,0x8cc702081a6439ecULL,
        0x90befffa23631e28ULL,0xa4506cebde82bde9ULL,0xbef9a3f7b2c67915ULL,0xc67178f2e372532bULL,
        0xca273eceea26619cULL,0xd186b8c721c0c207ULL,0xeada7dd6cde0eb1eULL,0xf57d4f7fee6ed178ULL,
        0x06f067aa72176fbaULL,0x0a637dc5a2c898a6ULL,0x113f9804bef90daeULL,0x1b710b35131c471bULL,
        0x28db77f523047d84ULL,0x32caab7b40c72493ULL,0x3c9ebe0a15c9bebcULL,0x431d67c49c100d4cULL,
        0x4cc5d4becb3e42b6ULL,0x597f299cfc657e2aULL,0x5fcb6fab3ad6faecULL,0x6c44198c4a475817ULL
    };
    static uint64_t rotr(uint64_t x, int n) { return (x >> n) | (x << (64 - n)); }
    static uint64_t ep0(uint64_t x) { return rotr(x,28)^rotr(x,34)^rotr(x,39); }
    static uint64_t ep1(uint64_t x) { return rotr(x,14)^rotr(x,18)^rotr(x,41); }
    static uint64_t sig0(uint64_t x) { return rotr(x,1)^rotr(x,8)^(x>>7); }
    static uint64_t sig1(uint64_t x) { return rotr(x,19)^rotr(x,61)^(x>>6); }
    static uint64_t ch(uint64_t x, uint64_t y, uint64_t z) { return (x&y)^(~x&z); }
    static uint64_t maj(uint64_t x, uint64_t y, uint64_t z) { return (x&y)^(x&z)^(y&z); }

    void transform(const uint8_t block[128]) {
        uint64_t W[80];
        for (int i = 0; i < 16; i++)
            W[i] = ((uint64_t)block[i*8]<<56)|((uint64_t)block[i*8+1]<<48)|((uint64_t)block[i*8+2]<<40)|
                    ((uint64_t)block[i*8+3]<<32)|((uint64_t)block[i*8+4]<<24)|((uint64_t)block[i*8+5]<<16)|
                    ((uint64_t)block[i*8+6]<<8)|(uint64_t)block[i*8+7];
        for (int i = 16; i < 80; i++) W[i] = sig1(W[i-2]) + W[i-7] + sig0(W[i-15]) + W[i-16];
        uint64_t a=state_[0],b=state_[1],c=state_[2],d=state_[3];
        uint64_t e=state_[4],f=state_[5],g=state_[6],h=state_[7];
        for (int i = 0; i < 80; i++) {
            uint64_t t1 = h + ep1(e) + ch(e,f,g) + K[i] + W[i];
            uint64_t t2 = ep0(a) + maj(a,b,c);
            h=g; g=f; f=e; e=d+t1; d=c; c=b; b=a; a=t1+t2;
        }
        state_[0]+=a; state_[1]+=b; state_[2]+=c; state_[3]+=d;
        state_[4]+=e; state_[5]+=f; state_[6]+=g; state_[7]+=h;
    }
    uint64_t state_[8];
    uint8_t buf_[128]; size_t buflen_; uint64_t totlen_;
};

// ===================== Concrete resources =====================

// ----- FILE -----
class FileResource : public Resource {
public:
    FileResource() = default;
    ~FileResource() override { if (fp_) { std::fclose(fp_); fp_ = nullptr; } }

    ResourceType getType() const override { return ResourceType::FILE; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*context*/) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                if (fp_) { std::fclose(fp_); fp_ = nullptr; }
                const char* path = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                const char* mode = args.size() > 1 ? register_value_to_cstr(args[1]) : nullptr;
                if (!path || !mode) return VAL_FALSE;
                fp_ = std::fopen(path, mode);
                return fp_ ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::CLOSE: {
                if (fp_) { std::fclose(fp_); fp_ = nullptr; }
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                if (!fp_) return VAL_NIL;
                long cur = std::ftell(fp_);
                if (cur < 0) return VAL_NIL;
                if (std::fseek(fp_, 0, SEEK_END) != 0) return VAL_NIL;
                long end = std::ftell(fp_);
                if (end < 0) return VAL_NIL;
                size_t n = (size_t)(end - cur);
                if (std::fseek(fp_, cur, SEEK_SET) != 0) return VAL_NIL;
                std::vector<char> buf(n + 1, '\0');
                size_t rd = n > 0 ? std::fread(buf.data(), 1, n, fp_) : 0;
                buf[rd] = '\0';
                return make_string_value(buf.data());
            }
            case ResourceOperation::WRITE: {
                if (!fp_) return VAL_FALSE;
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data) return VAL_FALSE;
                size_t len = std::strlen(data);
                size_t w = std::fwrite(data, 1, len, fp_);
                std::fflush(fp_);
                return (w == len) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::POLL: {
                return fp_ ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
    }

private:
    FILE* fp_ = nullptr;
};

// ----- STDOUT / STDERR -----
class StdoutResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::STDOUT; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::WRITE) {
            const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
            if (!data) return VAL_FALSE;
            std::fputs(data, stdout);
            std::fflush(stdout);
            return VAL_TRUE;
        }
        if (op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) return VAL_TRUE;
        return VAL_NIL;
    }
};

class StderrResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::STDERR; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::WRITE) {
            const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
            if (!data) return VAL_FALSE;
            std::fputs(data, stderr);
            std::fflush(stderr);
            return VAL_TRUE;
        }
        if (op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) return VAL_TRUE;
        return VAL_NIL;
    }
};

// ----- SOCKET (TCP, extended with BIND/LISTEN/ACCEPT) -----
class SocketResource : public Resource {
public:
    SocketResource() {
#ifdef __linux__
        fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
        if (fd_ >= 0) {
            int opt = 1;
            ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        }
#else
        fd_ = -1;
#endif
    }
    // Adopt an existing fd (used after accept)
    explicit SocketResource(int fd) : fd_(fd) {}
    ~SocketResource() override {
#ifdef __linux__
        if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
#endif
    }
    ResourceType getType() const override { return ResourceType::SOCKET; }
    int getFd() const { return fd_; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
#ifdef __linux__
        switch (op) {
            case ResourceOperation::CONNECT: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                if (!host || port <= 0 || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (::inet_pton(AF_INET, host, &addr.sin_addr) <= 0) return VAL_FALSE;
                return (::connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::SEND: {
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data || fd_ < 0) return VAL_FALSE;
                size_t len = std::strlen(data);
                ssize_t s = ::send(fd_, data, len, MSG_NOSIGNAL);
                return (s >= 0 && (size_t)s == len) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::RECEIVE: {
                if (fd_ < 0) return VAL_NIL;
                char buf[65536];
                ssize_t r = ::recv(fd_, buf, sizeof(buf) - 1, 0);
                if (r <= 0) return VAL_NIL;
                buf[r] = '\0';
                return make_string_value(buf);
            }
            case ResourceOperation::BIND: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : "0.0.0.0";
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                if (port <= 0 || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                ::inet_pton(AF_INET, host, &addr.sin_addr);
                return (::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::LISTEN: {
                int64_t backlog = args.size() > 0 ? register_value_to_i64(args[0]) : 128;
                if (fd_ < 0) return VAL_FALSE;
                return (::listen(fd_, (int)backlog) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::ACCEPT: {
                if (fd_ < 0) return VAL_NIL;
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = ::accept(fd_, (struct sockaddr*)&client_addr, &client_len);
                if (client_fd < 0) return VAL_NIL;
                return make_i64((int64_t)client_fd);
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
                return VAL_TRUE;
            }
            case ResourceOperation::POLL: {
                if (fd_ < 0) return VAL_FALSE;
                struct pollfd pfd;
                pfd.fd = fd_;
                pfd.events = POLLIN;
                int ret = ::poll(&pfd, 1, 0);
                return (ret > 0) ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
#else
        return VAL_NIL;
#endif
    }
private:
    int fd_ = -1;
};

// ----- UDP SOCKET -----
class UdpSocketResource : public Resource {
public:
    UdpSocketResource() {
#ifdef __linux__
        fd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
        if (fd_ >= 0) {
            int opt = 1;
            ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        }
#else
        fd_ = -1;
#endif
    }
    ~UdpSocketResource() override {
#ifdef __linux__
        if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
#endif
    }
    ResourceType getType() const override { return ResourceType::UDP_SOCKET; }

    static bool parse_addr(const char* host, int64_t port, struct sockaddr_in* out) {
        std::memset(out, 0, sizeof(*out));
        out->sin_family = AF_INET;
        out->sin_port = htons((uint16_t)port);
        if (!host || std::strlen(host) == 0) {
            out->sin_addr.s_addr = INADDR_ANY;
            return true;
        }
        return (::inet_pton(AF_INET, host, &out->sin_addr) > 0);
    }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
#ifdef __linux__
        switch (op) {
            case ResourceOperation::BIND: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : "0.0.0.0";
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                if (port <= 0 || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                if (!parse_addr(host, port, &addr)) return VAL_FALSE;
                return (::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) == 0) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::SEND_TO: {
                const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                int64_t port = args.size() > 1 ? register_value_to_i64(args[1]) : 0;
                const char* data = args.size() > 2 ? register_value_to_cstr(args[2]) : nullptr;
                if (!host || port <= 0 || !data || fd_ < 0) return VAL_FALSE;
                struct sockaddr_in addr;
                if (!parse_addr(host, port, &addr)) return VAL_FALSE;
                size_t len = std::strlen(data);
                ssize_t s = ::sendto(fd_, data, len, 0, (struct sockaddr*)&addr, sizeof(addr));
                return (s >= 0) ? make_i64((int64_t)s) : VAL_NIL;
            }
            case ResourceOperation::RECV_FROM: {
                if (fd_ < 0) return VAL_NIL;
                char buf[65536];
                struct sockaddr_in from_addr;
                socklen_t from_len = sizeof(from_addr);
                std::memset(&from_addr, 0, sizeof(from_addr));
                ssize_t r = ::recvfrom(fd_, buf, sizeof(buf) - 1, 0,
                                       (struct sockaddr*)&from_addr, &from_len);
                if (r <= 0) return VAL_NIL;
                buf[r] = '\0';
                char from_ip[INET_ADDRSTRLEN];
                ::inet_ntop(AF_INET, &from_addr.sin_addr, from_ip, sizeof(from_ip));
                int from_port = ntohs(from_addr.sin_port);
                // Return "ip:port\0data" format
                std::string result = std::string(from_ip) + ":" + std::to_string(from_port) + "\n" + buf;
                return make_string_value(result.c_str());
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
                return VAL_TRUE;
            }
            case ResourceOperation::POLL: {
                if (fd_ < 0) return VAL_FALSE;
                struct pollfd pfd;
                pfd.fd = fd_;
                pfd.events = POLLIN;
                int ret = ::poll(&pfd, 1, 0);
                return (ret > 0) ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
#else
        return VAL_NIL;
#endif
    }
private:
    int fd_ = -1;
};

// ----- DNS RESOLVER -----
class DnsResolverResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::DNS_RESOLVER; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::RESOLVE) {
            const char* host = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
            if (!host || std::strlen(host) == 0) return VAL_NIL;
#ifdef __linux__
            struct addrinfo hints, *res = nullptr;
            std::memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            int err = ::getaddrinfo(host, nullptr, &hints, &res);
            if (err != 0 || !res) return VAL_NIL;
            char ip[INET_ADDRSTRLEN];
            struct sockaddr_in* addr = (struct sockaddr_in*)res->ai_addr;
            ::inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));
            ::freeaddrinfo(res);
            return make_string_value(ip);
#else
            return VAL_NIL;
#endif
        }
        if (op == ResourceOperation::CLOSE) return VAL_TRUE;
        return VAL_NIL;
    }
};

// ----- WEBSOCKET -----
class WebSocketResource : public Resource {
public:
    WebSocketResource() : fd_(-1), state_(WS_CLOSED) {}
    explicit WebSocketResource(int fd) : fd_(fd), state_(WS_CONNECTED) {}
    ~WebSocketResource() override {
#ifdef __linux__
        if (fd_ >= 0) {
            if (state_ == WS_CONNECTED) send_close_frame();
            ::close(fd_);
            fd_ = -1;
        }
#endif
    }
    ResourceType getType() const override { return ResourceType::WEBSOCKET; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
#ifdef __linux__
        switch (op) {
            case ResourceOperation::CONNECT: {
                const char* url = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!url) return VAL_FALSE;
                // Parse ws://host:port/path
                std::string surl(url);
                std::string host, path;
                int port = 80;
                bool ssl = false;
                if (surl.substr(0, 6) == "wss://") { ssl = true; port = 443; }
                if (surl.substr(0, 3) == "ws://" || ssl) {
                    size_t start = ssl ? 6 : 5;
                    size_t slash = surl.find('/', start);
                    std::string hostport = (slash == std::string::npos) ? surl.substr(start) : surl.substr(start, slash - start);
                    path = (slash == std::string::npos) ? "/" : surl.substr(slash);
                    size_t colon = hostport.find(':');
                    if (colon != std::string::npos) {
                        host = hostport.substr(0, colon);
                        port = std::stoi(hostport.substr(colon + 1));
                    } else {
                        host = hostport;
                    }
                } else {
                    // Treat as host:port
                    size_t colon = surl.find(':');
                    if (colon != std::string::npos) {
                        host = surl.substr(0, colon);
                        port = std::stoi(surl.substr(colon + 1));
                    } else {
                        host = surl;
                    }
                    path = "/";
                }

                fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
                if (fd_ < 0) return VAL_FALSE;

                struct sockaddr_in addr;
                std::memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons((uint16_t)port);
                if (::inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
                    // Try DNS resolution
                    struct addrinfo hints, *res = nullptr;
                    std::memset(&hints, 0, sizeof(hints));
                    hints.ai_family = AF_INET;
                    if (::getaddrinfo(host.c_str(), nullptr, &hints, &res) != 0 || !res) {
                        ::close(fd_); fd_ = -1; return VAL_FALSE;
                    }
                    addr.sin_addr = ((struct sockaddr_in*)res->ai_addr)->sin_addr;
                    ::freeaddrinfo(res);
                }

                if (::connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
                    ::close(fd_); fd_ = -1; return VAL_FALSE;
                }

                // Send WebSocket upgrade request
                std::string key = generate_ws_key();
                std::string req = "GET " + path + " HTTP/1.1\r\n"
                    "Host: " + host + (port != 80 && port != 443 ? ":" + std::to_string(port) : "") + "\r\n"
                    "Upgrade: websocket\r\n"
                    "Connection: Upgrade\r\n"
                    "Sec-WebSocket-Key: " + key + "\r\n"
                    "Sec-WebSocket-Version: 13\r\n\r\n";
                ::send(fd_, req.c_str(), req.size(), 0);

                // Read response
                char resp[4096];
                ssize_t r = ::recv(fd_, resp, sizeof(resp) - 1, 0);
                if (r <= 0) { ::close(fd_); fd_ = -1; return VAL_FALSE; }
                resp[r] = '\0';
                std::string response(resp);

                // Check for 101 Switching Protocols
                if (response.find("101") == std::string::npos) {
                    ::close(fd_); fd_ = -1; return VAL_FALSE;
                }
                state_ = WS_CONNECTED;
                return VAL_TRUE;
            }
            case ResourceOperation::SEND: {
                if (state_ != WS_CONNECTED || fd_ < 0) return VAL_FALSE;
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data) return VAL_FALSE;
                return send_text_frame(data) ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::RECEIVE: {
                if (state_ != WS_CONNECTED || fd_ < 0) return VAL_NIL;
                return recv_frame();
            }
            case ResourceOperation::CLOSE: {
                if (fd_ >= 0) {
                    if (state_ == WS_CONNECTED) send_close_frame();
                    ::close(fd_);
                    fd_ = -1;
                    state_ = WS_CLOSED;
                }
                return VAL_TRUE;
            }
            case ResourceOperation::POLL: {
                if (fd_ < 0) return VAL_FALSE;
                struct pollfd pfd;
                pfd.fd = fd_;
                pfd.events = POLLIN;
                return (::poll(&pfd, 1, 0) > 0) ? VAL_TRUE : VAL_FALSE;
            }
            default:
                return VAL_NIL;
        }
#else
        return VAL_NIL;
#endif
    }

private:
    enum WsState { WS_CLOSED, WS_CONNECTING, WS_CONNECTED };
    int fd_;
    WsState state_;

    static std::string generate_ws_key() {
        char buf[17];
#ifdef __linux__
        ::getrandom(buf, 16, 0);
#else
        for (int i = 0; i < 16; i++) buf[i] = (char)(std::rand() & 0xFF);
#endif
        // Base64 encode
        static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string result;
        for (int i = 0; i < 16; i += 3) {
            unsigned int n = (unsigned char)buf[i] << 16;
            if (i + 1 < 16) n |= (unsigned char)buf[i + 1] << 8;
            if (i + 2 < 16) n |= (unsigned char)buf[i + 2];
            result += b64[(n >> 18) & 0x3F];
            result += b64[(n >> 12) & 0x3F];
            result += (i + 1 < 16) ? b64[(n >> 6) & 0x3F] : '=';
            result += (i + 2 < 16) ? b64[n & 0x3F] : '=';
        }
        return result;
    }

    bool send_text_frame(const std::string& data) {
#ifdef __linux__
        std::vector<uint8_t> frame;
        frame.push_back(0x81); // FIN + text opcode
        size_t len = data.size();
        if (len < 126) {
            frame.push_back((uint8_t)len);
        } else if (len < 65536) {
            frame.push_back(126);
            frame.push_back((len >> 8) & 0xFF);
            frame.push_back(len & 0xFF);
        } else {
            frame.push_back(127);
            for (int i = 56; i >= 0; i -= 8) frame.push_back((len >> i) & 0xFF);
        }
        frame.insert(frame.end(), data.begin(), data.end());
        return ::send(fd_, frame.data(), frame.size(), 0) == (ssize_t)frame.size();
#else
        return false;
#endif
    }

    void send_close_frame() {
#ifdef __linux__
        uint8_t close_frame[] = {0x88, 0x00};
        ::send(fd_, close_frame, 2, 0);
#endif
    }

    RegisterValue recv_frame() {
#ifdef __linux__
        uint8_t header[2];
        ssize_t r = ::recv(fd_, header, 2, MSG_WAITALL);
        if (r < 2) return VAL_NIL;

        bool fin = (header[0] & 0x80) != 0;
        uint8_t opcode = header[0] & 0x0F;
        bool masked = (header[1] & 0x80) != 0;
        uint64_t payload_len = header[1] & 0x7F;

        if (payload_len == 126) {
            uint8_t ext[2];
            if (::recv(fd_, ext, 2, MSG_WAITALL) < 2) return VAL_NIL;
            payload_len = ((uint64_t)ext[0] << 8) | ext[1];
        } else if (payload_len == 127) {
            uint8_t ext[8];
            if (::recv(fd_, ext, 8, MSG_WAITALL) < 8) return VAL_NIL;
            payload_len = 0;
            for (int i = 0; i < 8; i++) payload_len = (payload_len << 8) | ext[i];
        }

        uint8_t mask_key[4] = {};
        if (masked) {
            if (::recv(fd_, mask_key, 4, MSG_WAITALL) < 4) return VAL_NIL;
        }

        std::vector<uint8_t> payload(payload_len);
        if (payload_len > 0) {
            size_t total = 0;
            while (total < payload_len) {
                ssize_t n = ::recv(fd_, payload.data() + total, payload_len - total, 0);
                if (n <= 0) return VAL_NIL;
                total += (size_t)n;
            }
        }

        if (masked) {
            for (size_t i = 0; i < payload_len; i++) {
                payload[i] ^= mask_key[i % 4];
            }
        }

        // Handle close frame
        if (opcode == 0x8) {
            state_ = WS_CLOSED;
            send_close_frame();
            return VAL_NIL;
        }

        // Handle ping
        if (opcode == 0x9) {
            // Send pong
            std::vector<uint8_t> pong = {0x8A, (uint8_t)(payload_len < 126 ? payload_len : 126)};
            if (payload_len >= 126) { pong.push_back(0); pong.push_back(0); }
            pong.insert(pong.end(), payload.begin(), payload.end());
            ::send(fd_, pong.data(), pong.size(), 0);
            return recv_frame(); // Continue reading
        }

        std::string result(payload.begin(), payload.end());
        return make_string_value(result.c_str());
#else
        return VAL_NIL;
#endif
    }
};

// ----- HASH ENGINE -----
class HashEngineResource : public Resource {
public:
    HashEngineResource() : algorithm_("sha256") {}
    ResourceType getType() const override { return ResourceType::HASH_ENGINE; }

    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                const char* algo = args.size() > 0 ? register_value_to_cstr(args[0]) : "sha256";
                if (!algo) return VAL_FALSE;
                algorithm_ = algo;
                // Reset the appropriate hasher
                if (algorithm_ == "sha256") sha256_.reset();
                else if (algorithm_ == "sha512") sha512_.reset();
                else if (algorithm_ == "sha1") sha1_.reset();
                else if (algorithm_ == "md5") md5_.reset();
                else return VAL_FALSE;
                return VAL_TRUE;
            }
            case ResourceOperation::WRITE: {
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data) return VAL_FALSE;
                size_t len = std::strlen(data);
                if (algorithm_ == "sha256") sha256_.update((const uint8_t*)data, len);
                else if (algorithm_ == "sha512") sha512_.update((const uint8_t*)data, len);
                else if (algorithm_ == "sha1") sha1_.update((const uint8_t*)data, len);
                else if (algorithm_ == "md5") md5_.update((const uint8_t*)data, len);
                else return VAL_FALSE;
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                std::string digest;
                if (algorithm_ == "sha256") digest = sha256_.digest();
                else if (algorithm_ == "sha512") digest = sha512_.digest();
                else if (algorithm_ == "sha1") digest = sha1_.digest();
                else if (algorithm_ == "md5") digest = md5_.digest();
                else return VAL_NIL;
                return make_string_value(digest.c_str());
            }
            case ResourceOperation::CLOSE:
                return VAL_TRUE;
            default:
                return VAL_NIL;
        }
    }

private:
    std::string algorithm_;
    SHA256 sha256_;
    SHA512 sha512_;
    SHA1 sha1_;
    MD5 md5_;
};

// ----- CHANNEL -----
class ChannelResource : public Resource {
public:
    explicit ChannelResource(size_t capacity = 1024) : channel_(capacity) {}
    ResourceType getType() const override { return ResourceType::CHANNEL; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* context) override {
        Fiber* fiber = static_cast<Fiber*>(context);
        switch (op) {
            case ResourceOperation::SEND:
            case ResourceOperation::PUSH:
                channel_.send(args.empty() ? VAL_NIL : args[0], fiber);
                return VAL_TRUE;
            case ResourceOperation::RECEIVE:
            case ResourceOperation::POP:
                return channel_.recv(fiber);
            case ResourceOperation::POLL: {
                RegisterValue out = VAL_NIL;
                return channel_.poll(out) ? out : VAL_NIL;
            }
            case ResourceOperation::CLOSE:
                channel_.close();
                return VAL_TRUE;
            default:
                return VAL_NIL;
        }
    }
private:
    LM::Backend::Channel channel_;
};

// ----- MEMORY -----
class MemoryResource : public Resource {
public:
    explicit MemoryResource(size_t size) {
        if (size > 0) {
            ptr_ = std::malloc(size);
            size_ = ptr_ ? size : 0;
        }
    }
    ~MemoryResource() override {
        if (ptr_) { std::free(ptr_); ptr_ = nullptr; size_ = 0; }
    }
    ResourceType getType() const override { return ResourceType::MEMORY; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        switch (op) {
            case ResourceOperation::OPEN: {
                size_t new_size = (size_t)register_value_to_i64(args.empty() ? make_i64((int64_t)size_) : args[0]);
                if (ptr_) { std::free(ptr_); ptr_ = nullptr; }
                size_ = 0;
                if (new_size > 0) {
                    ptr_ = std::malloc(new_size);
                    if (ptr_) size_ = new_size;
                }
                return ptr_ ? VAL_TRUE : VAL_FALSE;
            }
            case ResourceOperation::WRITE: {
                const char* data = args.size() > 0 ? register_value_to_cstr(args[0]) : nullptr;
                if (!data || !ptr_) return VAL_FALSE;
                size_t len = std::strlen(data);
                if (len > size_) len = size_;
                std::memcpy(ptr_, data, len);
                return VAL_TRUE;
            }
            case ResourceOperation::READ: {
                if (!ptr_ || size_ == 0) return VAL_NIL;
                std::vector<char> buf(size_ + 1, '\0');
                std::memcpy(buf.data(), ptr_, size_);
                return make_string_value(buf.data());
            }
            case ResourceOperation::CLOSE: {
                if (ptr_) { std::free(ptr_); ptr_ = nullptr; size_ = 0; }
                return VAL_TRUE;
            }
            default:
                return VAL_NIL;
        }
    }
private:
    void* ptr_ = nullptr;
    size_t size_ = 0;
};

// ----- ENTROPY -----
class EntropyResource : public Resource {
public:
    ResourceType getType() const override { return ResourceType::ENTROPY; }
    RegisterValue call(ResourceOperation op, const std::vector<RegisterValue>& args, void* /*ctx*/) override {
        if (op == ResourceOperation::READ) {
            size_t want = (size_t)register_value_to_i64(args.empty() ? make_i64(32) : args[0]);
            if (want == 0) want = 32;
            if (want > 65536) want = 65536;
            std::vector<char> buf(want, '\0');
            fill_random(buf.data(), want);
            return make_string_value(std::string(buf.begin(), buf.end()).c_str());
        }
        if (op == ResourceOperation::WRITE || op == ResourceOperation::CLOSE || op == ResourceOperation::POLL) {
            return op == ResourceOperation::POLL ? VAL_TRUE : VAL_NIL;
        }
        return VAL_NIL;
    }
private:
    static void fill_random(char* out, size_t n) {
#ifdef __linux__
        ssize_t got = 0;
        while ((size_t)got < n) {
            ssize_t r = ::getrandom(out + got, n - (size_t)got, 0);
            if (r <= 0) break;
            got += r;
        }
        if ((size_t)got == n) return;
#endif
        FILE* f = std::fopen("/dev/urandom", "rb");
        if (f) {
            size_t rd = std::fread(out, 1, n, f);
            (void)rd;
            std::fclose(f);
            return;
        }
        for (size_t i = 0; i < n; ++i) out[i] = (char)(std::rand() & 0xFF);
    }
};

} // anonymous namespace

// ===================== ResourceManager =====================

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::~ResourceManager() {
    shutdown();
}

int64_t ResourceManager::create(ResourceType type, const std::vector<RegisterValue>& args) {
    std::lock_guard<std::mutex> lock(mutex_);

    std::unique_ptr<Resource> res;
    switch (type) {
        case ResourceType::FILE:
            res = std::make_unique<FileResource>();
            break;
        case ResourceType::STDOUT:
            res = std::make_unique<StdoutResource>();
            break;
        case ResourceType::STDERR:
            res = std::make_unique<StderrResource>();
            break;
        case ResourceType::SOCKET: {
            int fd = -1;
            if (!args.empty()) fd = (int)register_value_to_i64(args[0]);
            if (fd >= 0) {
                res = std::make_unique<SocketResource>(fd);
            } else {
                res = std::make_unique<SocketResource>();
            }
            break;
        }
        case ResourceType::CHANNEL: {
            size_t capacity = 1024;
            if (!args.empty()) {
                int64_t c = register_value_to_i64(args[0]);
                if (c > 0) capacity = (size_t)c;
            }
            res = std::make_unique<ChannelResource>(capacity);
            break;
        }
        case ResourceType::MEMORY: {
            size_t sz = 0;
            if (!args.empty()) {
                int64_t s = register_value_to_i64(args[0]);
                if (s > 0) sz = (size_t)s;
            }
            res = std::make_unique<MemoryResource>(sz);
            break;
        }
        case ResourceType::ENTROPY:
            res = std::make_unique<EntropyResource>();
            break;
        case ResourceType::DNS_RESOLVER:
            res = std::make_unique<DnsResolverResource>();
            break;
        case ResourceType::UDP_SOCKET:
            res = std::make_unique<UdpSocketResource>();
            break;
        case ResourceType::WEBSOCKET:
            res = std::make_unique<WebSocketResource>();
            break;
        case ResourceType::HASH_ENGINE:
            res = std::make_unique<HashEngineResource>();
            break;
        default:
            // WINDOW/SURFACE/PROCESS/TIMER/TASK/LIBRARY: not yet implemented.
            return -1;
    }

    int64_t id = next_id_++;
    resources_[id] = std::move(res);
    return id;
}

RegisterValue ResourceManager::call(int64_t id, ResourceOperation op, const std::vector<RegisterValue>& args, void* context) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = resources_.find(id);
    if (it == resources_.end()) {
        return VAL_NIL;
    }
    return it->second->call(op, args, context);
}

void ResourceManager::destroy(int64_t id) {
    std::lock_guard<std::mutex> lock(mutex_);
    resources_.erase(id);
}

void ResourceManager::shutdown() {
    std::lock_guard<std::mutex> lock(mutex_);
    resources_.clear();
}

} // namespace VM
} // namespace Backend
} // namespace LM
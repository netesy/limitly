// src/native/openssl_wrapper.c
//
// Native OpenSSL bridge for Limitly std.crypto and std.net.tls.
// Provides clean C-ABI exports callable via Limitly's FFI trampoline.

#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET socket_t;
#define CLOSE_SOCKET(s) closesocket(s)
#else
#define EXPORT __attribute__((visibility("default")))
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
typedef int socket_t;
#define CLOSE_SOCKET(s) close(s)
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR   (-1)
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#include <zlib.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int g_ssl_initialized = 0;

static void ensure_ssl_init(void) {
    if (g_ssl_initialized) return;
#if defined(_WIN32)
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
#else
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
#endif
    g_ssl_initialized = 1;
}

EXPORT int limitly_ssl_init(void) {
    ensure_ssl_init();
    return 1;
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void bytes_to_hex(const unsigned char* bytes, int len, char* out_hex) {
    static const char hex_digits[] = "0123456789abcdef";
    for (int i = 0; i < len; ++i) {
        out_hex[i * 2]     = hex_digits[(bytes[i] >> 4) & 0x0F];
        out_hex[i * 2 + 1] = hex_digits[bytes[i] & 0x0F];
    }
    out_hex[len * 2] = '\0';
}

static int hex_char_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int hex_to_bytes(const char* hex, unsigned char* out_bytes, int max_bytes) {
    if (!hex) return 0;
    int len = (int)strlen(hex);
    if (len % 2 != 0) return 0;
    int num_bytes = len / 2;
    if (num_bytes > max_bytes) return 0;
    for (int i = 0; i < num_bytes; ++i) {
        int h = hex_char_val(hex[i * 2]);
        int l = hex_char_val(hex[i * 2 + 1]);
        if (h < 0 || l < 0) return 0;
        out_bytes[i] = (unsigned char)((h << 4) | l);
    }
    return num_bytes;
}

static const EVP_MD* resolve_md(const char* algo) {
    if (!algo || strlen(algo) == 0) return EVP_sha256();
    if (strcmp(algo, "sha256") == 0 || strcmp(algo, "SHA256") == 0) return EVP_sha256();
    if (strcmp(algo, "sha512") == 0 || strcmp(algo, "SHA512") == 0) return EVP_sha512();
    if (strcmp(algo, "sha384") == 0 || strcmp(algo, "SHA384") == 0) return EVP_sha384();
    if (strcmp(algo, "sha1") == 0   || strcmp(algo, "SHA1") == 0)   return EVP_sha1();
    if (strcmp(algo, "md5") == 0    || strcmp(algo, "MD5") == 0)    return EVP_md5();
    return EVP_get_digestbyname(algo);
}

// ---------------------------------------------------------------------------
// 1. EVP Hashing (One-shot & Streaming)
// ---------------------------------------------------------------------------

EXPORT int crypto_hash(const char* algo, const unsigned char* data, int len, char* out_hex) {
    ensure_ssl_init();
    if (!data || !out_hex) return 0;
    const EVP_MD* md = resolve_md(algo);
    if (!md) return 0;

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) return 0;

    int ok = EVP_DigestInit_ex(ctx, md, NULL) &&
             EVP_DigestUpdate(ctx, data, (size_t)len) &&
             EVP_DigestFinal_ex(ctx, md_value, &md_len);
    EVP_MD_CTX_free(ctx);

    if (!ok) return 0;
    bytes_to_hex(md_value, (int)md_len, out_hex);
    return 1;
}

EXPORT void* crypto_hasher_create(const char* algo) {
    ensure_ssl_init();
    const EVP_MD* md = resolve_md(algo);
    if (!md) return NULL;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) return NULL;

    if (!EVP_DigestInit_ex(ctx, md, NULL)) {
        EVP_MD_CTX_free(ctx);
        return NULL;
    }
    return ctx;
}

EXPORT int crypto_hasher_update(void* ctx_ptr, const unsigned char* data, int len) {
    if (!ctx_ptr || !data || len < 0) return 0;
    EVP_MD_CTX* ctx = (EVP_MD_CTX*)ctx_ptr;
    return EVP_DigestUpdate(ctx, data, (size_t)len) == 1 ? 1 : 0;
}

EXPORT int crypto_hasher_final_hex(void* ctx_ptr, char* out_hex) {
    if (!ctx_ptr || !out_hex) return 0;
    EVP_MD_CTX* ctx = (EVP_MD_CTX*)ctx_ptr;

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;
    int ok = EVP_DigestFinal_ex(ctx, md_value, &md_len);
    EVP_MD_CTX_free(ctx);

    if (!ok) return 0;
    bytes_to_hex(md_value, (int)md_len, out_hex);
    return 1;
}

EXPORT void crypto_hasher_free(void* ctx_ptr) {
    if (ctx_ptr) {
        EVP_MD_CTX_free((EVP_MD_CTX*)ctx_ptr);
    }
}

// ---------------------------------------------------------------------------
// 2. HMAC
// ---------------------------------------------------------------------------

EXPORT int crypto_hmac(const char* algo,
                       const unsigned char* key, int key_len,
                       const unsigned char* data, int data_len,
                       char* out_hex) {
    ensure_ssl_init();
    if (!key || !data || !out_hex) return 0;
    const EVP_MD* md = resolve_md(algo);
    if (!md) return 0;

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    unsigned char* res = HMAC(md, key, key_len, data, (size_t)data_len, md_value, &md_len);
    if (!res) return 0;

    bytes_to_hex(md_value, (int)md_len, out_hex);
    return 1;
}

// ---------------------------------------------------------------------------
// 3. Secure Random
// ---------------------------------------------------------------------------

EXPORT int crypto_random_bytes(unsigned char* buf, int len) {
    ensure_ssl_init();
    if (!buf || len <= 0) return 0;
    return RAND_bytes(buf, len) == 1 ? 1 : 0;
}

EXPORT int crypto_random_hex(char* out_hex, int num_bytes) {
    ensure_ssl_init();
    if (!out_hex || num_bytes <= 0) return 0;
    unsigned char* buf = (unsigned char*)malloc((size_t)num_bytes);
    if (!buf) return 0;

    if (RAND_bytes(buf, num_bytes) != 1) {
        free(buf);
        return 0;
    }
    bytes_to_hex(buf, num_bytes, out_hex);
    free(buf);
    return 1;
}

// ---------------------------------------------------------------------------
// 4. AES-256-GCM (Authenticated Encryption with Associated Data)
// ---------------------------------------------------------------------------

EXPORT int crypto_aes_gcm_encrypt(const unsigned char* key, int key_len,
                                  const unsigned char* iv, int iv_len,
                                  const unsigned char* pt, int pt_len,
                                  const unsigned char* aad, int aad_len,
                                  unsigned char* ct_out,
                                  unsigned char* tag_out) {
    ensure_ssl_init();
    if (!key || !iv || !ct_out || !tag_out) return -1;
    if (key_len != 32) return -1; // AES-256 requires 32-byte key

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return -1;

    int out_len = 0;
    int total_len = 0;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) goto fail;
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL)) goto fail;
    if (!EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) goto fail;

    // Provide AAD if specified
    if (aad && aad_len > 0) {
        if (!EVP_EncryptUpdate(ctx, NULL, &out_len, aad, aad_len)) goto fail;
    }

    // Encrypt plaintext
    if (pt && pt_len > 0) {
        if (!EVP_EncryptUpdate(ctx, ct_out, &out_len, pt, pt_len)) goto fail;
        total_len += out_len;
    }

    // Finalize
    if (!EVP_EncryptFinal_ex(ctx, ct_out + total_len, &out_len)) goto fail;
    total_len += out_len;

    // Extract 16-byte authentication tag
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag_out)) goto fail;

    EVP_CIPHER_CTX_free(ctx);
    return total_len;

fail:
    EVP_CIPHER_CTX_free(ctx);
    return -1;
}

EXPORT int crypto_aes_gcm_decrypt(const unsigned char* key, int key_len,
                                  const unsigned char* iv, int iv_len,
                                  const unsigned char* ct, int ct_len,
                                  const unsigned char* aad, int aad_len,
                                  const unsigned char* tag,
                                  unsigned char* pt_out) {
    ensure_ssl_init();
    if (!key || !iv || !tag || !pt_out) return -1;
    if (key_len != 32) return -1;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return -1;

    int out_len = 0;
    int total_len = 0;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) goto fail;
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL)) goto fail;
    if (!EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) goto fail;

    // Provide AAD if specified
    if (aad && aad_len > 0) {
        if (!EVP_DecryptUpdate(ctx, NULL, &out_len, aad, aad_len)) goto fail;
    }

    // Decrypt ciphertext
    if (ct && ct_len > 0) {
        if (!EVP_DecryptUpdate(ctx, pt_out, &out_len, ct, ct_len)) goto fail;
        total_len += out_len;
    }

    // Set expected 16-byte authentication tag
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, (void*)tag)) goto fail;

    // Finalize — verifies authenticity tag!
    if (EVP_DecryptFinal_ex(ctx, pt_out + total_len, &out_len) <= 0) {
        // Tag mismatch / tampering!
        goto fail;
    }
    total_len += out_len;

    EVP_CIPHER_CTX_free(ctx);
    return total_len;

fail:
    EVP_CIPHER_CTX_free(ctx);
    return -1;
}

// ---------------------------------------------------------------------------
// 5. AES-256-CBC (PKCS#7 padded)
// ---------------------------------------------------------------------------

EXPORT int crypto_aes_cbc_encrypt(const unsigned char* key, int key_len,
                                  const unsigned char* iv,
                                  const unsigned char* pt, int pt_len,
                                  unsigned char* ct_out) {
    ensure_ssl_init();
    if (!key || !iv || !ct_out) return -1;
    if (key_len != 32) return -1;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return -1;

    int out_len = 0;
    int total_len = 0;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) goto fail;
    if (pt && pt_len > 0) {
        if (!EVP_EncryptUpdate(ctx, ct_out, &out_len, pt, pt_len)) goto fail;
        total_len += out_len;
    }
    if (!EVP_EncryptFinal_ex(ctx, ct_out + total_len, &out_len)) goto fail;
    total_len += out_len;

    EVP_CIPHER_CTX_free(ctx);
    return total_len;

fail:
    EVP_CIPHER_CTX_free(ctx);
    return -1;
}

EXPORT int crypto_aes_cbc_decrypt(const unsigned char* key, int key_len,
                                  const unsigned char* iv,
                                  const unsigned char* ct, int ct_len,
                                  unsigned char* pt_out) {
    ensure_ssl_init();
    if (!key || !iv || !pt_out || ct_len <= 0) return -1;
    if (key_len != 32) return -1;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return -1;

    int out_len = 0;
    int total_len = 0;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) goto fail;
    if (!EVP_DecryptUpdate(ctx, pt_out, &out_len, ct, ct_len)) goto fail;
    total_len += out_len;

    if (!EVP_DecryptFinal_ex(ctx, pt_out + total_len, &out_len)) goto fail;
    total_len += out_len;

    EVP_CIPHER_CTX_free(ctx);
    return total_len;

fail:
    EVP_CIPHER_CTX_free(ctx);
    return -1;
}

EXPORT int crypto_aes_gcm_encrypt_hex(const char* key_str,
                                      const char* iv_str,
                                      const char* pt_str, int pt_len,
                                      const char* aad_str, int aad_len,
                                      char* out_ct_hex,
                                      char* out_tag_hex) {
    if (!key_str || !iv_str || !out_ct_hex || !out_tag_hex) return -1;

    unsigned char key[32];
    int klen = (int)strlen(key_str);
    if (klen == 64) {
        if (hex_to_bytes(key_str, key, 32) != 32) return -1;
    } else if (klen == 32) {
        memcpy(key, key_str, 32);
    } else return -1;

    unsigned char iv[16];
    int ivlen = (int)strlen(iv_str);
    int actual_iv_len = 0;
    if (ivlen == 24 || ivlen == 32) {
        actual_iv_len = hex_to_bytes(iv_str, iv, 16);
        if (actual_iv_len <= 0) return -1;
    } else if (ivlen == 12 || ivlen == 16) {
        actual_iv_len = ivlen;
        memcpy(iv, iv_str, ivlen);
    } else return -1;

    if (pt_len < 0) pt_len = pt_str ? (int)strlen(pt_str) : 0;
    if (aad_len < 0) aad_len = aad_str ? (int)strlen(aad_str) : 0;

    unsigned char* ct_raw = pt_len > 0 ? (unsigned char*)malloc(pt_len) : NULL;
    unsigned char tag_raw[16];

    int enc_len = crypto_aes_gcm_encrypt(key, 32,
                                         iv, actual_iv_len,
                                         (const unsigned char*)pt_str, pt_len,
                                         (const unsigned char*)aad_str, aad_len,
                                         ct_raw, tag_raw);
    if (enc_len < 0) {
        if (ct_raw) free(ct_raw);
        return -1;
    }

    if (enc_len > 0 && ct_raw) {
        bytes_to_hex(ct_raw, enc_len, out_ct_hex);
        free(ct_raw);
    } else {
        out_ct_hex[0] = '\0';
    }

    bytes_to_hex(tag_raw, 16, out_tag_hex);
    return enc_len;
}

EXPORT int crypto_aes_gcm_decrypt_hex(const char* key_str,
                                      const char* iv_str,
                                      const char* ct_hex,
                                      const char* aad_str, int aad_len,
                                      const char* tag_hex,
                                      char* pt_out) {
    if (!key_str || !iv_str || !ct_hex || !tag_hex || !pt_out) return -1;

    unsigned char key[32];
    int klen = (int)strlen(key_str);
    if (klen == 64) {
        if (hex_to_bytes(key_str, key, 32) != 32) return -1;
    } else if (klen == 32) {
        memcpy(key, key_str, 32);
    } else return -1;

    unsigned char iv[16];
    int ivlen = (int)strlen(iv_str);
    int actual_iv_len = 0;
    if (ivlen == 24 || ivlen == 32) {
        actual_iv_len = hex_to_bytes(iv_str, iv, 16);
        if (actual_iv_len <= 0) return -1;
    } else if (ivlen == 12 || ivlen == 16) {
        actual_iv_len = ivlen;
        memcpy(iv, iv_str, ivlen);
    } else return -1;

    unsigned char tag_raw[16];
    int tlen = (int)strlen(tag_hex);
    if (tlen == 32) {
        if (hex_to_bytes(tag_hex, tag_raw, 16) != 16) return -1;
    } else if (tlen == 16) {
        memcpy(tag_raw, tag_hex, 16);
    } else return -1;

    int ct_hex_len = (int)strlen(ct_hex);
    int ct_raw_len = ct_hex_len / 2;
    unsigned char* ct_raw = ct_raw_len > 0 ? (unsigned char*)malloc(ct_raw_len) : NULL;
    if (ct_raw_len > 0) {
        if (hex_to_bytes(ct_hex, ct_raw, ct_raw_len) != ct_raw_len) {
            free(ct_raw);
            return -1;
        }
    }

    if (aad_len < 0) aad_len = aad_str ? (int)strlen(aad_str) : 0;

    int dec_len = crypto_aes_gcm_decrypt(key, 32,
                                         iv, actual_iv_len,
                                         ct_raw, ct_raw_len,
                                         (const unsigned char*)aad_str, aad_len,
                                         tag_raw,
                                         (unsigned char*)pt_out);
    if (ct_raw) free(ct_raw);
    if (dec_len < 0) return -1;
    pt_out[dec_len] = '\0';
    return dec_len;
}

EXPORT int crypto_aes_cbc_encrypt_hex(const char* key_str,
                                      const char* iv_str,
                                      const char* pt_str, int pt_len,
                                      char* out_ct_hex) {
    if (!key_str || !iv_str || !out_ct_hex) return -1;

    unsigned char key[32];
    int klen = (int)strlen(key_str);
    if (klen == 64) {
        if (hex_to_bytes(key_str, key, 32) != 32) return -1;
    } else if (klen == 32) {
        memcpy(key, key_str, 32);
    } else return -1;

    unsigned char iv[16];
    int ivlen = (int)strlen(iv_str);
    if (ivlen == 32) {
        if (hex_to_bytes(iv_str, iv, 16) != 16) return -1;
    } else if (ivlen == 16) {
        memcpy(iv, iv_str, 16);
    } else return -1;

    if (pt_len < 0) pt_len = pt_str ? (int)strlen(pt_str) : 0;
    int max_ct_len = pt_len + 32;
    unsigned char* ct_raw = (unsigned char*)malloc(max_ct_len);
    if (!ct_raw) return -1;

    int ct_len = crypto_aes_cbc_encrypt(key, 32, iv, (const unsigned char*)pt_str, pt_len, ct_raw);
    if (ct_len < 0) {
        free(ct_raw);
        return -1;
    }

    bytes_to_hex(ct_raw, ct_len, out_ct_hex);
    free(ct_raw);
    return ct_len;
}

EXPORT int crypto_aes_cbc_decrypt_hex(const char* key_str,
                                      const char* iv_str,
                                      const char* ct_hex,
                                      char* pt_out) {
    if (!key_str || !iv_str || !ct_hex || !pt_out) return -1;

    unsigned char key[32];
    int klen = (int)strlen(key_str);
    if (klen == 64) {
        if (hex_to_bytes(key_str, key, 32) != 32) return -1;
    } else if (klen == 32) {
        memcpy(key, key_str, 32);
    } else return -1;

    unsigned char iv[16];
    int ivlen = (int)strlen(iv_str);
    if (ivlen == 32) {
        if (hex_to_bytes(iv_str, iv, 16) != 16) return -1;
    } else if (ivlen == 16) {
        memcpy(iv, iv_str, 16);
    } else return -1;

    int ct_hex_len = (int)strlen(ct_hex);
    int ct_raw_len = ct_hex_len / 2;
    if (ct_raw_len <= 0) return -1;

    unsigned char* ct_raw = (unsigned char*)malloc(ct_raw_len);
    if (!ct_raw) return -1;
    if (hex_to_bytes(ct_hex, ct_raw, ct_raw_len) != ct_raw_len) {
        free(ct_raw);
        return -1;
    }

    int pt_len = crypto_aes_cbc_decrypt(key, 32, iv, ct_raw, ct_raw_len, (unsigned char*)pt_out);
    free(ct_raw);
    if (pt_len < 0) return -1;
    pt_out[pt_len] = '\0';
    return pt_len;
}

// ---------------------------------------------------------------------------
// 6. TLS Client Socket Connection & Data Transfer
// ---------------------------------------------------------------------------

typedef struct {
    socket_t fd;
    SSL_CTX* ctx;
    SSL*     ssl;
} LimitlyTLSSocket;

EXPORT void* tls_client_connect(const char* host, int port,
                                const char* sni,
                                int verify_peer,
                                const char* ca_file,
                                const char* cert_file,
                                const char* key_file,
                                int timeout_ms) {
    ensure_ssl_init();
    if (!host || port <= 0) return NULL;

    char port_str[16];
    snprintf(port_str, sizeof(port_str), "%d", port);

    struct addrinfo hints, *res = NULL, *rp = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port_str, &hints, &res) != 0) {
        return NULL;
    }

    socket_t sock_fd = INVALID_SOCKET;
    for (rp = res; rp != NULL; rp = rp->ai_next) {
        sock_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock_fd == INVALID_SOCKET) continue;

        if (connect(sock_fd, rp->ai_addr, (int)rp->ai_addrlen) == 0) {
            break; // Successfully connected!
        }
        CLOSE_SOCKET(sock_fd);
        sock_fd = INVALID_SOCKET;
    }
    freeaddrinfo(res);

    if (sock_fd == INVALID_SOCKET) {
        return NULL;
    }

    // Set socket timeout if requested
    if (timeout_ms > 0) {
#ifdef _WIN32
        DWORD tv = (DWORD)timeout_ms;
        setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
        setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv));
#else
        struct timeval tv;
        tv.tv_sec  = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;
        setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#endif
    }

    // Setup SSL Context
    const SSL_METHOD* method = TLS_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        CLOSE_SOCKET(sock_fd);
        return NULL;
    }

    // Minimum TLS version 1.2
    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);

    // CA Verification
    if (ca_file && strlen(ca_file) > 0) {
        SSL_CTX_load_verify_locations(ctx, ca_file, NULL);
    } else {
        SSL_CTX_set_default_verify_paths(ctx);
    }

    if (verify_peer) {
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    } else {
        SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
    }

    // Client certificate & key if specified
    if (cert_file && strlen(cert_file) > 0) {
        SSL_CTX_use_certificate_file(ctx, cert_file, SSL_FILETYPE_PEM);
    }
    if (key_file && strlen(key_file) > 0) {
        SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM);
    }

    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        SSL_CTX_free(ctx);
        CLOSE_SOCKET(sock_fd);
        return NULL;
    }

    // Server Name Indication (SNI)
    const char* server_name = (sni && strlen(sni) > 0) ? sni : host;
    SSL_set_tlsext_host_name(ssl, server_name);

    // Attach socket
    SSL_set_fd(ssl, (int)sock_fd);

    // Perform TLS handshake
    int ret = SSL_connect(ssl);
    if (ret <= 0) {
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        CLOSE_SOCKET(sock_fd);
        return NULL;
    }

    LimitlyTLSSocket* sock = (LimitlyTLSSocket*)malloc(sizeof(LimitlyTLSSocket));
    if (!sock) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        CLOSE_SOCKET(sock_fd);
        return NULL;
    }
    sock->fd  = sock_fd;
    sock->ctx = ctx;
    sock->ssl = ssl;
    return sock;
}

EXPORT int tls_write(void* sock_ptr, const unsigned char* data, int len) {
    if (!sock_ptr || !data || len <= 0) return 0;
    LimitlyTLSSocket* s = (LimitlyTLSSocket*)sock_ptr;
    return SSL_write(s->ssl, data, len);
}

EXPORT int tls_read(void* sock_ptr, unsigned char* buf, int max_len) {
    if (!sock_ptr || !buf || max_len <= 0) return 0;
    LimitlyTLSSocket* s = (LimitlyTLSSocket*)sock_ptr;
    return SSL_read(s->ssl, buf, max_len);
}

EXPORT void tls_close(void* sock_ptr) {
    if (!sock_ptr) return;
    LimitlyTLSSocket* s = (LimitlyTLSSocket*)sock_ptr;
    if (s->ssl) {
        SSL_shutdown(s->ssl);
        SSL_free(s->ssl);
    }
    if (s->ctx) {
        SSL_CTX_free(s->ctx);
    }
    if (s->fd != INVALID_SOCKET) {
        CLOSE_SOCKET(s->fd);
    }
    free(s);
}

EXPORT int tls_get_peer_cert(void* sock_ptr, char* out_buf, int max_len) {
    if (!sock_ptr || !out_buf || max_len <= 0) return 0;
    LimitlyTLSSocket* s = (LimitlyTLSSocket*)sock_ptr;
    X509* cert = SSL_get_peer_certificate(s->ssl);
    if (!cert) return 0;

    X509_NAME* subj = X509_get_subject_name(cert);
    if (subj) {
        X509_NAME_oneline(subj, out_buf, max_len);
    } else {
        out_buf[0] = '\0';
    }
    X509_free(cert);
    return 1;
}

// ---------------------------------------------------------------------------
// 7. Zlib Compression & Decompression (with Limits)
// ---------------------------------------------------------------------------

EXPORT int limitly_zlib_compress(const unsigned char* in_data, int in_len,
                                 unsigned char* out_data, int* out_len,
                                 int level) {
    if (!in_data || in_len < 0 || !out_data || !out_len) return -1;
    if (level < 0 || level > 9) level = Z_DEFAULT_COMPRESSION;

    uLongf dest_len = (uLongf)(*out_len);
    int res = compress2((Bytef*)out_data, &dest_len, (const Bytef*)in_data, (uLong)in_len, level);
    if (res != Z_OK) return -1;
    *out_len = (int)dest_len;
    return (int)dest_len;
}

EXPORT int limitly_zlib_decompress(const unsigned char* in_data, int in_len,
                                   unsigned char* out_data, int* out_len,
                                   int max_limit) {
    if (!in_data || in_len <= 0 || !out_data || !out_len) return -1;
    if (max_limit <= 0) max_limit = 10 * 1024 * 1024; // 10MB default limit

    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    strm.next_in  = (Bytef*)in_data;
    strm.avail_in = (uInt)in_len;

    // 15 + 32 enables automatic zlib or gzip header detection
    if (inflateInit2(&strm, 15 + 32) != Z_OK) {
        if (inflateInit(&strm) != Z_OK) return -1;
    }

    int total_decompressed = 0;
    int chunk_size = 64 * 1024;
    int status = Z_OK;

    while (status == Z_OK) {
        if (total_decompressed >= max_limit) {
            inflateEnd(&strm);
            return -2; // -2: Decompression limit exceeded
        }

        int remaining = max_limit - total_decompressed;
        int step = (remaining < chunk_size) ? remaining : chunk_size;

        strm.next_out  = out_data + total_decompressed;
        strm.avail_out = (uInt)step;

        status = inflate(&strm, Z_NO_FLUSH);

        int written = step - (int)strm.avail_out;
        total_decompressed += written;

        if (status == Z_STREAM_END) {
            break;
        }

        if (status != Z_OK && status != Z_BUF_ERROR) {
            inflateEnd(&strm);
            return -1; // Corrupted data
        }

        if (strm.avail_out == 0 && total_decompressed >= max_limit) {
            inflateEnd(&strm);
            return -2; // Limit exceeded
        }
    }

    inflateEnd(&strm);
    *out_len = total_decompressed;
    return total_decompressed;
}

EXPORT int limitly_zlib_compress_hex(const char* in_data, int in_len, int level, char* out_hex) {
    if (!in_data || in_len < 0 || !out_hex) return -1;
    uLong bound = compressBound((uLong)in_len);
    unsigned char* tmp = (unsigned char*)malloc(bound);
    if (!tmp) return -1;

    int out_len = (int)bound;
    int res = limitly_zlib_compress((const unsigned char*)in_data, in_len, tmp, &out_len, level);
    if (res < 0) {
        free(tmp);
        return -1;
    }

    bytes_to_hex(tmp, out_len, out_hex);
    free(tmp);
    return out_len;
}

EXPORT int limitly_zlib_decompress_hex(const char* in_hex, int max_limit, char* out_str, int* out_len) {
    if (!in_hex || !out_str || !out_len) return -1;
    int hex_len = (int)strlen(in_hex);
    int in_raw_len = hex_len / 2;
    if (in_raw_len <= 0) return -1;

    unsigned char* raw_in = (unsigned char*)malloc(in_raw_len);
    if (!raw_in) return -1;
    if (hex_to_bytes(in_hex, raw_in, in_raw_len) != in_raw_len) {
        free(raw_in);
        return -1;
    }

    int res = limitly_zlib_decompress(raw_in, in_raw_len, (unsigned char*)out_str, out_len, max_limit);
    free(raw_in);
    if (res >= 0) {
        out_str[*out_len] = '\0';
    }
    return res;
}

// ---------------------------------------------------------------------------
// 8. POSIX Regex Compilation & Matching
// ---------------------------------------------------------------------------

EXPORT void* limitly_regex_compile(const char* pattern, int flags) {
    if (!pattern) return NULL;
    int cflags = REG_EXTENDED;
    if (flags & 1) cflags |= REG_ICASE;
    if (flags & 2) cflags |= REG_NEWLINE;

    regex_t* preg = (regex_t*)malloc(sizeof(regex_t));
    if (!preg) return NULL;

    int err = regcomp(preg, pattern, cflags);
    if (err != 0) {
        free(preg);
        return NULL;
    }
    return preg;
}

EXPORT int limitly_regex_match(void* preg_ptr, const char* text, int start_offset, int* out_start, int* out_end) {
    if (!preg_ptr || !text || !out_start || !out_end) return -1;
    int text_len = (int)strlen(text);
    if (start_offset < 0 || start_offset > text_len) return 0;

    const char* target = text + start_offset;
    regmatch_t pmatch[1];
    regex_t* preg = (regex_t*)preg_ptr;

    int eflags = (start_offset > 0 ? REG_NOTBOL : 0);
    int err = regexec(preg, target, 1, pmatch, eflags);
    if (err == 0 && pmatch[0].rm_so != -1) {
        *out_start = start_offset + (int)pmatch[0].rm_so;
        *out_end   = start_offset + (int)pmatch[0].rm_eo;
        return 1;
    }
    return 0;
}

EXPORT void limitly_regex_free(void* preg_ptr) {
    if (!preg_ptr) return;
    regex_t* preg = (regex_t*)preg_ptr;
    regfree(preg);
    free(preg);
}



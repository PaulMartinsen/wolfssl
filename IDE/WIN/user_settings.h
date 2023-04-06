#ifndef _WIN_USER_SETTINGS_H_
#define _WIN_USER_SETTINGS_H_

/* Verify this is Windows */
#ifndef _WIN32
#error This user_settings.h header is only designed for Windows
#endif

// Currently creates link errors.
#include "../Wolf_Features.h"

#define USE_WOLFSSL_IO
#define HAVE_AESGCM
#define WOLFSSL_TLS13
#define HAVE_HKDF
#define HAVE_FFDHE_4096
#define WC_RSA_PSS
#define WOLFSSL_DTLS
#define WOLFSSL_DTLS13
#define WOLFSSL_SEND_HRR_COOKIE
#define WOLFSSL_DTLS_CID

// Enable things needed to decode SSL messages with wireshark. 
#define HAVE_SECRET_CALLBACK

// Enable support for post-handshake authentication in TLS 1.3
#define WOLFSSL_POST_HANDSHAKE_AUTH

// Enable key generation:
// https://www.wolfssl.com/documentation/manuals/wolfssl/chapter07.html#rsa-key-generation
#define WOLFSSL_KEY_GEN

// Enable certificate generation: 
// https://www.wolfssl.com/documentation/manuals/wolfssl/chapter07.html#certificate-generation
#define WOLFSSL_CERT_GEN

// Enable certificate request generation: 
// https://www.wolfssl.com/documentation/manuals/wolfssl/chapter07.html#certificate-signing-request-csr-generation
#define WOLFSSL_CERT_REQ

// Enable debugging and logging support
// https://www.wolfssl.com/documentation/manuals/wolfssl/chapter08.html
#define DEBUG_WOLFSSL

// Enable additional debugging during a TLS connection
// https://www.wolfssl.com/documentation/manuals/wolfssl/chapter02.html#wolfssl_debug_tls
//#define WOLFSSL_DEBUG_TLS

// Force callback set in wolfSSL_CTX_set_verify to be called every time (not just on failure)
// see: https://www.wolfssl.com/forums/post2349.html#p2349
#define WOLFSSL_ALWAYS_VERIFY_CB

// Support certificate extensions. If an unsupported or unknown extension that is marked as critical is found, 
// then an error message is returned, otherwise unsupported or unknown extensions found are ignored.
// see: https://www.wolfssl.com/documentation/manuals/wolfssl/chapter07.html#supported-certificate-extensions
#define WOLFSSL_CERT_EXT

// To support session resumption for TLSv1.3 
// https://www.wolfssl.com/documentation/manuals/wolfssl/group__IO.html#function-wolfssl_usesessionticket
#define HAVE_SESSION_TICKET

// for wolfSSL_get_sessionID (only needed for debugging in Lumos). 
//#define SESSION_CERTS

/* Configurations */
#if defined(HAVE_FIPS)
    /* FIPS */
    #define OPENSSL_EXTRA
    #define HAVE_THREAD_LS
    #define WOLFSSL_KEY_GEN
    #define HAVE_HASHDRBG
    #define WOLFSSL_SHA384
    #define WOLFSSL_SHA512
    #define NO_PSK
    #define NO_RC4
    #define NO_DSA
    #define NO_MD4

    #define GCM_NONCE_MID_SZ 12
#else
    /* Enables blinding mode, to prevent timing attacks */
    #define WC_RSA_BLINDING
    #define NO_MULTIBYTE_PRINT

    #if defined(WOLFSSL_LIB)
        /* The lib */
        #define OPENSSL_EXTRA
        #define WOLFSSL_RIPEMD
        #define NO_PSK
        #define HAVE_EXTENDED_MASTER
        #define WOLFSSL_SNIFFER
        #define HAVE_SECURE_RENEGOTIATION

        #define HAVE_AESGCM
        #define WOLFSSL_AESGCM_STREAM
        #define WOLFSSL_SHA384
        #define WOLFSSL_SHA512

        #define HAVE_SUPPORTED_CURVES
        #define HAVE_TLS_EXTENSIONS

        #define HAVE_ECC
        #define ECC_SHAMIR
        #define ECC_TIMING_RESISTANT

        #define WOLFSSL_SP_X86_64
        #define SP_INT_BITS  4096

        /* Optional Performance Speedups */
        #if 0
            /* AESNI on x64 */
            #ifdef _WIN64
                #define HAVE_INTEL_RDSEED
                #define WOLFSSL_AESNI
                #define HAVE_INTEL_AVX1
                #if 0
                    #define HAVE_INTEL_AVX2
                #endif
            #endif

            /* Single Precision Support for RSA/DH 1024/2048/3072 and
             * ECC P-256/P-384 */
            #define WOLFSSL_SP
            #define WOLFSSL_HAVE_SP_ECC
            #define WOLFSSL_HAVE_SP_DH
            #define WOLFSSL_HAVE_SP_RSA

            #ifdef _WIN64
                /* Old versions of MASM compiler do not recognize newer
                 * instructions. */
                #if 0
                    #define NO_AVX2_SUPPORT
                    #define NO_MOVBE_SUPPORT
                #endif
                #define WOLFSSL_SP_ASM
                #define WOLFSSL_SP_X86_64_ASM
            #endif
        #endif
    #else
        /* The servers and clients */
        #define OPENSSL_EXTRA
        #define NO_PSK
    #endif
#endif /* HAVE_FIPS */

#endif /* _WIN_USER_SETTINGS_H_ */

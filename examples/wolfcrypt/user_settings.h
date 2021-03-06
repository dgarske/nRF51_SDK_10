/* Custom user settings file written for NRF51 by wolfSSL */

#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* Platform */
/* ------------------------------------------------------------------------- */
#undef  WOLFSSL_NRF51
#define WOLFSSL_NRF51

#undef  WOLFCRYPT_ONLY
#define WOLFCRYPT_ONLY

#undef  WOLFSSL_GENERAL_ALIGNMENT
#define WOLFSSL_GENERAL_ALIGNMENT   4

#undef  SINGLE_THREADED
#define SINGLE_THREADED

#undef  WOLFSSL_SMALL_STACK
#define WOLFSSL_SMALL_STACK


/* ------------------------------------------------------------------------- */
/* Math Configuration */
/* ------------------------------------------------------------------------- */
#undef  CURVED25519_SMALL
#define CURVED25519_SMALL

#undef  CURVED25519_SMALL
#define CURVED25519_SMALL

#undef  USE_FAST_MATH
#define USE_FAST_MATH

#undef  TFM_TIMING_RESISTANT
#define TFM_TIMING_RESISTANT

#undef  NO_BIG_INT
#define NO_BIG_INT


/* ------------------------------------------------------------------------- */
/* Crypto */
/* ------------------------------------------------------------------------- */
/* Ed/Curve255519 */
#if 0
    #undef  HAVE_CURVE25519
    #define HAVE_CURVE25519

    #undef  HAVE_ED25519
    #define HAVE_ED25519

    #undef  WOLFSSL_SHA512
    #define WOLFSSL_SHA512

    #undef  USE_SLOW_SHA256
    #define USE_SLOW_SHA256
#endif

/* ECC */
#if 1
    #undef  HAVE_ECC
    #define HAVE_ECC

    /* Custom Curve Config */
    #undef  ECC_USER_CURVES
    #define ECC_USER_CURVES

    /* Enable only P-256 */
    #undef NO_ECC256

    /* Examples for enabling other curves */
    //#define HAVE_ECC192
    //#define HAVE_ECC224
    //#define HAVE_ECC384
    //#define HAVE_ECC521

    /* Optional ECC calculation method */
    /* Note: doubles heap usage, but slightly faster */
    #undef  ECC_SHAMIR
    #define ECC_SHAMIR

    /* Use TFM optimizations for ECC 256 */
    #undef  TFM_ECC256
    #define TFM_ECC256

    /* Reduces heap usage, but much slower */
    #undef  ECC_TIMING_RESISTANT
    #define ECC_TIMING_RESISTANT
#endif

/* AES */
#undef NO_AES
#if 1
    /* Enables nRF51 AES ECB Hardware for AES CCM Encrypt or AES Counter */
    #undef  WOLFSSL_NRF51_AES
    #define WOLFSSL_NRF51_AES

    /* AES 128-bit max */
    #undef  AES_MAX_KEY_SIZE
    #define AES_MAX_KEY_SIZE    128

    /* Disable AES Decrypt */
    #undef  NO_AES_DECRYPT
    #define NO_AES_DECRYPT

    /* AES Counter Mode */
    #undef  WOLFSSL_AES_COUNTER
    #define WOLFSSL_AES_COUNTER

    /* AES Direct */
    #undef  WOLFSSL_AES_DIRECT
    #define WOLFSSL_AES_DIRECT

    /* Disable AES CBC */
    #undef  NO_AES_CBC
    #define NO_AES_CBC
#else
    #define NO_AES
#endif


/* ------------------------------------------------------------------------- */
/* Benchmark / Test */
/* ------------------------------------------------------------------------- */
/* Use reduced benchmark / test sizes */
#undef  BENCH_EMBEDDED
#define BENCH_EMBEDDED

/* Use this to measure / print heap usage (comment out NO_WOLFSSL_MEMORY) */
#undef  USE_WOLFSSL_MEMORY
//#define USE_WOLFSSL_MEMORY
#undef  WOLFSSL_TRACK_MEMORY
//#define WOLFSSL_TRACK_MEMORY
#undef  NO_WOLFSSL_MEMORY
#define NO_WOLFSSL_MEMORY


/* ------------------------------------------------------------------------- */
/* RNG */
/* ------------------------------------------------------------------------- */
/* Use HW RNG Only */
#if 1
    #undef  WC_NO_HASHDRBG
    #define WC_NO_HASHDRBG

    /* Override P-RNG with HW RNG */
    #undef  CUSTOM_RAND_GENERATE_BLOCK
    #define CUSTOM_RAND_GENERATE_BLOCK  nrf51_random_generate

/* Use P-RNG + HW RNG (adds 8K) */
#else
    /* Use built-in P-RNG (SHA256 based) with HW RNG */
    #undef  HAVE_HASHDRBG
    #define HAVE_HASHDRBG
#endif


/* ------------------------------------------------------------------------- */
/* Disable Features */
/* ------------------------------------------------------------------------- */
#undef  NO_FILESYSTEM
#define NO_FILESYSTEM

#undef  NO_WRITEV
#define NO_WRITEV

#undef  NO_MAIN_DRIVER
#define NO_MAIN_DRIVER

#undef  NO_HMAC
#define NO_HMAC

#undef  NO_DSA
#define NO_DSA

#undef  NO_ERROR_STRINGS
#define NO_ERROR_STRINGS

#undef  NO_OLD_TLS
#define NO_OLD_TLS

#undef  NO_RSA
#define NO_RSA

#undef  NO_DH
#define NO_DH

#undef  NO_CERTS
#define NO_CERTS

#undef  NO_CODING
#define NO_CODING

#undef  NO_DES3
#define NO_DES3

#undef  NO_RC4
#define NO_RC4

#undef  NO_MD5
#define NO_MD5

#undef  NO_OLD_TLS
#define NO_OLD_TLS

#undef  NO_SHA
#define NO_SHA

#undef  NO_OLD_TLS
#define NO_OLD_TLS

#undef  NO_HC128
#define NO_HC128

#undef  NO_RABBIT
#define NO_RABBIT

#undef  NO_PSK
#define NO_PSK

#undef  NO_MD4
#define NO_MD4

#undef  NO_PWDBASED
#define NO_PWDBASED

#undef  NO_ASN_TIME
#define NO_ASN_TIME

/* Ignore ASN name constraints */
#undef  IGNORE_NAME_CONSTRAINTS
#define IGNORE_NAME_CONSTRAINTS


/* ------------------------------------------------------------------------- */
/* Port */
/* ------------------------------------------------------------------------- */
/* Include the nRF51 Port (this include needs to be at bottom) */
#include <wolfssl/wolfcrypt/port/nrf51.h>

/* Override Current Time */
/* Allows custom_time() function to be defined in port layer */
#define WOLFSSL_USER_CURRTIME


#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_USER_SETTINGS_H */

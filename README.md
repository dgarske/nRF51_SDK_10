# nRF51 wolfCrypt

This effort documents the porting effort for the wolfCrypt library on a Nordic nRF51422 (PCA10028 V1.1.0 devlopment board). The [GCC ARM compiler from Launchpad](https://launchpad.net/gcc-arm-embedded) is the compiler used. This reference is based on the Nordic nRF51_SDK_10.

Important Directories/Files

* wolfSSL: `/external/wolfssl` as a git submodule.
* wolfCrypt Example Project: `/examples/wolfcrypt`
* Makefile: `example\wolfcrypt\Makefile`
* wolfSSL Configuration: `examples/wolfcrypt/user_settings.h`


## Requirements

1. Port wolfCrypt to Nordic nRF51422 with < 10KB RAM and < 40Kb Flash.2. Enable wolfCrypt API’s for Curve255519 (shared secret), Ed255519 (verify), SHA512, AES Encrypt/Decrypt using Nordic AES HW and Nordic HW RNG. 3. Measure RAM (heap) and Flash usage.4. Cryptographic verification of Ed/Curve, SHA512, AES and RNG using our wolfCrypt tests.5. Example nRF51488 GCC ARM Makefile project demonstrating Ed/Curve255519, SHA512 and AES.6. Documentation of example project and wolfCrypt test results.

## Results
### ECC 256

#### Code Size

Test application total code size in bytes: 32,152

```
.TEXT
Random: 118
AES: 164
ASN: 596
SHA256: 1394
ECC: 5218
FastMath: 10300
TOTAL: 17790

.RODATA
SHA256: 256
ECC: 471
FastMath: 97
TOTAL: 824

GRAND TOTAL: 18614```

#### Test Results
```
SHA-256  test passed!
AES      test passed!
RANDOM   test passed!
ECC      test passed!
```
#### Benchmark Resutls
```
AES      25 kB took 0.274 seconds,    0.089 MB/s
SHA-256  25 kB took 0.190 seconds,    0.128 MB/s
ECC  256 key generation  3059.800 milliseconds, avg over 5 iterations
EC-DHE   key agreement   3014.000 milliseconds, avg over 5 iterations
EC-DSA   sign   time     3043.400 milliseconds, avg over 5 iterations
EC-DSA   verify time     6081.800 milliseconds, avg over 5 iterations
```
#### Heap Usage
Heap Peak: 2508 (4616 with ECC_SHAMIR, 1368 with ECC_TIMING_RESISTANT)
```
total   Allocs =       128
total   Bytes  =     28834
peak    Bytes  =      2508
current Bytes  =         0
```

### Ed255519/Curve255519

#### Code Size

Test application total code size in bytes: 19,400

```
.TEXT
Random: 118
AES: 164
SHA256: 1394
SHA512: 1428
Ed255519: 198
Curve255519: 620
FE/GE Math: 1648
TOTAL: 5570

.RODATA
SHA256: 256
SHA512: 640
Ed255519: 0
Curve255519: 19
FE/GE Math: 192
TOTAL: 1107

GRAND TOTAL: 6677```

#### Test Results
```
SHA-256  test passed!
SHA-512  test passed!
AES      test passed!
RANDOM   test passed!
CURVE25519 test passed!
ED25519  test passed!
```
#### Benchmark Results
```
AES      25 kB took 0.275 seconds,    0.089 MB/s
SHA-256  25 kB took 0.191 seconds,    0.128 MB/s
SHA-512  25 kB took 0.474 seconds,    0.052 MB/s
CURVE25519 256 key generation 5196.400 milliseconds, avg over 5 iterations
CURVE25519 key agreement      5180.600 milliseconds, avg over 5 iterations
ED25519  key generation  5238.600 milliseconds, avg over 5 iterations
ED25519  sign   time     5317.200 milliseconds, avg over 5 iterations
ED25519  verify time     10986.000 milliseconds, avg over 5 iterations
```

#### Heap Usage
Heap Peak: 336 bytes
```
total   Allocs =       132
total   Bytes  =     18400
peak    Bytes  =       336
current Bytes  =         0
```

## Building

`make wolfcrypt_bench`
`make wolfcrypt_test`

## Programming

Uses on-board J-Link and the Segger J-Link software. Use the `/components/toolchain/gcc/Makefile.posix` to modify the path.

`make flash.segger TARGET=wolfcrypt_bench`
`make flash.segger TARGET= wolfcrypt_test`

## Debugging

Run this from the examples/wolfcrypt:
`make run-debug.segger`

In another terminal do:
`/opt/gcc-arm-none-eabi/bin/arm-none-eabi-gdb _build_wolfcrypt_test/firmware.out`
`target remote localhost:9992`

### GDB Help
Set Breakpoint: `b main.c:102`
Reset Board: `mon reset`
Continue: `c`
Print variable: `print x`
Backtrace: `bt`

## Makefile

The wolfCrypt example project's Makefile is located at `/examples/wolfcrypt/Makefile`. The section for wolfSSL (wolfCrypt) is lines 137 to 174.

```
## ----------------------------------------------------------------------------- ##
## wolfSSL ##
## ----------------------------------------------------------------------------- ##
#wolfSSL source files
# core
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/random.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/logging.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/memory.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/wc_encrypt.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/wc_port.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/error.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/signature.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/hash.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/asn.c)
# crypto
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/aes.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/sha256.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/sha512.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/curve25519.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/ed25519.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/ecc.c)
# math libraries
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/tfm.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/integer.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/fe_low_mem.c)
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/ge_low_mem.c)
# port
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/src/port/nrf51.c)
#wolfSSL includes
INC_PATHS += -I$(abspath ../../external/wolfssl)
#wolfSSL preprocessor (use the user_settings.h)
CFLAGS += -DWOLFSSL_USER_SETTINGS

#wolfTest
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/test/test.c)
#wolfBenchmark
C_SOURCE_FILES += $(abspath ../../external/wolfssl/wolfcrypt/benchmark/benchmark.c)
## ----------------------------------------------------------------------------- ##
```

## Example for Cross-Compilation of wolfSSL as static library
You will need `gcc-arm-none-eabi/bin` in your path:
`export PATH="$PATH:/opt/gcc-arm-none-eabi/bin"`

You can adjust the install path by editing the prefix above.

To build wolfCrypt use this command from inside the wolfssl directory:

Ed/Curve 255519

```
./configure --prefix="`pwd`/../nRF51_SDK_10/external/wolfcrypt" --host=arm-none-eabi CC=gcc AR=ar --disable-shared --enable-cryptonly --enable-curve25519=small --enable-ed25519=small --enable-sha512 --enable-smallstack --disable-sha --disable-coding --disable-memory --disable-errorstrings --disable-rsa --disable-oldtls --disable-dh --disable-chacha --disable-poly1305 --disable-aes --disable-des3 --disable-md5 --disable-aesgcm --disable-asn --disable-hashdrbg --disable-crypttests --disable-sha256 CFLAGS="-Os -DNO_ASN_TIME -DIGNORE_NAME_CONSTRAINTS -DUSE_SLOW_SHA2 -DNO_HMAC"
```

ECC:

```
./configure --prefix="`pwd`/../nRF51_SDK_10/external/wolfcrypt" --host=arm-none-eabi CC=gcc AR=ar --disable-shared --enable-cryptonly --enable-smallstack --enable-ecc --disable-sha --disable-coding --disable-memory --disable-errorstrings --disable-rsa --disable-oldtls --disable-dh --disable-chacha --disable-poly1305 --disable-aes --disable-des3 --disable-md5 --disable-aesgcm --disable-asn --disable-hashdrbg --disable-crypttests CFLAGS="-Os -DNO_ASN_TIME -DIGNORE_NAME_CONSTRAINTS -DNO_ECC_SIGN -DNO_ECC_KEY_EXPORT -DUSE_SLOW_SHA2 -DNO_HMAC"
```

Then: `make && make install`


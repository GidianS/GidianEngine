#pragma once

#if defined(ANDROID) || defined(__ANDROID__)

#define GE_PLATFORM_ANDROID 1

#elif defined(linux) || defined(__linux) || defined(__linux__)

#define GE_PLATFORM_LINUX 1

#elif defined(_WIN32)

#define GE_PLATFORM_WINDOWS 1

#elif defined(__APPLE__)

#include <TargetConditionals.h>

#define GE_PLATFORM_APPLE 1

#if TARGET_OS_MAC

#define GE_PLATFORM_MACOS 1

#elif TARGET_OS_IOS

#define GE_PLATFORM_IOS 1

#else

#error Unsupported Apple platform.

#endif

#else

#error Unsupported target platform.

#endif

#if defined(GE_PLATFORM_ANDROID) || defined(GE_PLATFORM_LINUX) || defined(GE_PLATFORM_APPLE)

#define GE_PLATFORM_UNIX 1

#endif

#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__) || defined(_M_X64) || defined(_M_AMD64)

#define GE_PLATFORM_ARCH_X64 1

#elif defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(_M_IX86)

#define GE_PLATFORM_ARCH_X86 1

#elif defined(__arm__) || defined(_M_ARM)

#define GE_PLATFORM_ARCH_ARM32 1

#elif defined(__aarch64__) || defined(_M_ARM64)

#define GE_PLATFORM_ARCH_ARM64 1

#else

#error Unsupported CPU architecture.

#endif

#if defined(GE_PLATFORM_LINUX) || defined(GE_PLATFORM_WINDOWS) || defined(GE_PLATFORM_MACOS)

#define GE_PLATFORM_DESKTOP 1

#elif defined(GE_PLATFORM_ANDROID) || defined(GE_PLATFORM_IOS)

#define GE_PLATFORM_MOBILE 1

#endif

#if defined(GE_PLATFORM_ARCH_X64) || defined(GE_PLATFORM_ARCH_ARM64)

#define GE_PLATFORM_64BITS 1

#else

#define GE_PLATFORM_32BITS 1

#endif

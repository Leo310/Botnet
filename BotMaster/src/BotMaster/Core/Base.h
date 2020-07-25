#pragma once

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#error "x64 Builds are not supported!"
#else
	/* Windows x86 */
    #define BM_PLATFORM_WINDOWS
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define BM_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define BM_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define BM_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define BM_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef BM_DEBUG
#if defined(BM_PLATFORM_WINDOWS)
#define BM_DEBUGBREAK() __debugbreak()
#elif defined(BM_PLATFORM_LINUX)
#include <signal.h>
#define BM_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define BM_ENABLE_ASSERTS
#else
#define BM_DEBUGBREAK()
#endif

#include "Log.h"
// TODO: Make this macro able to take in no arguments except condition
#ifdef BM_ENABLE_ASSERTS
#define BM_ASSERT(x, ...) { if(!(x)) { BM_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BM_DEBUGBREAK(); } } static_assert(true, "semi-colon required after this macro")

#else
#define BM_ASSERT(x, ...)
#endif

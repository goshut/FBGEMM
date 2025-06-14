// D:/c_raw/marian-dev/src/3rd_party/fbgemm/src/fbgemm_mingw_patch.h

#ifndef FBGEMM_MINGW_PATCH_H
#define FBGEMM_MINGW_PATCH_H

// 仅在 Windows 且非 MSVC 编译器下（即 MinGW-w64）启用此补丁
#if defined(_WIN32) && !defined(_MSC_VER)

#include <stddef.h> // For size_t
// #include <malloc.h> // _aligned_malloc 的声明通常在这里，但我们只声明 posix_memalign

#ifdef __cplusplus
extern "C" { // 确保 C++ 编译器以 C 链接方式处理此函数
#endif

// 声明我们自定义的 posix_memalign 函数
// 这个函数将在 fbgemm_mingw_patch.cc 中实现
int posix_memalign(void** memptr, size_t alignment, size_t size);

#ifdef __cplusplus
}
#endif

#endif // _WIN32 && !_MSC_VER

#endif // FBGEMM_MINGW_PATCH_H

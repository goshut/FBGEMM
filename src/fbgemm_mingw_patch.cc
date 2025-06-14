// D:/c_raw/marian-dev/src/3rd_party/fbgemm/src/fbgemm_mingw_patch.cc

// 这个文件提供一个 posix_memalign 的实现，用于 MinGW-w64 (GCC on Windows) 环境。

#if defined(_WIN32) && !defined(_MSC_VER)

#include "fbgemm_mingw_patch.h" // <-- 添加这一行，包含我们自己的声明
#include <errno.h>    // For EINVAL, ENOMEM
#include <malloc.h>   // For _aligned_malloc, _aligned_free

// 模拟 posix_memalign 函数
// memptr: 指向分配内存的指针的指针
// alignment: 内存对齐字节数 (必须是2的幂，且是 sizeof(void*) 的倍数)
// size: 要分配的字节数
// 返回值: 0 表示成功，非0表示错误 (EINVAL 或 ENOMEM)
int posix_memalign(void** memptr, size_t alignment, size_t size) {
    // posix_memalign 要求 alignment 必须是 2 的幂，并且是 sizeof(void*) 的倍数。
    // _aligned_malloc 也有对齐要求，但通常更宽松。
    // 这里我们检查 posix_memalign 的严格要求。
    if (alignment % sizeof(void*) != 0 || (alignment & (alignment - 1)) != 0) {
        *memptr = NULL;
        return EINVAL; // Invalid argument
    }

    void* ptr = _aligned_malloc(size, alignment);
    if (ptr == NULL) {
        *memptr = NULL;
        return ENOMEM; // Out of memory
    }

    *memptr = ptr;
    return 0; // Success
}

#endif // _WIN32 && !_MSC_VER

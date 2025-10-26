#include <stdint.h>

static uintptr_t heap_base = 0;
static uintptr_t heap_top = 0;

void kmem_init(uintptr_t base, uintptr_t size) {
    heap_base = base;
    heap_top = base + size;
}

void* kmalloc(uint32_t bytes) {
    static uintptr_t cur = 0;
    if (cur == 0) cur = heap_base;
    if (cur + bytes > heap_top) return 0;
    void* r = (void*)cur;
    cur += bytes;
    return r;
}

/* examples/hello.c: the smallest bbcpu host. It places an x86-64 function in memory, tells bbcpu
 * that the memory is guest code, and calls it. Build: build.sh; run: out/hello. */
#include "cpu/bbcpu.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

/* What every host provides: the guest image's base (fault reports and recordings print offsets from
 * it; 0 when there is no image) and memory for guest stacks. */
uint64_t bb_image_base = 0;

void *runtime_low_map(size_t size, int prot) {
    void *memory = mmap(NULL, size, prot, MAP_ANON | MAP_PRIVATE, -1, 0);
    return memory == MAP_FAILED ? NULL : memory;
}

int main(void) {
    /* lea eax, [rdi + rsi]; ret */
    static const uint8_t code[] = {0x8d, 0x04, 0x37, 0xc3};
    uint8_t *guest = mmap(NULL, 0x4000, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (guest == MAP_FAILED) return 1;
    memcpy(guest, code, sizeof code);
    bbcpu_add_guest_code((uintptr_t)guest, 0x4000);
    const uint64_t args[2] = {40, 2};
    uint64_t result = bbcpu_call((uintptr_t)guest, 2, args);
    printf("guest returned %llu\n", (unsigned long long)result);
    return result == 42 ? 0 : 1;
}

#include <cstdint>

static uint8_t pmem[0x8000000] __attribute((aligned(4096))) = {};

uint32_t pmem_read(uint32_t pc) {
    return
}
#include <assert.h>

#include <cstdint>

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x8000000
#define PG_ALIGN __attribute((aligned(4096)))
#define FMT_PADDR "0x%08x"
#define FMT_WORD "0x%08x"
#define PMEM_LEFT ((paddr_t)CONFIG_MBASE)
#define PMEM_RIGHT ((paddr_t)CONFIG_MBASE + CONFIG_MSIZE - 1)

typedef uint32_t paddr_t;
typedef uint32_t word_t;

static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};

static inline word_t host_read(void *addr, int len) {
    switch (len) {
        case 1:
            return *(uint8_t *)addr;
        case 2:
            return *(uint16_t *)addr;
        case 4:
            return *(uint32_t *)addr;
        default:
            assert(0);
    }
}

static inline void host_write(void *addr, int len, word_t data) {
    switch (len) {
        case 1:
            *(uint8_t *)addr = data;
            return;
        case 2:
            *(uint16_t *)addr = data;
            return;
        case 4:
            *(uint32_t *)addr = data;
            return;
        default:
            assert(0);
    }
}

uint8_t *guest_to_host(paddr_t paddr) {
    return pmem + paddr - CONFIG_MBASE;
}
paddr_t host_to_guest(uint8_t *haddr) {
    return haddr - pmem + CONFIG_MBASE;
}

static word_t pmem_read(paddr_t addr, int len) {
    word_t ret = host_read(guest_to_host(addr), len);
    return ret;
}

static void pmem_write(paddr_t addr, int len, word_t data) {
    host_write(guest_to_host(addr), len, data);
}

/* 访存超出范围时报错 */
static void out_of_bound(paddr_t addr) {
    panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR
          ", " FMT_PADDR "] at pc = " FMT_WORD,
          addr, PMEM_LEFT, PMEM_RIGHT, cpu.pc);
}

/* 初始化物理内存，随机数是为了能暴露一些未初始化变量的问题 */
void init_mem() {
#if defined(CONFIG_PMEM_MALLOC)
    pmem = malloc(CONFIG_MSIZE);
    assert(pmem);
#endif
    IFDEF(CONFIG_MEM_RANDOM, memset(pmem, rand(), CONFIG_MSIZE));
    Log("physical memory area [" FMT_PADDR ", " FMT_PADDR "]", PMEM_LEFT,
        PMEM_RIGHT);
}

/* 读物理内存，一般都用这个封装好的，不用上面那两个 */
word_t paddr_read(paddr_t addr, int len) {
    if (likely(in_pmem(addr))) return pmem_read(addr, len);
    IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
    out_of_bound(addr);
    return 0;
}

/* 写物理内存，封装好的 */
void paddr_write(paddr_t addr, int len, word_t data) {
    if (likely(in_pmem(addr))) {
        pmem_write(addr, len, data);
        return;
    }
    IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return );
    out_of_bound(addr);
}

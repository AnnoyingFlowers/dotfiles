#include "paddr.h"

static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};

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
static inline bool in_pmem(paddr_t addr) {
    return addr - CONFIG_MBASE < CONFIG_MSIZE;
}
/* 访存超出范围时报错 */
static void out_of_bound(paddr_t addr, vaddr_t pc) {
    printf("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR
           ", " FMT_PADDR "] at pc = " FMT_WORD,
           addr, PMEM_LEFT, PMEM_RIGHT, pc);
}

/* 读物理内存，一般都用这个封装好的，不用上面那两个 */
word_t paddr_read(paddr_t addr, int len, vaddr_t pc) {
    if (likely(in_pmem(addr))) return pmem_read(addr, len);
    out_of_bound(addr, pc);
    return 0;
}

/* 写物理内存，封装好的 */
void paddr_write(paddr_t addr, int len, word_t data, vaddr_t pc) {
    if (likely(in_pmem(addr))) {
        pmem_write(addr, len, data);
        return;
    }
    out_of_bound(addr, pc);
}

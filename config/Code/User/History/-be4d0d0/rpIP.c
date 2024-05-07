/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 *PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 *KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 *NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <device/mmio.h>
#include <isa.h>
#include <memory/host.h>
#include <memory/paddr.h>

#if defined(CONFIG_PMEM_MALLOC)
static uint8_t *pmem = NULL;
#else  // CONFIG_PMEM_GARRAY
// 物理内存，本质是大数组，数组元素是1Byte
static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};
#endif

uint64_t g_nr_access_mem;

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
    g_nr_access_mem++;
    if (likely(in_pmem(addr))) return pmem_read(addr, len);
    IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
#ifdef CONFIG_MTRACE
    log_write("%s\n", _this->logbuf);
#endif
    out_of_bound(addr);
    return 0;
}

/* 写物理内存，封装好的 */
void paddr_write(paddr_t addr, int len, word_t data) {
    g_nr_access_mem++;
    if (likely(in_pmem(addr))) {
        pmem_write(addr, len, data);
        return;
    }
    IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return );
#ifdef CONFIG_MTRACE
#endif
    out_of_bound(addr);
}

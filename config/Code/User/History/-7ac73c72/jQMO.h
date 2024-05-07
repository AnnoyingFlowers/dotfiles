#include <assert.h>

#include <cstdint>
#include <iostream>

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x8000000
#define PG_ALIGN __attribute((aligned(4096)))
#define FMT_PADDR "0x%08x"
#define FMT_WORD "0x%08x"
#define PMEM_LEFT ((paddr_t)CONFIG_MBASE)
#define PMEM_RIGHT ((paddr_t)CONFIG_MBASE + CONFIG_MSIZE - 1)
#define likely(cond) __builtin_expect(cond, 1)

typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;
typedef uint32_t word_t;
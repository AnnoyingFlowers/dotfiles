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

#include "local-include/reg.h"

#include <isa.h>

const char *regs[] = {"$0", "ra", "sp",  "gp",  "tp", "t0", "t1", "t2",
                      "s0", "s1", "a0",  "a1",  "a2", "a3", "a4", "a5",
                      "a6", "a7", "s2",  "s3",  "s4", "s5", "s6", "s7",
                      "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

/* 打印所有寄存器状态（包括pc） */
void isa_reg_display() {
    // pc应该也算寄存器吧我猜...
    printf("pc\t" FMT_WORD "\t%u\n", cpu.pc, cpu.pc);
    for (int i = 0; i < MUXDEF(CONFIG_RVE, 16, 32); i++) {
        printf("%s\t" FMT_WORD "\t%u\n", reg_name(i), gpr(i), gpr(i));
    }
}

word_t isa_reg_str2val(const char *s, bool *success) {
    if (strcmp(s, "pc") == 0) {
        return cpu.pc;
    }
    int i;
    for (i = 0; i < MUXDEF(CONFIG_RVE, 16, 32); i++) {
        if (strcmp(s, reg_name(i)) == 0) {
            return gpr(i);
        }
    }
    if (i == MUXDEF(CONFIG_RVE, 16, 32)) {
        *success = false;
        Log("Can't find any register named %s.", s);
    }
    return 0;
}

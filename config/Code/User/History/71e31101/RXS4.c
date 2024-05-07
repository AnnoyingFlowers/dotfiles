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

#include <cpu/difftest.h>
#include <isa.h>

#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
    if (pc != cpu.pc) {
        Log("%s at DUT pc = " FMT_PADDR ", REF pc = " FMT_PADDR,
            ANSI_FMT("DIFFTEST FAILED", ANSI_FG_RED), cpu.pc, pc);
    }
    for (int i = 0; i < MUXDEF(CONFIG_RVE, 16, 32); i++) {
        if (gpr(i) != ref_r->gpr[check_reg_idx(i)]) {
            Log("%s in reg $%s at pc = " FMT_PADDR " with DUT = " FMT_WORD
                ", REF = " FMT_WORD,
                ANSI_FMT("DIFFTEST FAILED", ANSI_FG_RED), reg_name(i), pc,
                gpr(i), ref_r->gpr[check_reg_idx(i)]);
            return false;
        }
    }
    return true;
}

void isa_difftest_attach() {
}

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

#include <common.h>

extern uint64_t g_nr_guest_inst;

#ifndef CONFIG_TARGET_AM
FILE *log_fp = NULL;

void init_log(const char *log_file) {
    log_fp = stdout;
    if (log_file != NULL) {
        FILE *fp = fopen(log_file, "w");
        Assert(fp, "Can not open '%s'", log_file);
        log_fp = fp;
    }
    Log("Log is written to %s", log_file ? log_file : "stdout");
}

bool log_enable() {
    return MUXDEF(CONFIG_TRACE,
                  (g_nr_guest_inst >= CONFIG_TRACE_START) &&
                      (g_nr_guest_inst <= CONFIG_TRACE_END),
                  false);
}

IRingBuf iringbuf;

// 初始化环形缓冲区
void init_iringbuffer() {
    memset(iringbuf.buffer, 0, sizeof(iringbuf.buffer));  // 将缓冲区清零
    iringbuf.wp = 0;  // 设置写指针的初始位置为0
}

// 向缓冲区写入一个字符串
void iringbuf_write(const char *str) {
    // 将字符串复制到当前写指针指向的位置
    strncpy(iringbuf.buffer[iringbuf.wp], str, BUFFER_COLS);
    iringbuf.buffer[iringbuf.wp][BUFFER_COLS - 1] = '\0';

    // 更新写指针位置，如果到达数组末尾则回绕到0
    iringbuf.wp = (iringbuf.wp + 1) % BUFFER_ROWS;
}

void iringbuf_display() {
    for (int i = 0; i < BUFFER_ROWS; i++) {
        if (i == iringbuf.wp) {
            printf("--> ");
        } else {
            printf("    ");
        }
        printf("%s\n", iringbuf.buffer[i]);
    }
}
#endif

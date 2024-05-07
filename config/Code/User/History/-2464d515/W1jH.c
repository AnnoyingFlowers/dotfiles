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

#include "sdb.h"

#include <cpu/cpu.h>
#include <isa.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "memory/paddr.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();
void new_wp(char *e, bool *success);
void free_wp(int NO, bool *success);
void wp_display();

/* use the `readline' library to provide more flexibility to read from stdin. */
static char *rl_gets() {
    static char *line_read = NULL;

    if (line_read) {
        free(line_read);
        line_read = NULL;
    }

    line_read = readline("(nemu) ");

    if (line_read && *line_read) {
        add_history(line_read);
    }

    return line_read;
}

// deprecated
bool is_num_str(char *chs) {
    for (int i = 0; i < strlen(chs); i++) {
        if (chs[i] > '9' || chs[i] < '0') {
            return false;
        }
    }
    return true;
}

// deprecated
bool is_addr_str(char *chs) {
    int len = strlen(chs);

    if (len != 10) return false;
    if (chs[0] != '0' || chs[1] != 'x') return false;

    for (int i = 2; i < 10; i++) {
        if (!((chs[i] >= '0' && chs[i] <= '9') ||
              (chs[i] >= 'a' && chs[i] <= 'f') ||
              (chs[i] >= 'A' && chs[i] <= 'F'))) {
            return false;
        }
    }
    return true;
}

/* 继续执行 continue */
static int cmd_c(char *args) {
    // -1 => 0xffffffffffffffff
    // uint64_t的-1指UINT64_T_MAX，即18446744073709551615
    cpu_exec(-1);
    return 0;
}

static int cmd_q(char *args) {
    // 给一个状态再结束
    nemu_state.state = NEMU_QUIT;
    return -1;
}

static int cmd_si(char *args) {
    char *endptr = NULL;
    // 默认是执行 1 步
    int steps = 1;

    // 解析si后的第一个参数
    char *arg = strtok(NULL, " ");

    if (arg != NULL) {
        steps = strtol(arg, &endptr, 10);
        if (*endptr != '\0') {
            printf(
                "Invalid N '%s'\n"
                "Usage: si [N], [N] must be a positive number\n",
                arg);
            return 0;
        }
    }

    // 要不要类型转换？感觉可能会有隐患
    cpu_exec(steps);

    return 0;
}

static int cmd_info(char *args) {
    bool error = false;
    char *arg = strtok(NULL, " ");

    if (arg == NULL) {
        printf("NULL SUBCMD '%s'\n", arg);
        error = true;
    } else {
        if (strcmp(arg, "r") == 0) {
            isa_reg_display();
        } else if (strcmp(arg, "w") == 0) {
            // TODO: watchpoints
            wp_display();
        } else {
            printf("Unknown SUBCMD '%s'\n", arg);
            error = true;
        }
    }
    if (error) {
        printf(
            "Usage: info SUBCMD\n\t"
            "info r -- List of integer registers and their contents.\n\t"
            "info w -- Status of all watchpoints.\n");
    }

    return 0;
}

// deprecated
paddr_t parse_exp(char *exp) {
    char *endptr = NULL;
    paddr_t addr = (paddr_t)strtol(exp, &endptr, 16);
    if (*endptr != '\0') {
        return (paddr_t)0;
    }
    return addr;
}

static int cmd_x(char *args) {
    char *endptr;
    int steps = 1;
    bool error = false;

    // 第一个参数 N 是否为空
    char *arg = strtok(NULL, " ");

    if (arg == NULL) {
        printf("NULL N '%s'\n", arg);
        error = true;
    } else {
        // 第一个参数 N 是否合法
        steps = strtol(arg, &endptr, 10);

        if (*endptr != '\0') {
            printf("Invalid N '%s'\n", arg);
            error = true;
        } else {
            // 第二个参数 EXPR 是否为空
            // 这里一定要小心，如果delim还传" "的话，
            // 会把带空格的表达式截断，导致结果不正确
            char *exp = strtok(NULL, "\n");

            if (exp == NULL) {
                printf("NULL expression '%s'\n", exp);
                error = true;
            } else {
                // 第二个参数 EXPR 是否合法
                // TODO: complete parse_exp()
                bool success = true;
                paddr_t addr = expr(exp, &success);

                if (!success) {
                    error = true;
                } else {
                    for (int i = 0; i < steps; i++) {
                        paddr_t offset = i * 4;
                        printf(FMT_WORD " <%s+%u>: " FMT_WORD "\n",
                               addr + offset, exp, offset,
                               paddr_read(addr + offset, 4));
                    }
                }
            }
        }
    }
    if (error) {
        printf(
            "Usage: x N EXPR\n\tx 10 $exp -- calculate "
            "$exp, use the result as the starting memory address, and output "
            "4*N bytes in hex.\n");
    }
    return 0;
}

static int cmd_p(char *args) {
    // 检查参数 EXPR 是否为空
    char *exp = strtok(NULL, "\n");

    if (exp == NULL) {
        printf("NULL expression '%s'\n", exp);
    } else {
        // 参数 EXPR 是否合法
        bool success = true;
        word_t result = expr(exp, &success);

        if (success) {
            printf("%s = %u\t" FMT_WORD "\n", exp, result, result);
        } else {
            printf("Usage: p EXPR\n\tp $exp -- calculate and print $exp.\n");
        }
    }
    return 0;
}

static int cmd_w(char *args) {
    char *exp = strtok(NULL, "\n");

    if (exp == NULL) {
        printf("NULL expression '%s'\n", exp);
    } else {
        bool success = true;
        new_wp(exp, &success);
        if (!success) {
            printf(
                "Usage: w EXPR\n\tw $exp -- A watchpoint stops execution of "
                "your program whenever the value of an expression changes.\n");
        }
    }
    return 0;
}

static int cmd_d(char *args) {
    char *endptr = NULL;
    bool error = false;
    int NO = 0;
    char *arg = strtok(NULL, " ");
    if (arg == NULL) {
        printf("NULL N '%s'\n", arg);
        error = true;
    } else {
        NO = strtol(arg, &endptr, 10);
        if (*endptr != '\0') {
            printf("Invalid N '%s'\n", arg);
            error = true;
        } else {
            bool success = true;
            free_wp(NO, &success);
            if (!success) {
                error = true;
            }
        }
    }
    if (error) {
        printf("Usage: d N\n\td 2 -- delete watchpoint NO 2.\n");
    }
    return 0;
}

static int cmd_help(char *args);

static struct {
    const char *name;
    const char *description;
    int (*handler)(char *);  // 函数指针
} cmd_table[] = {
    {"help", "Display information about all supported commands", cmd_help},
    {"c", "Continue the execution of the program", cmd_c},
    {"q", "Exit NEMU", cmd_q},
    {"si", "Execute next N program line(s), the default N is 1", cmd_si},
    {"info", "Show things about the program being debugged", cmd_info},
    {"x", "Display 4*N byte memories start from expression", cmd_x},
    {"p", "Print value of expression EXP.", cmd_p},
    {"w", "Set a watchpoint for EXPRESSION.", cmd_w},
    {"d", "Delete a watchpoint.", cmd_d},

    /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
    /* extract the first argument */
    char *arg = strtok(NULL, " ");
    int i;

    if (arg == NULL) {
        /* no argument given */
        for (i = 0; i < NR_CMD; i++) {
            printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        }
    } else {
        for (i = 0; i < NR_CMD; i++) {
            if (strcmp(arg, cmd_table[i].name) == 0) {
                printf("%s - %s\n", cmd_table[i].name,
                       cmd_table[i].description);
                return 0;
            }
        }
        printf("Unknown command '%s'\n", arg);
    }
    return 0;
}

void sdb_set_batch_mode() {
    is_batch_mode = true;
}

void sdb_mainloop() {
    if (is_batch_mode) {
        cmd_c(NULL);
        return;
    }

    for (char *str; (str = rl_gets()) != NULL;) {
        char *str_end = str + strlen(str);

        /* extract the first token as the command */
        char *cmd = strtok(str, " ");
        if (cmd == NULL) {
            continue;
        }

        /* treat the remaining string as the arguments,
         * which may need further parsing
         */
        // 如果我输入help<space><space>c，args实际上是<space>c，
        // 但是cmd_help里又用了strtok避免了问题，之后写别的函数时要小心
        char *args = cmd + strlen(cmd) + 1;
        if (args >= str_end) {
            args = NULL;
        }

#ifdef CONFIG_DEVICE
        extern void sdl_clear_event_queue();
        sdl_clear_event_queue();
#endif

        int i;
        for (i = 0; i < NR_CMD; i++) {
            if (strcmp(cmd, cmd_table[i].name) == 0) {
                // 找到一样的命令就调用函数指针指向的函数
                if (cmd_table[i].handler(args) < 0) {
                    return;
                }
                break;
            }
        }

        if (i == NR_CMD) {
            printf("Unknown command '%s'\n", cmd);
        }
    }
}

void init_sdb() {
    /* Compile the regular expressions. */
    init_regex();

    /* Initialize the watchpoint pool. */
    init_wp_pool();
}

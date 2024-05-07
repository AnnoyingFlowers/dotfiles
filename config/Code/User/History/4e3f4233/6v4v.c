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

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// this should be enough
static char buf[65536] = {};
static int offset = 0;
static char code_buf[65536 + 128] = {};  // a little larger than `buf`
static char *code_format =
    "#include <stdio.h>\n"
    "int main() { "
    "  unsigned result = %s; "
    "  printf(\"%%u\", result); "
    "  return 0; "
    "}";

uint32_t choose(uint32_t n) {
    return rand() % n;
}

void gen_num() {
    char str[16] = {0};
    // 随机插入空格
    sprintf(str, "%*u", rand() % 9, rand() % 1000);
    strcpy(buf + offset, str);
    offset += strlen(str);
}

void gen(char c) {
    char str[16] = {0};
    sprintf(str, "%*c", rand() % 5, c);
    strcpy(buf + offset, str);
    offset += strlen(str);
}

void gen_rand_op() {
    char str[16] = {0};
    char op = 0;
    // clang-format off
    switch (choose(4)) {
        case 0: op = '+'; break;
        case 1: op = '-'; break;
        case 2: op = '*'; break;
        case 3: op = '/'; break;
        default: assert(0);
    }
    // clang-format on
    sprintf(str, "%*c", rand() % 5, op);
    strcpy(buf + offset, str);
    offset += strlen(str);
}

// 不知道怎么保证表达式进行无符号运算。。。
// C语言在计算常量表达式时，会把类似1/2这样的东西看作有理数而不是一个表达式
static void gen_rand_expr() {
    int c = choose(3);
    // 经测试，>=50000都不会使buf溢出，但是为了减少overflow的发生，这里取小一点
    if (offset >= 10000) {
        c = 0;
    }
    // clang-format off
    switch (c) {
        case 0: gen_num(); break; // +8
        case 1: gen('('); gen_rand_expr(); gen(')'); break; // +4+?+4
        default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break; // +?+4+?
    }
    // clang-format on
}

int main(int argc, char *argv[]) {
    int seed = time(0);
    srand(seed);
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);
    }
    int i;
    for (i = 0; i < loop; i++) {
        // offset = 0;
        // gen_rand_expr();
        // buf[offset] = '\0';
        strcpy(buf,
               "(((  (  (      38)   /   (  (( 853 )  )-338  *(783)   ) *879/  "
               "  796))  )   )-   (397  /198 /   931  -    837/  589*  ((   ( "
               "(857   -     235 *(((   508) /((  (((616  ) *  595 )   )  ) )- "
               " ( (    868) +     524)  / ((  (  ( 775)  )   ))  -    72   /( "
               "   136)  /  ((108+725)*17 +     126   +   (  (260  *815  /537  "
               " )*208  - (( (   ((  75  ))  ) )   +  (((524 ))  )   /  (875 * "
               " ( 16 /328 )   )  )   )  ) )  ))  )  -686 ))+695  * ( 13 ))");

        sprintf(code_buf, code_format, buf);

        FILE *fp = fopen("/tmp/.code.c", "w");
        assert(fp != NULL);
        fputs(code_buf, fp);
        fclose(fp);

        int ret = system("gcc -Wall -Werror /tmp/.code.c -o /tmp/.expr");
        printf("%d\n", ret);
        if (ret != 0) continue;

        fp = popen("/tmp/.expr", "r");
        assert(fp != NULL);

        int result;
        ret = fscanf(fp, "%d", &result);
        printf("%d\n", ret);
        // 遇到除零了，这次循环不算
        if (ret == -1) {
            i--;
            continue;
        }
        pclose(fp);

        printf("%u %s\n", result, buf);
    }
    gen_rand_expr();
    return 0;
}

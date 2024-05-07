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

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

#include "memory/paddr.h"

/* token类型枚举 */
enum {
    // clang-format off
    TK_LEFT_PAR  = '(',
    TK_RIGHT_PAR = ')',
    TK_MUL       = '*',
    TK_PLUS      = '+',
    TK_MINUS     = '-',
    TK_DIV       = '/',
    TK_NOTYPE    = 256,
    TK_LOGI_AND       ,
    TK_EQ             ,
    TK_NEQ            ,
    TK_HEX            ,
    TK_DEC            ,
    TK_REG            ,
    TK_NEG            ,
    TK_DEREF          ,
    // clang-format on
};

static int precedence[512] = {0};

/* 正则匹配规则 */
static struct rule {
    const char *regex;
    int token_type;
} rules[] = {
    // clang-format off
    {" +"                         , TK_NOTYPE   },  // spaces
    {"0[xX][0-9a-fA-F]+"          , TK_HEX      },  // hex integer
    {"[0-9]+"                     , TK_DEC      },  // decimal integer
    {"\\$[\\$agprst][0-9acp][01]?", TK_REG      },  // register name
    {"\\("                        , TK_LEFT_PAR },  // left parenthesis
    {"\\)"                        , TK_RIGHT_PAR},  // right parenthesis
    {"\\+"                        , TK_PLUS     },  // plus
    {"\\-"                        , TK_MINUS    },  // minus
    {"\\*"                        , TK_MUL      },  // mul
    {"\\/"                        , TK_DIV      },  // div
    {"=="                         , TK_EQ       },  // equal
    {"!="                         , TK_NEQ      },  // not equal
    {"&&"                         , TK_LOGI_AND },  // logical and
    //clang-format on
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

void test_expr();

// 根据C99标准，对运算符优先级进行初始化
void init_precedence() {
    // clang-format off
    precedence[TK_LEFT_PAR ] =  1;
    precedence[TK_RIGHT_PAR] =  1;
    precedence[TK_NEG      ] =  2;
    precedence[TK_DEREF    ] =  2;
    precedence[TK_MUL      ] =  3;
    precedence[TK_DIV      ] =  3;
    precedence[TK_PLUS     ] =  4;
    precedence[TK_MINUS    ] =  4;
    precedence[TK_EQ       ] =  7;
    precedence[TK_NEQ      ] =  7;
    precedence[TK_LOGI_AND ] = 11;
    // clang-format on
}

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
    int i;
    char error_msg[128];
    int ret;

    for (i = 0; i < NR_REGEX; i++) {
        ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
        if (ret != 0) {
            regerror(ret, &re[i], error_msg, 128);
            panic("regex compilation failed: %s\n%s", error_msg,
                  rules[i].regex);
        }
    }

    /* Init precedence of operations */
    init_precedence();

    /* Read the test expressions in the input file and test expr function. */
    // test_expr();
}

typedef struct token {
    int type;
    char str[32];
} Token;

#define MAX_TOKENS 64
static Token tokens[MAX_TOKENS] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

/* 给输入的表达式划分token */
static bool make_token(char *e) {
    int position = 0;
    int i;
    regmatch_t pmatch;

    nr_token = 0;

    while (e[position] != '\0') {
        /* Try all rules one by one. */
        for (i = 0; i < NR_REGEX; i++) {
            if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 &&
                pmatch.rm_so == 0) {
                char *substr_start = e + position;
                int substr_len = pmatch.rm_eo;

                /*Log("match rules[%d] = \"%s\" at position %d with len %d:
                   %.*s", i, rules[i].regex, position, substr_len, substr_len,
                    substr_start);*/

                position += substr_len;

                // Now a new token is recognized with rules[i].
                // 其他类型都是要赋值的，就他不要，给他放一边去
                if (rules[i].token_type == TK_NOTYPE) {
                    break;
                }

                Token *tk = &tokens[nr_token];
                // 虽然除了数字之外都不用str值，还是赋个零保险一点
                memset(tk->str, 0, 32);
                tk->type = rules[i].token_type;

                switch (tk->type) {
                    case TK_REG:
                        Assert(*substr_start == '$',
                               "register token must start with '$'.");
                        // 去掉开头的'$'
                        strncpy(tk->str, substr_start + 1, substr_len - 1);
                        break;
                    case TK_HEX:
                        // fall through
                    case TK_DEC:
                        Assert(substr_len <= 32,
                               "token length must be smaller than 32.");
                        strncpy(tk->str, substr_start, substr_len);
                        break;
                    case TK_MINUS:
                        // 区分减号还是负号
                        if (nr_token == 0 ||
                            (tokens[nr_token - 1].type != TK_RIGHT_PAR &&
                             tokens[nr_token - 1].type != TK_DEC &&
                             tokens[nr_token - 1].type != TK_HEX &&
                             tokens[nr_token - 1].type != TK_REG)) {
                            tk->type = TK_NEG;
                        }
                        break;
                    case TK_MUL:
                        // 区分乘号还是解引用
                        if (nr_token == 0 ||
                            (tokens[nr_token - 1].type != TK_RIGHT_PAR &&
                             tokens[nr_token - 1].type != TK_DEC &&
                             tokens[nr_token - 1].type != TK_HEX &&
                             tokens[nr_token - 1].type != TK_REG)) {
                            tk->type = TK_DEREF;
                        }
                        break;
                    default:
                        break;
                }

                nr_token++;
                Assert(nr_token < MAX_TOKENS,
                       "nr_token must be smaller than MAX_TOKENS");
                break;
            }
        }

        // 没找到，报错
        if (i == NR_REGEX) {
            printf("no match at position %d\n%s\n%*.s^\n", position, e,
                   position, "");
            return false;
        }
    }

    return true;
}

/* "(expr)"判断expr两端的括号是否相配 */
bool check_parentheses(int p, int q) {
    if (tokens[p].type != TK_LEFT_PAR || tokens[q].type != TK_RIGHT_PAR) {
        return false;
    }
    // 去掉外部括号之后还必须是合法括号结构
    int valid_par = 0;
    for (int i = p + 1; i < q; i++) {
        if (tokens[i].type == TK_LEFT_PAR) valid_par++;
        if (tokens[i].type == TK_RIGHT_PAR) valid_par--;
        if (valid_par < 0) return false;
    }
    return true;
}

/* 寻找主运算符 */
int find_main_op(int p, int q) {
    int op_pos = -1;
    int in_parentheses = 0;
    for (int i = p; i <= q; i++) {
        int type = tokens[i].type;
        if (type == TK_RIGHT_PAR) in_parentheses--;
        if (type == TK_LEFT_PAR) in_parentheses++;
        if (in_parentheses != 0 || precedence[type] == 0) continue;
        if (op_pos == -1 || precedence[type] >= precedence[tokens[op_pos].type])
            op_pos = i;
    }
    return op_pos;
}

/* 递归求值 */
word_t eval(int p, int q, bool *success) {
    if (!*success) {
        return 0;
    }
    if (p > q) {
        /* Bad expression */
        *success = false;
        return 0;
    } else if (p == q) {
        /* Single token.
         * For now this token should be a number.
         * Return the value of the number.
         */
        char *endptr = NULL;
        word_t num = 0;
        switch (tokens[p].type) {
            case TK_DEC:
                num = (word_t)strtol(tokens[p].str, &endptr, 10);
                Assert(endptr - tokens[p].str < 32,
                       "that's a pretty awful bug...");
                return num;
            case TK_HEX:
                num = (word_t)strtol(tokens[p].str, &endptr, 16);
                Assert(endptr - tokens[p].str < 32,
                       "that's a pretty awful bug...");
                return num;
            case TK_REG:
                num = isa_reg_str2val(tokens[p].str, success);
                return num;
            default:
                *success = false;
                return 0;
        }
    } else if (check_parentheses(p, q) == true) {
        /* The expression is surrounded by a matched pair of parentheses.
         * If that is the case, just throw away the parentheses.
         */
        return eval(p + 1, q - 1, success);
    } else {
        int op = find_main_op(p, q);
        // 没找到主要运算符
        if (op == -1) {
            *success = false;
            return 0;
        }

        // 处理单目运算符
        if (tokens[op].type == TK_NEG) {
            // 处理负号
            return -eval(op + 1, q, success);
        } else if (tokens[op].type == TK_DEREF) {
            // 处理解引用
            paddr_t addr = eval(op + 1, q, success);
            return paddr_read(addr, 8);
        }

        // 处理双目运算符
        word_t val1 = eval(p, op - 1, success);
        word_t val2 = eval(op + 1, q, success);

        // clang-format off
        switch (tokens[op].type) {
            case TK_PLUS: return val1 + val2;
            case TK_MINUS: return val1 - val2;
            case TK_MUL: return val1 * val2;
            case TK_DIV:
                // 在这里处理除零
                if (val2 == 0) {
                    *success = false;
                    printf("Division by zero in [p, q] = [%d, %d].\n", p, q);
                    return 0;
                }
                return val1 / val2;
            case TK_EQ:       return val1 == val2;
            case TK_NEQ:      return val1 != val2;
            case TK_LOGI_AND: return val1 && val2;
            default:
                printf("val1: %u, val2: %u, type: %d\n", val1, val2,
                       tokens[op].type);
                assert(0);
        }
        // clang-format on
    }
    // 保险起见
    *success = false;
    return 0;
}

word_t expr(char *e, bool *success) {
    if (!make_token(e)) {
        *success = false;
        return 0;
    }

    /* TODO: Insert codes to evaluate the expression. */
    word_t result = eval(0, nr_token - 1, success);
    if (*success) {
        return result;
    } else {
        printf("Invalid expression: %s\n", e);
    }

    return 0;
}

void test_expr() {
    char *endptr = NULL;

    FILE *fp = fopen("tools/gen-expr/input", "r");
    assert(fp != NULL);
    char line[65536] = {0};

    while (fgets(line, sizeof(line), fp) != NULL) {
        bool success = true;

        char *expect_str = strtok(line, " ");
        Assert(expect_str != NULL, "expect_str must not be NULL.");

        word_t expect = (word_t)strtol(expect_str, &endptr, 10);
        Assert(*endptr == '\0', "endptr must be '\\0'.");

        char *expression = strtok(NULL, "\n");
        word_t result = expr(expression, &success);

        if (success && result == expect) {
            printf("Success!\n");
        } else {
            printf("Fail! expect: %u, result: %u\n", expect, result);
            printf("%s - %s\n", expect_str, expression);
        }
    }
    fclose(fp);
}
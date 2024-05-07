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
#ifdef CONFIG_WATCHPOINT

#define NR_WP 32

typedef struct watchpoint {
    int NO;
    struct watchpoint* next;
    char* expr;
    word_t val;
    word_t hit_times;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

/* 初始化监视点池 */
void init_wp_pool() {
    int i;
    for (i = 0; i < NR_WP; i++) {
        wp_pool[i].NO = i;
        wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
        wp_pool[i].expr = NULL;
        wp_pool[i].val = 0;
        wp_pool[i].hit_times = 0;
    }

    head = NULL;
    free_ = wp_pool;
}

/* 从free_链表中返回一个空闲的监视点结构 */
void new_wp(char* e, bool* success) {
    if (free_ == NULL) {
        printf("No more space in pool, create watchpoint failed.\n");
        *success = false;
        return;
    }

    // 计算表达式
    word_t res = expr(e, success);
    if (!*success) {
        return;
    }

    // 从pool里拿一个空闲的WP
    WP* wp = free_;
    free_ = wp->next;
    wp->next = NULL;

    // 考虑head为空的情况
    if (head == NULL) {
        head = wp;
    } else {
        // head不为空的情况
        WP* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        // 接到head上最后一个WP后面
        tail->next = wp;
    }
    if (wp != NULL) {
        wp->expr = calloc(1, strlen(e) + 1);
        strcpy(wp->expr, e);
        wp->val = res;
        wp->hit_times = 0;
        printf("Watchpoint NO %d created.\n", wp->NO);
    }
    return;
}

/* 将wp归还到free_链表中 */
void free_wp(int NO, bool* success) {
    if (head == NULL) {
        printf("No watchpoints now, delete watchpoint failed.\n");
        *success = false;
        return;
    }
    WP* wp = &wp_pool[NO];
    // 如果刚好是head
    if (wp == head) {
        head = wp->next;
        wp->next = free_;
        free_ = wp;
    } else {
        // 找wp的上一个
        WP* prev = head;
        while (prev->next != wp && prev->next != NULL) {
            prev = prev->next;
        }
        // 没找到
        if (prev->next == NULL) {
            printf("Watchpoint NO %d does not exist.\n", NO);
            *success = false;
            return;
        }
        // 找到了
        prev->next = wp->next;
        wp->next = free_;
        free_ = wp;
    }
    if (wp != NULL) {
        free(wp->expr);
        wp->expr = NULL;
        wp->val = 0;
        wp->hit_times = 0;
        printf("Watchpoint No %d deleted.\n", NO);
    }
    return;
}

/* 打印所有监视点状态 */
void wp_display() {
    if (head == NULL) {
        printf("No watchpoints.\n");
        return;
    }
    printf("NO\tWhat\n");
    WP* wp = head;
    while (wp != NULL) {
        printf("%d\t%s\n\twatchpoint already hit %d time(s).\n", wp->NO,
               wp->expr, wp->hit_times);
        wp = wp->next;
    }
    return;
}

/* 检查监视点是否有变化 */
void eval_all_wp(bool* is_changed) {
    WP* wp = head;
    while (wp != NULL) {
        bool success = true;
        word_t new_val = expr(wp->expr, &success);
        Assert(success, "Can't evaluate the expression in watchpoint NO %d.",
               wp->NO);
        word_t old_val = wp->val;
        if (old_val != new_val) {
            printf("\nWatchpoint NO %d: %s\n\nOld value = %u\nNew value = %u\n",
                   wp->NO, wp->expr, old_val, new_val);
            wp->hit_times++;
            *is_changed = true;
        }
        wp->val = new_val;
        wp = wp->next;
    }
    return;
}
#endif
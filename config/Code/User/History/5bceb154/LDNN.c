/**
 * rng_buf库的实现
 *
 * @作者 Vitalii Chernookyi
 * @版权 BSD
 */

#include "ringbuffer_posix.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

// 默认的rng_buf名称
static const char rng_buf_default_name[] = "rng_buf";

// 将最小大小转换为页大小的辅助函数
static inline uint64_t min_size2size(size_t min_size) {
    const long pagesize = sysconf(_SC_PAGESIZE);

    uint64_t pages_qty = min_size / pagesize;

    if (min_size % pagesize) pages_qty++;

    if (!pages_qty) pages_qty++;

    return pages_qty * ((pagesize > 0) ? (unsigned long)pagesize : 4096UL);
}

// 创建一个新的rng_buf实例
rng_buf_t *rng_buf_create(const char *name, size_t min_size,
                          _Bool use_file_in_tmp) {
    int shm_fd = -1;
    int s_seg_counter = 0;
    int res, err_no;

    char seg_name[4096] = "";
    const uint64_t size = min_size2size(min_size);

    const char *tmp_dir = getenv("TMPDIR");

    if (NULL == tmp_dir) tmp_dir = P_tmpdir;

    if (NULL == name) name = rng_buf_default_name;

    if ('/' == name[0]) name++;

    if ('\0' == name[0]) name = rng_buf_default_name;

    // 打开一个新的命名共享内存段
    while (1) {
        if (!use_file_in_tmp) {
            // 这是POSIX推荐的“便携式格式”。
            // 当然，“便携式格式”在某些系统上不起作用...
            snprintf(seg_name, sizeof(seg_name), "/%s-%d-%d", name, getpid(),
                     s_seg_counter);
            shm_fd = shm_open(seg_name, O_RDWR | O_CREAT | O_EXCL, 0600);
        } else {
            // 当“便携式格式”不起作用时，我们尝试构建
            // 一个完整的文件系统路径名，指向一个合适的临时目录。
            snprintf(seg_name, sizeof(seg_name), "%s/%s-%d-%d", tmp_dir, name,
                     getpid(), s_seg_counter);
            shm_fd = open(seg_name, O_RDWR | O_CREAT | O_EXCL, 0600);
        }

        if (shm_fd != -1) break;

        // 出错了，让我们尝试基本的解决方法
        if (errno == EACCES && (!use_file_in_tmp)) {
            use_file_in_tmp = true;
            continue;  // 尝试在TMP目录中使用文件再次尝试
        }

        s_seg_counter++;

        if (errno == EEXIST)  // 命名段已经存在（不应该发生）。 再试一次
            continue;

        goto return_null;
    }

    // 我们已经打开了一个新的共享内存段fd。
    // 现在将其长度设置为我们实际需要的大小的两倍，并将其映射到两个相邻的内存区域。
    if (ftruncate(shm_fd, (off_t)2 * size) == -1) goto return_null;

    unsigned char *first_copy =
        mmap(0, 2 * size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, (off_t)0);

    if (first_copy == MAP_FAILED) goto return_null;

    // 将第一半映射到第二半原来的空洞中。
    unsigned char *second_copy =
        mmap((char *)first_copy + size, size, PROT_READ | PROT_WRITE,
             MAP_SHARED | MAP_FIXED, shm_fd, (off_t)0);

    if (second_copy == MAP_FAILED) goto return_null;

    close(shm_fd);  // 不再需要fd。 映射被保留。
    shm_fd = -1;

    if (!use_file_in_tmp)
        res = shm_unlink(seg_name);
    else
        res = unlink(seg_name);
    (void)res;

    rng_buf_t *rb = malloc(sizeof(rb[0]) + strlen(seg_name));
    if (NULL == rb) {
        err_no = errno;
        munmap(first_copy, 2 * size);
        errno = err_no;
        goto return_null;
    }

    // 现在记住重要的信息
    rb->base = first_copy;
    rb->size = size;
    rb->write_offset_bytes = 0;
    rb->read_offset_bytes = 0;
    strcpy(rb->name, seg_name);
    return rb;

return_null:
    err_no = errno;

    close(shm_fd);  // 清理
    if (!use_file_in_tmp)
        shm_unlink(seg_name);
    else
        unlink(seg_name);

    errno = err_no;
    return NULL;
}

// 销毁rng_buf实例
void rng_buf_destroy(rng_buf_t **rb) {
    int res;

    res = munmap(rb[0]->base, 2 * rb[0]->size);

    (void)res;

    free(rb[0]);
    rb[0] = NULL;
}

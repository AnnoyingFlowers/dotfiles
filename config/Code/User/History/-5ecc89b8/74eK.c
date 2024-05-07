#include <common.h>
#include <elf.h>

#include "debug.h"

// another instruction tracer
IRingBuf iringbuf;

void init_iringbuffer() {
    memset(iringbuf.buffer, 0, sizeof(iringbuf.buffer));
    iringbuf.wp = 0;
}

void iringbuf_write(const char* str) {
    strncpy(iringbuf.buffer[iringbuf.wp], str, BUFFER_COLS);
    iringbuf.buffer[iringbuf.wp][BUFFER_COLS - 1] = '\0';

    // 更新写指针位置，如果到达数组末尾则回绕到0
    iringbuf.wp = (iringbuf.wp + 1) % BUFFER_ROWS;
}

void iringbuf_display() {
    for (int i = 0; i < BUFFER_ROWS; i++) {
        if ((i + 1) % BUFFER_ROWS == iringbuf.wp) {
            printf("--> ");
        } else {
            printf("    ");
        }
        printf("%s\n", iringbuf.buffer[i]);
    }
}

// function tracer
Funtab funtab = {0, NULL};

void init_elf(const char* elf_file) {
    printf("%s\n", elf_file);
    FILE* fp = fopen(elf_file, "rb");
    Assert(fp, "Can not open '%s'", elf_file);
    // 读取ELF头部
    Elf32_Ehdr ehdr;
    // fread的size和n倒腾来倒腾去没啥区别，但是有结构的数据类型最好按照结构分块读取
    fread(&ehdr, sizeof(ehdr), 1, fp);
    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 || ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        fclose(fp);
        Assert(0, "Not an ELF file\n");
        return;
    }

    // 定位到节头表，并读取
    fseek(fp, ehdr.e_shoff, SEEK_SET);
    Elf32_Shdr* shdr = malloc(ehdr.e_shentsize * ehdr.e_shnum);
    fread(shdr, ehdr.e_shentsize, ehdr.e_shnum, fp);

    // 查找符号表和字符串表
    Elf32_Shdr *symtab = NULL, *strtab = NULL;
    for (int i = 0; i < ehdr.e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            symtab = &shdr[i];
        } else if (shdr[i].sh_type == SHT_STRTAB &&
                   i != ehdr.e_shstrndx) {  // 排除section header string table
            strtab = &shdr[i];
        }
    }

    if (!symtab || !strtab) {
        fclose(fp);
        Assert(0, "Symbol table or string table not found\n");
        return;
    }

    // 读取符号表
    Elf32_Sym* symbols = malloc(symtab->sh_size);
    fseek(fp, symtab->sh_offset, SEEK_SET);
    fread(symbols, symtab->sh_size, 1, fp);

    // 读取字符串表
    char* strs = malloc(strtab->sh_size);
    fseek(fp, strtab->sh_offset, SEEK_SET);
    fread(strs, strtab->sh_size, 1, fp);

    // 输出符号名称
    for (int i = 0; i < symtab->sh_size / symtab->sh_entsize; ++i) {
        if (ELF32_ST_TYPE(symbols[i].st_info) == STT_FUNC) {
            printf("%d: %s: [%x, %x)\n", i, &strs[symbols[i].st_name],
                   symbols[i].st_value,
                   symbols[i].st_value + symbols[i].st_size);
            // 重新分配funcs数组以添加新的Func
            funtab.funcs =
                realloc(funtab.funcs, (funtab.func_cnt + 1) * sizeof(Func));
            if (!funtab.funcs) {
                // 处理内存分配错误
                fprintf(stderr, "Failed to allocate memory for functions.\n");
                exit(EXIT_FAILURE);
            }

            int len = strlen(&strs[symbols[i].st_name]);
            funtab.funcs[funtab.func_cnt].func_name = (char*)malloc(len + 1);
            strcpy(funtab.funcs[funtab.func_cnt].func_name,
                   &strs[symbols[i].st_name]);
            funtab.funcs[funtab.func_cnt].start =
                symbols[i].st_value;  // 假设 start 是地址值
            funtab.funcs[funtab.func_cnt].end =
                symbols[i].st_value +
                symbols[i].st_size;  // 假设 end 是地址值加上大小

            // 更新函数计数
            funtab.func_cnt++;
        }
    }

    fclose(fp);
    free(shdr);
    free(symbols);
    free(strs);
}
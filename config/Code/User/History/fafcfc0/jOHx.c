#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_DATA 512
// #define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int MAX_DATA;
    int MAX_ROWS;
    struct Address **rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

// void die(const char *message) {
//     if (errno) {
//         perror(message);
//     } else {
//         printf("ERROR: %s\n", message);
//     }

//     exit(1);
// }

// die函数需要接收conn变量作为参数，以便执行清理并关闭它。
void die(struct Connection *conn, const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    // 安全退出，free掉conn
    Database_close(conn);
    exit(1);
}

void diec(const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *addr) {
    printf("Address_print: %d %d %s %s\n", addr->id, addr->set, addr->name,
           addr->email);
}

void Database_load(struct Connection *conn) {
    assert(conn->db && conn->file);

    // int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    // if (rc != 1) die(conn, "Failed to load Database.");
    int rc = fread(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
    if (rc != 1) die(conn, "Failed to load MAX_DATA.");
    rc = fread(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
    if (rc != 1) die(conn, "Failed to load MAX_ROWS.");

    conn->db->rows = (struct Address **)malloc(sizeof(struct Address *) *
                                               conn->db->MAX_ROWS);

    for (int i = 0; i < conn->db->MAX_ROWS; i++) {
        struct Address *row = (struct Address *)malloc(sizeof(struct Address));
        // struct Address *row = conn->db->rows[i];
        rc = fread(&row->id, sizeof(int), 1, conn->file);
        if (rc != 1) die(conn, "Failed to load id.");
        rc = fread(&row->set, sizeof(int), 1, conn->file);
        if (rc != 1) die(conn, "Failed to load set.");

        row->name = (char *)malloc(conn->db->MAX_DATA);
        row->email = (char *)malloc(conn->db->MAX_DATA);

        rc = fread(row->name, sizeof(conn->db->MAX_DATA), 1, conn->file);
        if (rc != 1) die(conn, "Failed to load name.");
        rc = fread(row->email, sizeof(conn->db->MAX_DATA), 1, conn->file);
        if (rc != 1) die(conn, "Failed to load email.");

        conn->db->rows[i] = row;
    }
}

struct Connection *Database_open(const char *filename, char mode) {
    // 如果你的变量并不是从malloc中获取的，也不是从一个从malloc获取的函数中获取的，那么它在栈上。
    //  -如果你从malloc获取了一块内存，并且把指针放在了栈上，那么当函数退出时，指针会被弹出而丢失。
    //  -如果你在栈上存放了大量数据（比如大结构体和数组），那么会产生“栈溢出”并且程序会中止。这种情况下应该通过malloc放在堆上。
    //  -如果你获取了指向栈上变量的指针，并且将它用于传参或从函数返回，接收它的函数会产生“段错误”。因为实际的数据被弹出而消失，指针也会指向被释放的内存。
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die(conn, "Memory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die(conn, "Memory error");

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die(conn, "Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->file) fclose(conn->file);

        if (conn->db) {
            for (int i = 0; i < conn->db->MAX_ROWS; i++) {
                if (conn->db->rows[i]) {
                    free(conn->db->rows[i]->email);
                    free(conn->db->rows[i]->name);
                    free(conn->db->rows[i]);
                }
            }
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file);

    // 是否可以这样写进文件，暂且存疑
    // int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    // if (rc != 1) die(conn, "Failed to write MAX_DATA.");
    int rc = fwrite(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
    if (rc != 1) die(conn, "Failed to write MAX_DATA.");
    rc = fwrite(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
    if (rc != 1) die(conn, "Failed to write MAX_ROWS.");

    for (int i = 0; i < conn->db->MAX_ROWS; i++) {
        struct Address *row = conn->db->rows[i];
        rc = fwrite(&(row->id), sizeof(int), 1, conn->file);
        if (rc != 1) die(conn, "Failed to write id.");
        rc = fwrite(&(row->set), sizeof(int), 1, conn->file);
        if (rc != 1) die(conn, "Failed to write set.");
        rc = fwrite(row->name, 1, conn->db->MAX_DATA, conn->file);
        if (rc != conn->db->MAX_DATA) die(conn, "Failed to write name.");
        rc = fwrite(row->email, 1, conn->db->MAX_DATA, conn->file);
        if (rc != conn->db->MAX_DATA) die(conn, "Failed to write email.");
    }

    rc = fflush(conn->file);
    if (rc == -1) die(conn, "Cannot flush database.");
}

void Database_create(struct Connection *conn, char *str_MAX_DATA,
                     char *str_MAX_ROWS) {
    int MAX_ROWS = atoi(str_MAX_ROWS);
    int MAX_DATA = atoi(str_MAX_DATA);

    if (MAX_ROWS <= 0) die(conn, "MAX_ROWS must be positive.");
    if (MAX_DATA <= 0) die(conn, "MAX_DATA must be positive.");

    conn->db->MAX_ROWS = MAX_ROWS;
    conn->db->MAX_DATA = MAX_DATA;

    conn->db->rows = (struct Address **)malloc(sizeof(struct Address *) *
                                               conn->db->MAX_ROWS);

    for (int i = 0; i < conn->db->MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address *addr = malloc(sizeof(struct Address));
        addr->id = i;
        addr->set = 0;
        addr->name = (char *)malloc(conn->db->MAX_DATA);
        addr->email = (char *)malloc(conn->db->MAX_DATA);

        memset(addr->name, 0, conn->db->MAX_DATA);
        memset(addr->email, 0, conn->db->MAX_DATA);

        // then just assign it
        conn->db->rows[i] = addr;
        printf("Database_create: %d %d %s %s\n", conn->db->rows[i]->id,
               conn->db->rows[i]->set, conn->db->rows[i]->name,
               conn->db->rows[i]->email);
    }
}

void Database_set(struct Connection *conn, int id, const char *name,
                  const char *email) {
    if (id >= conn->db->MAX_ROWS) die(conn, "There's not that many records.");

    struct Address *addr = conn->db->rows[id];
    printf("Database_set: %d %d %d %s %s\n", id, addr->id, addr->set,
           addr->name, addr->email);
    if (addr->set) die(conn, "Already set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    // The strncpy() function is similar, except that at most n bytes of src
    // are copied.  Warning: If there is no null  byte  among  the  first  n
    // bytes of src, the string placed in dest will not be null-terminated.
    char *res = strncpy(addr->name, name, conn->db->MAX_DATA);
    // a simple way to avoid error.
    addr->name[conn->db->MAX_DATA - 1] = '\0';
    if (!res) die(conn, "Name copy failed");

    res = strncpy(addr->email, email, conn->db->MAX_DATA);
    // also a strncpy bug
    addr->email[conn->db->MAX_DATA - 1] = '\0';
    if (!res) die(conn, "Email copy failed");

    printf("Database_set: %d %d %d %s %s\n", id, addr->id, addr->set,
           addr->name, addr->email);
}

void Database_get(struct Connection *conn, int id) {
    if (id >= conn->db->MAX_ROWS) die(conn, "There's not that many records.");

    struct Address *addr = conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die(conn, "ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    if (id >= conn->db->MAX_ROWS) die(conn, "There's not that many records.");

    // We don't really delete the entry, because that's expensive, we just write
    // the "set" flag as 0
    struct Address *addr = conn->db->rows[id];
    addr->set = 0;

    // char *name = (char *)malloc(conn->db->MAX_DATA);
    // char *email = (char *)malloc(conn->db->MAX_DATA);

    // free(conn->db->rows[id]->name);
    // free(conn->db->rows[id]->email);

    // struct Address addr = {.id = id, .set = 0, .name = name, .email = email};
    // conn->db->rows[id] = &addr;
}

void Database_list(struct Connection *conn) {
    if (!conn) die(conn, "There's no database yet.");
    int i = 0;
    struct Database *db = conn->db;
    if (!db) die(conn, "There's no rows yet.");

    for (i = 0; i < conn->db->MAX_ROWS; i++) {
        struct Address *cur = db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) diec("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;
    // 传递非法参数
    if (argc > 3) id = atoi(argv[3]);

    switch (action) {
        case 'c':
            if (argc != 5) die(conn, "Need MAX_ROWS, MAX DATA to set");

            Database_create(conn, argv[3], argv[4]);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) die(conn, "Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die(conn, "Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die(conn, "Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        // 安全检查
        default:
            die(conn,
                "Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
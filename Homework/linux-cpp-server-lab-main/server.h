#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdint.h>

struct server_module {
    void* handle;                /* 动态库句柄 */
    const char* name;           /* 模块名称 */
    void (*generate_function) (int); /* 生成函数指针 */
};

extern struct server_module* module_open(const char* module_name);
extern void module_close(struct server_module* module);

extern void server_run(struct in_addr local_address, uint16_t port);

extern char* module_dir;       /* 模块目录 */
extern int verbose;            /* 是否输出详细信息 */

#endif /* SERVER_H */
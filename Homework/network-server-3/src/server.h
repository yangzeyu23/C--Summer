#ifndef SERVER_H
#define SERVER_H

#include "common.h"
#include <netinet/in.h>  // 用于 struct in_addr

#ifdef __cplusplus
extern "C" {
#endif

// 声明 server_run 函数
extern void server_run(struct in_addr local_address, uint16_t port);

// 声明 handle_client 函数
extern void handle_client(int client_socket);

#ifdef __cplusplus
}
#endif

#endif // SERVER_H
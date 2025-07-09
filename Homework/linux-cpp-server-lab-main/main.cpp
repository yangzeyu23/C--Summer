#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

void print_help(const char* program_name) {
    printf("用法: %s [选项]\n", program_name);
    printf("选项:\n");
    printf("  -a, --address ADDR   指定服务器地址 (默认: localhost)\n");
    printf("  -h, --help           显示帮助信息\n");
    printf("  -m, --modir DIR      指定模块目录 (默认: ./)\n");
    printf("  -p, --port PORT      指定服务器端口 (默认: 8008)\n");
    printf("  -v, --verbose        显示详细运行信息\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    const char* address = "localhost";
    uint16_t port = 8008;
    
    int opt;
    int option_index = 0;
    
    static struct option long_options[] = {
        {"address", required_argument, 0, 'a'},
        {"help", no_argument, 0, 'h'},
        {"modir", required_argument, 0, 'm'},
        {"port", required_argument, 0, 'p'},
        {"verbose", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };
    
    while ((opt = getopt_long(argc, argv, "a:hm:p:v", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'a':
                address = optarg;
                break;
            case 'h':
                print_help(argv[0]);
                break;
            case 'm':
                module_dir = strdup(optarg);
                break;
            case 'p':
                port = (uint16_t)atoi(optarg);
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                fprintf(stderr, "尝试 '%s --help' 获取更多信息\n", argv[0]);
                exit(1);
        }
    }
    
    struct in_addr local_address;
    if (strcmp(address, "localhost") == 0) {
        local_address.s_addr = htonl(INADDR_LOOPBACK);
    } else {
        if (inet_aton(address, &local_address) == 0) {
            fprintf(stderr, "无效的地址: %s\n", address);
            exit(1);
        }
    }
    
    server_run(local_address, port);
    
    if (module_dir != NULL) {
        free(module_dir);
    }
    
    return 0;
}
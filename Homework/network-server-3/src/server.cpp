#include "server.h"
#include "module.h"
#include "modules/time.h"
#include "modules/issue.h"
#include "modules/diskfree.h"
#include "modules/process.h"
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

// 定义 HTML 模板变量
static const char* not_found_response_template =
    "HTTP/1.0 404 Not Found\n"
    "Content-type: text/html\n"
    "\n"
    "<html>\n"
    "<body>\n"
    "<h1>Not Found</h1>\n"
    "<p>The requested URL %s was not found on this server.</p>\n"
    "</body>\n"
    "</html>\n";

static const char* bad_request_response =
    "HTTP/1.0 400 Bad Request\n"
    "Content-type: text/html\n"
    "\n"
    "<html>\n"
    "<body>\n"
    "<h1>Bad Request</h1>\n"
    "<p>This server did not understand your request.</p>\n"
    "</body>\n"
    "</html>\n";

void handle_client(int client_socket) {
    char request[1024];
    read(client_socket, request, sizeof(request));

    // 简单解析请求
    char method[16], resource[256];
    sscanf(request, "%s %s", method, resource);

    if (strcmp(method, "GET") == 0) {
        if (strcmp(resource, "/time") == 0) {
            module_generate_time(client_socket);
        } else if (strcmp(resource, "/issue") == 0) {
            module_generate_issue(client_socket);
        } else if (strcmp(resource, "/diskfree") == 0) {
            module_generate_diskfree(client_socket);
        } else if (strcmp(resource, "/process") == 0) {
            module_generate_process(client_socket);
        } else {
            dprintf(client_socket, "%s", not_found_response_template);
        }
    } else {
        dprintf(client_socket, "%s", bad_request_response);
    }

    close(client_socket);
}

void server_run(struct in_addr local_address, uint16_t port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error: Could not create socket." << std::endl;
        return;
    }

    struct sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr = local_address;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Could not bind to address." << std::endl;
        close(server_socket);
        return;
    }

    if (listen(server_socket, 10) < 0) {
        std::cerr << "Error: Could not listen on socket." << std::endl;
        close(server_socket);
        return;
    }

    std::cout << "Server is running on port " << port << "..." << std::endl;

    while (true) {
        struct sockaddr_in client_addr = {};
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Error: Could not accept connection." << std::endl;
            continue;
        }

        // 处理客户端请求
        handle_client(client_socket);
    }

    close(server_socket);
}
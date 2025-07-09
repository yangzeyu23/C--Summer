#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server.h"

static char* ok_response =
  "HTTP/1.0 200 OK\n"
  "Content-type: text/html\n"
  "\n";

static char* bad_request_response =
  "HTTP/1.0 400 Bad Request\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  "<body>\n"
  "<h1>Bad Request</h1>\n"
  "<p>This server did not understand your request.</p>\n"
  "</body>\n"
  "</html>\n";

static char* not_found_response_template =
  "HTTP/1.0 404 Not Found\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  "<body>\n"
  "<h1>Not Found</h1>\n"
  "<p>The requested URL %s was not found on this server.</p>\n"
  "</body>\n"
  "</html>\n";

static char* bad_method_response_template =
  "HTTP/1.0 501 Method Not Implemented\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  "<body>\n"
  "<h1>Method Not Implemented</h1>\n"
  "<p>The method %s is not implemented by this server.</p>\n"
  "</body>\n"
  "</html>\n";

#define THREAD_POOL_SIZE 10

typedef struct {
    pthread_t threads[THREAD_POOL_SIZE];
    int client_sockets[THREAD_POOL_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    int available_threads;
} thread_pool_t;

thread_pool_t thread_pool;

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    char buffer[1024];
    ssize_t bytes_read;
    
    bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        close(client_socket);
        return NULL;
    }
    
    buffer[bytes_read] = '\0';
    
    char method[10];
    char url[255];
    char protocol[10];
    
    if (sscanf(buffer, "%9s %254s %9s", method, url, protocol) != 3) {
        write(client_socket, bad_request_response, strlen(bad_request_response));
        close(client_socket);
        return NULL;
    }
    
    if (verbose) {
        printf("收到请求: %s %s %s\n", method, url, protocol);
    }
    
    if (strcmp(method, "GET") != 0) {
        char response[1024];
        sprintf(response, bad_method_response_template, method);
        write(client_socket, response, strlen(response));
        close(client_socket);
        return NULL;
    }
    
    char module_name[255];
    if (url[0] == '/' && url[1] != '\0') {
        strcpy(module_name, url + 1);
    } else {
        strcpy(module_name, "time");
    }
    
    struct server_module* module = module_open(module_name);
    if (module == NULL) {
        char response[1024];
        sprintf(response, not_found_response_template, url);
        write(client_socket, response, strlen(response));
        close(client_socket);
        return NULL;
    }
    
    write(client_socket, ok_response, strlen(ok_response));
    
    module->generate_function(client_socket);
    
    module_close(module);
    
    close(client_socket);
    
    return NULL;
}

void init_thread_pool() {
    pthread_mutex_init(&thread_pool.mutex, NULL);
    pthread_cond_init(&thread_pool.condition, NULL);
    thread_pool.available_threads = THREAD_POOL_SIZE;
    
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        thread_pool.client_sockets[i] = -1;
    }
}

void assign_thread(int client_socket) {
    pthread_mutex_lock(&thread_pool.mutex);
    
    while (thread_pool.available_threads == 0) {
        pthread_cond_wait(&thread_pool.condition, &thread_pool.mutex);
    }
    
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        if (thread_pool.client_sockets[i] == -1) {
            thread_pool.client_sockets[i] = client_socket;
            thread_pool.available_threads--;
            
            pthread_create(&thread_pool.threads[i], NULL, handle_client, &thread_pool.client_sockets[i]);
            pthread_detach(thread_pool.threads[i]);
            
            break;
        }
    }
    
    pthread_mutex_unlock(&thread_pool.mutex);
}

void release_thread(int index) {
    pthread_mutex_lock(&thread_pool.mutex);
    
    thread_pool.client_sockets[index] = -1;
    thread_pool.available_threads++;
    
    pthread_cond_signal(&thread_pool.condition);
    pthread_mutex_unlock(&thread_pool.mutex);
}

void server_run(struct in_addr local_address, uint16_t port) {
    int server_socket;
    struct sockaddr_in server_addr;
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("无法创建套接字");
        exit(1);
    }
    
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("设置套接字选项失败");
        exit(1);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr = local_address;
    server_addr.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("绑定失败");
        exit(1);
    }
    
    if (listen(server_socket, 5) < 0) {
        perror("监听失败");
        exit(1);
    }
    
    printf("服务器已启动，监听 %s:%d\n", inet_ntoa(local_address), port);
    
    init_thread_pool();
    
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket;
        
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("接受连接失败");
            continue;
        }
        
        if (verbose) {
            printf("接受来自 %s:%d 的连接\n", 
                   inet_ntoa(client_addr.sin_addr), 
                   ntohs(client_addr.sin_port));
        }
        assign_thread(client_socket);
    }
}
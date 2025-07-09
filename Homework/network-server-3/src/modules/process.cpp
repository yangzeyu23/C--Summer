#include "process.h"
#include <cstdio>
#include <cstring>
#include <sys/socket.h>

void module_generate_process(int client_socket) {
    FILE* fp = popen("ps aux", "r");
    if (!fp) {
        const char* error_message = "Error: Could not execute ps command.";
        send(client_socket, error_message, strlen(error_message), 0);
        return;
    }

    char buffer[1024];
    static const char* page_start = "<html>\n<body>\n<pre>\n";
    static const char* page_end = "</pre>\n</body>\n</html>\n";

    send(client_socket, page_start, strlen(page_start), 0);
    while (fgets(buffer, sizeof(buffer), fp)) {
        send(client_socket, buffer, strlen(buffer), 0);
    }
    send(client_socket, page_end, strlen(page_end), 0);

    pclose(fp);
}
#include "time.h"
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <ctime>

void module_generate_time(int client_socket) {
    time_t now = time(nullptr);
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

    static const char* page_template =
        "<html>\n"
        "<head>\n"
        "<meta http-equiv=\"refresh\" content=\"5\">\n"
        "</head>\n"
        "<body>\n"
        "<p>The current time is %s.</p>\n"
        "</body>\n"
        "</html>\n";

    char response[512];
    snprintf(response, sizeof(response), page_template, time_str);

    send(client_socket, response, strlen(response), 0);
}
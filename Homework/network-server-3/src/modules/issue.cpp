#include "issue.h"
#include <fstream>
#include <cstring>
#include <sys/socket.h>

void module_generate_issue(int client_socket) {
    std::ifstream issue_file("/proc/issue");
    if (!issue_file.is_open()) {
        const char* error_message = "Error: Could not open /proc/issue.";
        send(client_socket, error_message, strlen(error_message), 0);
        return;
    }

    static const char* page_start = "<html>\n<body>\n<pre>\n";
    static const char* page_end = "</pre>\n</body>\n</html>\n";

    send(client_socket, page_start, strlen(page_start), 0);
    std::string line;
    while (std::getline(issue_file, line)) {
        send(client_socket, line.c_str(), line.size(), 0);
        send(client_socket, "\n", 1, 0);
    }
    send(client_socket, page_end, strlen(page_end), 0);
}
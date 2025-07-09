#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

char* module_dir = NULL;
int verbose = 0;

ssize_t write_to_socket(int fd, const char* buffer, size_t n) {
    size_t total_written = 0;
    while (total_written < n) {
        ssize_t count = write(fd, buffer + total_written, n - total_written);
        if (count == -1) {
            return -1;
        }
        total_written += count;
    }
    return total_written;
}

void error(const char* message) {
    perror(message);
    exit(1);
}

void log_message(const char* format, ...) {
    if (verbose) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
        fprintf(stderr, "\n");
    }
}
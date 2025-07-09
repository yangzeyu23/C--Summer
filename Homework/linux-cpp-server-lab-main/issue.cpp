#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static char* page_start = "<html>\n" "<body>\n" "<pre>\n";
static char* page_end = "</pre>\n" "</body>\n" "</html>\n";
static char* error_page =
"<html>\n"
"<body>\n"
"<p>Error: Could not open /proc/issue.</p>\n"
"</body>\n"
"</html>\n";

extern "C" void module_generate(int fd) {
    int issue_fd;
    char buffer[1024];
    ssize_t bytes_read;
    
#ifdef __APPLE__
    issue_fd = open("/System/Library/CoreServices/SystemVersion.plist", O_RDONLY);
#else
    issue_fd = open("/etc/issue", O_RDONLY);
#endif
    
    if (issue_fd == -1) {
        write(fd, error_page, strlen(error_page));
        return;
    }
    
    write(fd, page_start, strlen(page_start));
    
    while ((bytes_read = read(issue_fd, buffer, sizeof(buffer))) > 0) {
        write(fd, buffer, bytes_read);
    }
    
    write(fd, page_end, strlen(page_end));
    
    close(issue_fd);
}
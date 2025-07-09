#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static char* page_template =
"<html>\n" "<head>\n"
"<meta http-equiv=\"refresh\" content=\"5\">\n"
"</head>\n" "<body>\n" "<p>The current time is %s.</p>\n"
"</body>\n" "</html>\n";

extern "C" void module_generate(int fd) {
    time_t current_time;
    char time_string[100];
    char buffer[1024];
    
    time(&current_time);
    strftime(time_string, sizeof(time_string), "%H:%M:%S", localtime(&current_time));
    
    snprintf(buffer, sizeof(buffer), page_template, time_string);
    
    write(fd, buffer, strlen(buffer));
}
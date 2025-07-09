#ifndef TIME_H
#define TIME_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function to generate the HTML page displaying the current system time
void module_generate_time(int client_socket);

#ifdef __cplusplus
}
#endif

#endif // TIME_H
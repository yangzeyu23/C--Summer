#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function to generate the HTML page displaying process information
void module_generate_process(int client_socket);

#ifdef __cplusplus
}
#endif

#endif // PROCESS_H
#ifndef DISKFREE_H
#define DISKFREE_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function to generate the HTML page displaying disk free information
void module_generate_diskfree(int client_socket);

#ifdef __cplusplus
}
#endif

#endif // DISKFREE_H
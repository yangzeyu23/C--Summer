#ifndef ISSUE_H
#define ISSUE_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function to generate the HTML page displaying system issue information
void module_generate_issue(int client_socket);

#ifdef __cplusplus
}
#endif

#endif // ISSUE_H
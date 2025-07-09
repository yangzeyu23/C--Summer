#ifndef MODULE_H
#define MODULE_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct server_module* module_open(const char* module_name);
extern void module_close(struct server_module* module);

#ifdef __cplusplus
}
#endif

#endif // MODULE_H
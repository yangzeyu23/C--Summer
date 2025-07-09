#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

struct server_module {
    void* handle;
    const char* name;
    void (*generate_function)(int);
};

#ifdef __cplusplus
}
#endif

#endif // COMMON_H
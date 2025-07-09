#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "server.h"

static char* get_module_path(const char* module_name) {
    char* module_filename = (char*)malloc(strlen(module_name) + 7);
    if (module_filename == NULL) {
        return NULL;
    }
    sprintf(module_filename, "lib%s.so", module_name);
    
    char* module_path;
    if (module_dir != NULL) {
        module_path = (char*)malloc(strlen(module_dir) + strlen(module_filename) + 2);
        if (module_path == NULL) {
            free(module_filename);
            return NULL;
        }
        sprintf(module_path, "%s/%s", module_dir, module_filename);
    } else {
        module_path = (char*)malloc(strlen(module_filename) + 3);
        if (module_path == NULL) {
            free(module_filename);
            return NULL;
        }
        sprintf(module_path, "./%s", module_filename);
    }
    
    free(module_filename);
    return module_path;
}

struct server_module* module_open(const char* module_name) {
    char* module_path = get_module_path(module_name);
    if (module_path == NULL) {
        return NULL;
    }
    
    void* handle = dlopen(module_path, RTLD_NOW);
    free(module_path);
    if (handle == NULL) {
        fprintf(stderr, "无法加载模块 %s: %s\n", module_name, dlerror());
        return NULL;
    }
    
    void (*generate_function)(int) = (void (*)(int))dlsym(handle, "module_generate");
    if (generate_function == NULL) {
        fprintf(stderr, "无法找到模块 %s 中的 module_generate 函数: %s\n", module_name, dlerror());
        dlclose(handle);
        return NULL;
    }
    
    struct server_module* module = (struct server_module*)malloc(sizeof(struct server_module));
    if (module == NULL) {
        dlclose(handle);
        return NULL;
    }
    
    module->handle = handle;
    module->name = strdup(module_name);
    module->generate_function = generate_function;
    
    if (verbose) {
        printf("已加载模块: %s\n", module_name);
    }
    
    return module;
}

void module_close(struct server_module* module) {
    if (module == NULL) {
        return;
    }
    
    if (verbose) {
        printf("正在卸载模块: %s\n", module->name);
    }
    
    dlclose(module->handle);
    
    free((void*)module->name);
    free(module);
}
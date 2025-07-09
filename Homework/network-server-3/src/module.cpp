#include "module.h"
#include <dlfcn.h>
#include <cstring>
#include <iostream>

struct server_module* module_open(const char* module_name) {
    struct server_module* module = new server_module;
    module->handle = dlopen(module_name, RTLD_LAZY);
    if (!module->handle) {
        std::cerr << "Error: Could not open module " << module_name << ": " << dlerror() << std::endl;
        delete module;
        return nullptr;
    }

    module->generate_function = (void (*)(int))dlsym(module->handle, "module_generate");
    if (!module->generate_function) {
        std::cerr << "Error: Could not find symbol 'module_generate' in module " << module_name << ": " << dlerror() << std::endl;
        dlclose(module->handle);
        delete module;
        return nullptr;
    }

    module->name = module_name;
    return module;
}

void module_close(struct server_module* module) {
    if (module) {
        if (module->handle) {
            dlclose(module->handle);
        }
        delete module;
    }
}
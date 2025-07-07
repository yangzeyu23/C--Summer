// filepath: cpu-process-info/src/process_info.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include "process_info.h"

void print_process_info() {
    std::cout << "Process Information:" << std::endl;

    DIR *procDir = opendir("/proc");
    if (!procDir) {
        std::cerr << "Unable to open /proc directory" << std::endl;
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(procDir)) != nullptr) 
    {
        if (entry->d_type == DT_DIR && std::isdigit(entry->d_name[0])) {
            std::string pid = entry->d_name;
            std::ifstream statusFile("/proc/" + pid + "/status");
            if (statusFile.is_open()) 
            {
                std::string line;
                std::cout << "PID " << pid << ":" << std::endl;

                while (std::getline(statusFile, line)) 
                {
                    if (line.find("Name:") != std::string::npos ||
                        line.find("State:") != std::string::npos ||
                        line.find("VmSize:") != std::string::npos ||
                        line.find("VmRSS:") != std::string::npos) 
                        {
                        std::cout << "  " << line << std::endl;
                    }
                }
                statusFile.close();
                std::cout << std::endl;
            }
        }
    }
    closedir(procDir);
}
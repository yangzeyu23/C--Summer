// filepath: cpu-process-info/src/cpu_info.cpp
#include "cpu_info.h"
#include <iostream>
#include <fstream>
#include <string>

void print_cpu_info() 
{
    std::ifstream cpuinfo("/proc/cpuinfo");

    if (!cpuinfo.is_open()) 
    {
        std::cerr << "无法打开 /proc/cpuinfo 文件" << std::endl;
        return;
    }

    std::string line;
    std::cout << "CPU 信息:" << std::endl;

    while (std::getline(cpuinfo, line)) 
    {
        if (line.find("processor") != std::string::npos ||
            line.find("model name") != std::string::npos ||
            line.find("cpu MHz") != std::string::npos ||
            line.find("cache size") != std::string::npos) {
            std::cout << line << std::endl;
        }
    }
    std::cout << std::endl;
}
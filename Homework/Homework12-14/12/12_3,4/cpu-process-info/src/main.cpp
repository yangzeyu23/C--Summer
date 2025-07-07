#include <iostream>
#include "cpu_info.h"
#include "process_info.h"

int main() 
{
    std::cout << "CPU Information:" << std::endl;
    print_cpu_info();
    
    std::cout << "\nProcess Information:" << std::endl;
    print_process_info();
    
    return 0;
}
//在 Linux 系统环境下运行：创建一个临时文件，向其中写入数据，然后读取并验证数据，最后删除该临时文件。

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h> // for write, close

int main() 
{
    // 创建临时文件
    char tempFileName[] = "testXXXXXX";
    int fd = mkstemp(tempFileName);
    if (fd == -1) 
    {
        perror("mkstemp 失败");
        return 1;
    }

    std::cout << "临时文件创建成功: " << tempFileName << std::endl;

    // 写入数据
    const char* data = "这是测试数据";
    ssize_t bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) 
    {
        perror("write 失败");
        close(fd);
        std::remove(tempFileName);
        return 1;
    }
    else if (bytesWritten != (ssize_t)strlen(data)) 
    {
        std::cerr << "写入数据不完整！" << std::endl;
        close(fd);
        std::remove(tempFileName);
        return 1;
    }

    // 关闭文件描述符以便重新打开进行读取
    if (close(fd) == -1) 
    {
        perror("close 失败");
        std::remove(tempFileName);
        return 1;
    }

    // 读取数据
    std::ifstream inputFile(tempFileName);
    if (!inputFile.is_open()) 
    {
        std::cerr << "无法打开临时文件进行读取！" << std::endl;
        std::remove(tempFileName);
        return 1;
    }

    std::string readData;
    inputFile >> readData;
    inputFile.close();

    // 验证数据
    if (readData == data) 
    {
        std::cout << "数据验证成功: " << readData << std::endl;
    }
    else {
        std::cerr << "数据验证失败！读取到的数据: " << readData << std::endl;
    }

    // 删除临时文件
    if (std::remove(tempFileName) != 0) {
        perror("删除临时文件失败");
        return 1;
    }

    std::cout << "临时文件已删除。" << std::endl;
    return 0;
}
# Dynamic Memory Management

## 简介
本作业实现了动态存储管理机制，重载了 `new` 和 `delete` 操作符，用于跟踪内存的分配和释放情况。

## 文件结构
- `MemoryManager.h`：动态存储管理器的声明和实现。
- `main.cpp`：测试程序入口。
- `test_memory.cpp`：单元测试文件。

## 编译与运行
```bash
g++ -o main main.cpp
./main

g++ -o test test_memory.cpp
./test
```

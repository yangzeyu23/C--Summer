# 远程系统管理Web服务器

## 项目概述

这是一个基于HTTP协议的远程系统管理Web服务器，允许本地或远程客户通过HTTP协议访问系统信息，例如显示时间、系统发布版本、空闲磁盘空间、当前运行的进程等。

服务器使用模块架构针对Web请求生成动态HTML网页，各模块实现为共享目标库，允许动态装载模块，且可在服务器运行期间添加、删除和替换。

## 功能特点

- 使用线程池处理并发Web请求
- 动态加载模块，支持热插拔
- 提供系统时间、系统信息、磁盘空间和进程列表等信息
- 支持命令行参数配置

## 项目结构

- **server.h**: 全局变量、全局类型和函数的声明
- **common.cpp**: 通用函数的定义
- **module.cpp**: 服务模块的装载与卸载功能的实现
- **server.cpp**: 服务器功能的实现
- **main.cpp**: 主函数

服务模块：
- **time.cpp**: 显示系统时间
- **issue.cpp**: 显示系统发布信息
- **diskfree.cpp**: 显示空闲磁盘空间信息
- **process.cpp**: 显示服务器中当前运行的进程列表

## 编译和运行

### 编译

```bash
make
```

### 运行

```bash
./server --address localhost --port 8008
```

或者使用make run命令：

```bash
make run
```

### 命令行选项

- `-a, --address ADDR`: 指定服务器地址（默认：localhost）
- `-h, --help`: 显示帮助信息
- `-m, --modir DIR`: 指定模块目录（默认：./）
- `-p, --port PORT`: 指定服务器端口（默认：8008）
- `-v, --verbose`: 显示详细运行信息

## 访问服务

启动服务器后，可以通过浏览器访问以下URL：

- http://localhost:8008/time - 显示系统时间
- http://localhost:8008/issue - 显示系统发布信息
- http://localhost:8008/diskfree - 显示磁盘空闲信息
- http://localhost:8008/process - 显示进程列表

## 清理

```bash
make clean
```
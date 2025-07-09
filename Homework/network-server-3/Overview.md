# 大作业：构建远程系统管理Web服务器

## 要求和预期功能概述

允许本地或远程客户通过HTTP协议访问系统信息，例如显示时间、Linux发布版本、空闲磁盘空间、当前运行的进程等。

使用模块架构针对Web请求生成动态HTML网页；各模块实现为共享目标库，允许动态装载模块，且可在服务器运行期间添加、删除和替换。

在子进程或线程中服务Web请求，并设计进程池或线程池管理这些进程或线程。服务器不要求超级用户权限。

不要求实现HTTP全部功能；要求使用面向对象架构。

## 要求的程序框架

程序架构：
- server.h：可导出的全局变量、全局类型和函数的声明
- common.cpp：通用函数的定义
- module.cpp：服务模块的装载与卸载功能的实现
- server.cpp：服务器功能的实现
- main.cpp：主函数

服务模块：
- time.h：显示系统时间
- issue.cpp：显示系统发布信息
- diskfree.cpp：显示空闲磁盘空间信息
- process.cpp：显示服务器中当前运行的进程列表

## 程序架构细节提示

### server.h

一. 设计目标：全局变量、全局数据类型和函数的声明

二. 关键任务：

1. 服务模块的数据类型描述
   ```
   struct server_module { void* handle; const char* name; void (*generate_function) (int); };
   ```

2. 服务模块的装载与卸载
   ```
   extern struct server_module* module_open (const char* module_name);
   extern void module_close (struct server_module* module);
   ```

3. 服务器运行
   ```
   extern void server_run (struct in_addr local_address, uint16_t port);
   ```

### common.cpp
设计目标：通用函数的实现，有就统一实现在此文件中

### module.cpp

一. 设计目标：实现服务模块的装载与卸载函数

二. 关键任务：
1. 服务模块装载
   - 获取服务模块（动态库）的完整路径
   - 装载动态库
   - 解析动态库中的模块生成函数，执行之

2. 服务模块卸载
   - 注意释放所有不再需要的动态分配内存

### server.cpp

一. 设计目标：实现Web服务器的基本功能

二. 关键任务:
1. 服务器运行函数
   - 使用套接字创建Web服务器
   - 处理客户Web请求，在子进程中创建单独连接，并响应

2. 客户Web请求响应
   - 连接请求响应：GET请求响应（必须实现）
   - 其他请求响应（非必需实现内容）

### HTML网页模板

```
/* HTTP response and header for a successful request. */
static char* ok_response =
  "HTTP/1.0 200 OK\n"
  "Content-type: text/html\n"
  "\n";

/* HTTP response, header, and body, indicating that we didn’t understand the request. */
static char* bad_request_response =
  "HTTP/1.0 400 Bad Request\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  "<body>\n"
  "<h1>Bad Request</h1>\n"
  "<p>This server did not understand your request.</p>\n"
  "</body>\n"
  "</html>\n";

/* HTTP response, header, and body template, indicating that the requested document was not found. */
static char* not_found_response_template =
  "HTTP/1.0 404 Not Found\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  "<body>\n"
  "<h1>Not Found</h1>\n"
  "<p>The requested URL %s was not found on this server.</p>\n"
  "</body>\n"
  "</html>\n";

/* HTTP response, header, and body template, indicating that the method was not understood. */
static char* bad_method_response_template =
  "HTTP/1.0 501 Method Not Implemented\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  "<body>\n"
  "<h1>Method Not Implemented</h1>\n"
  "<p>The method %s is not implemented by this server.</p>\n"
  "</body>\n"
  "</html>\n";
```

### main.cpp

一. 设计目标
主程序，解析用户输入的命令行参数，启动服务器

二. 关键任务
1. 服务器启动与响应Web请求
   服务器启动命令：```./server  --address  localhost  --port  8008```
   Web请求：```http://localhost:8008/diskfree```

2. 服务器启动选项
   ```-a/--address```（服务器地址）、
   ```-h/--help```（帮助）、
   ```-m/--modir```（服务模块目录）、
   ```-p/--port```（服务器端口）、
   ```-v/--verbose```（冗长运行状态，在此状态下输出详细运行信息）
   短选项格式：```“a:hm:p:v”```（凡是选项后带附加参数的需要添加一个冒号）

## 动态库细节提示

### time.cpp

设计目标：生成一个简单HTML网页，显示系统当前时间

关键任务：实现函数``module_generate``（参数：客户套接字的文件描述符），将系统时间转换为字符串

**HTML网页模板**
```
static char* page_template =
"<html>\n" "<head>\n"
"<meta http-equiv=\"refresh\" content=\"5\">\n"
"</head>\n" "<body>\n" "<p>The current time is %s.</p>\n"
"</body>\n" "</html>\n";
```

### issue.cpp

设计目标：生成一个简单HTML网页，显示系统发布信息

关键任务：实现函数```module_generate```（参数：客户套接字的文件描述符），读取 /```proc/issue ```文件中的信息

**HTML网页模板**
```
static char* page_start = "<html>\n" "<body>\n" "<pre>\n";
static char* page_end = "</pre>\n" "</body>\n" "</html>\n";
static char* error_page =
"<html>\n"
"<body>\n"
"<p>Error: Could not open /proc/issue.</p>\n"
"</body>\n"
"</html>\n";
```

### diskfree.cpp

设计目标：生成一个简单HTML网页，显示磁盘空闲信息

关键任务：实现函数```module_generate```（参数：客户套接字的文件描述符），启动新进程，调用 ``df ``命令获取磁盘空闲信息，将其输出流挂接到套接字的输入流上

**HTML网页模板**
```
static char* page_start =   "<html>\n"  "<body>\n"  "<pre>\n";
static char* page_end =  "</pre>\n"  "</body>\n"  "</html>\n";
```

### process.cpp

设计目标：生成一个简单HTML网页，显示运行进程信息

关键任务：实现函数```module_generate```（参数：客户套接字的文件描述符），读取并解析 ```/proc ```中的信息

**HTML网页模板**
```
static char* page_start =
  "<html>\n" " <body>\n"
  " <table cellpadding=\"4\" cellspacing=\"0\" border=\"1\">\n" 
   "<thead>\n" "<tr>\n" "<th>PID</th>\n" "<th>Program</th>\n"
     "<th>User</th>\n"  " <th>Group</th>\n" "<th>RSS&nbsp;(KB)</th>\n"
       "</tr>\n" "</thead>\n" "<tbody>\n";

static char* page_end =
  "</tbody>\n" " </table>\n" " </body>\n" "</html>\n";
```
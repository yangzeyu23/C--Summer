#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <stdexcept>

// 进程池类模板
template <typename Task>
class ProcessPool {
public:
    static ProcessPool<Task>& getInstance(size_t processCount = 4) {
        static ProcessPool<Task> instance(processCount);
        return instance;
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void run() {
        if (isRunning) {
            throw std::runtime_error("Process pool is already running.");
        }
        isRunning = true;

        for (size_t i = 0; i < processCount; ++i) {
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                throw std::runtime_error("Failed to create pipe.");
            }
            pipes.push_back({pipefd[0], pipefd[1]});

            pid_t pid = fork();
            if (pid < 0) {
                throw std::runtime_error("Failed to fork process.");
            } else if (pid == 0) {
                close(pipefd[1]);
                childProcess(pipefd[0]);
                exit(0);
            } else {
                close(pipefd[0]);
                childPIDs.push_back(pid);
            }
        }

        parentProcess();
    }

    void stop() {
        if (!isRunning) return;

        for (pid_t pid : childPIDs) {
            kill(pid, SIGTERM);
            waitpid(pid, nullptr, 0);
        }
        childPIDs.clear();
        isRunning = false;
    }

    ~ProcessPool() {
        stop();
        for (auto& pipe : pipes) {
            close(pipe[0]);
            close(pipe[1]);
        }
    }

private:
    size_t processCount;
    std::vector<Task> tasks;
    std::vector<std::array<int, 2>> pipes; // 使用 std::array 替代 int[2]
    std::vector<pid_t> childPIDs;
    bool isRunning = false;

    ProcessPool(size_t processCount) : processCount(processCount) {}

    ProcessPool(const ProcessPool&) = delete;
    ProcessPool& operator=(const ProcessPool&) = delete;

    void parentProcess() {
        size_t taskIndex = 0;
        size_t pipeIndex = 0;

        while (taskIndex < tasks.size()) {
            int writePipe = pipes[pipeIndex][1];
            const Task& task = tasks[taskIndex];

            write(writePipe, &task, sizeof(Task));

            taskIndex++;
            pipeIndex = (pipeIndex + 1) % processCount;
        }

        for (auto& pipe : pipes) {
            close(pipe[1]);
        }
    }

    void childProcess(int readPipe) {
        Task task;
        while (read(readPipe, &task, sizeof(Task)) > 0) {
            task.execute();
        }
    }
};

// 示例任务类
class ExampleTask {
public:
    ExampleTask() : id(-1) {} // 默认构造函数
    ExampleTask(int id) : id(id) {}

    void execute() const {
        std::cout << "Processing task " << id << " in process " << getpid() << std::endl;
    }

private:
    int id;
};

int main() {
    auto& pool = ProcessPool<ExampleTask>::getInstance(3);

    for (int i = 0; i < 10; ++i) {
        pool.addTask(ExampleTask(i));
    }

    pool.run();
    return 0;
}
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

// 互斥锁封装类
class Mutex {
public:
    void lock() {
        mtx.lock();
    }

    void unlock() {
        mtx.unlock();
    }

private:
    std::mutex mtx;
};

// 信号量封装类
class Semaphore {
public:
    explicit Semaphore(int count = 0) : count(count) {}

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        --count;
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

// 条件变量封装类
class ConditionVariable {
public:
    void wait(std::unique_lock<std::mutex>& lock) {
        cv.wait(lock);
    }

    template <typename Predicate>
    void wait(std::unique_lock<std::mutex>& lock, Predicate pred) {
        cv.wait(lock, pred);
    }

    void notify_one() {
        cv.notify_one();
    }

    void notify_all() {
        cv.notify_all();
    }

private:
    std::condition_variable cv;
};

// 线程池类模板
template <typename Task>
class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount) : stop(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back(&ThreadPool::workerThread, this);
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

    void addTask(const Task& task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.push(task);
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> workers;
    std::queue<Task> tasks;
    std::mutex queueMutex;
    ConditionVariable condition;
    std::atomic<bool> stop;

    static void workerThread(ThreadPool* pool) {
        while (true) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(pool->queueMutex);
                pool->condition.wait(lock, [pool]() { return pool->stop || !pool->tasks.empty(); });
                if (pool->stop && pool->tasks.empty()) {
                    return;
                }
                task = pool->tasks.front();
                pool->tasks.pop();
            }
            task.execute();
        }
    }
};

// 示例任务类
class ExampleTask {
public:
    ExampleTask() : id(-1) {} // 默认构造函数
    explicit ExampleTask(int id) : id(id) {}

    void execute() const {
        std::cout << "Processing task " << id << " in thread " << std::this_thread::get_id() << std::endl;
    }

private:
    int id;
};

int main() {
    ThreadPool<ExampleTask> pool(3);

    for (int i = 0; i < 10; ++i) {
        pool.addTask(ExampleTask(i));
    }

    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟主线程工作
    return 0;
}
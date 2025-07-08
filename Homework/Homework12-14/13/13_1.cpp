//注意必须在 Linux 环境下运行

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// 初始化信号量的函数
void set_semaphore_value(int semid, int value) {
    semctl(semid, 0, SETVAL, value);
}

// P操作（等待信号量）
void semaphore_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}

// V操作（释放信号量）
void semaphore_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

int main() 
{
    // 创建二元信号量
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        return 1;
    }

    // 初始化信号量为0
    set_semaphore_value(semid, 0);

    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("fork failed");
        semctl(semid, 0, IPC_RMID); // 删除信号量
        return 1;
    } 
    else if (pid == 0) 
    {
        // 子进程
        cout << "子进程开始执行..." << endl;

        // 模拟子进程的工作
        sleep(2);

        cout << "子进程完成工作，释放信号量。" << endl;
        semaphore_signal(semid);
        return 0;
    } 
    else 
    {
        // 父进程
        cout << "父进程等待子进程完成..." << endl;

        semaphore_wait(semid); 

        cout << "父进程检测到子进程完成。" << endl;

        wait(nullptr);

        semctl(semid, 0, IPC_RMID);
        cout << "父进程释放信号量并退出。" << endl;
    }

    return 0;
}
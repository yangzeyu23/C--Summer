#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static char* page_start = "<html>\n" "<body>\n" "<pre>\n";
static char* page_end = "</pre>\n" "</body>\n" "</html>\n";

extern "C" void module_generate(int fd) {
    pid_t child_pid;
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return;
    }
    
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return;
    }
    
    if (child_pid == 0) {
        close(pipe_fd[0]);
        
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        
        execlp("df", "df", "-h", NULL);
        
        perror("execlp");
        exit(1);
    } else {
        
        close(pipe_fd[1]);
        
        write(fd, page_start, strlen(page_start));
        
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            write(fd, buffer, bytes_read);
        }
        
        write(fd, page_end, strlen(page_end));
        
        close(pipe_fd[0]);
        
        waitpid(child_pid, NULL, 0);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>

static char* page_start =
  "<html>\n" " <body>\n"
  " <table cellpadding=\"4\" cellspacing=\"0\" border=\"1\">\n" 
   "<thead>\n" "<tr>\n" "<th>PID</th>\n" "<th>Program</th>\n"
     "<th>User</th>\n"  " <th>Group</th>\n" "<th>RSS&nbsp;(KB)</th>\n"
       "</tr>\n" "</thead>\n" "<tbody>\n";

static char* page_end =
  "</tbody>\n" " </table>\n" " </body>\n" "</html>\n";

static int get_process_rss(pid_t pid) {
    char statm_path[100];
    FILE* statm_file;
    int rss = 0;
    
    snprintf(statm_path, sizeof(statm_path), "/proc/%d/statm", pid);
    
    statm_file = fopen(statm_path, "r");
    if (statm_file != NULL) {
        int size, resident, share, text, lib, data, dt;
        if (fscanf(statm_file, "%d %d %d %d %d %d %d", 
                  &size, &resident, &share, &text, &lib, &data, &dt) == 7) {
            rss = resident * (getpagesize() / 1024);
        }
        fclose(statm_file);
    }
    
    return rss;
}

static char* get_process_name(pid_t pid) {
    char cmdline_path[100];
    FILE* cmdline_file;
    static char cmdline[256];
    
    snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", pid);
    
    cmdline_file = fopen(cmdline_path, "r");
    if (cmdline_file != NULL) {
        size_t bytes_read = fread(cmdline, 1, sizeof(cmdline) - 1, cmdline_file);
        if (bytes_read > 0) {
            cmdline[bytes_read] = '\0';
            for (size_t i = 0; i < bytes_read - 1; i++) {
                if (cmdline[i] == '\0') {
                    cmdline[i] = ' ';
                }
            }
        } else {
            fclose(cmdline_file);
            char comm_path[100];
            snprintf(comm_path, sizeof(comm_path), "/proc/%d/comm", pid);
            FILE* comm_file = fopen(comm_path, "r");
            if (comm_file != NULL) {
                if (fgets(cmdline, sizeof(cmdline), comm_file) != NULL) {
                    size_t len = strlen(cmdline);
                    if (len > 0 && cmdline[len - 1] == '\n') {
                        cmdline[len - 1] = '\0';
                    }
                } else {
                    strcpy(cmdline, "[unknown]");
                }
                fclose(comm_file);
            } else {
                strcpy(cmdline, "[unknown]");
            }
            return cmdline;
        }
        fclose(cmdline_file);
    } else {
        strcpy(cmdline, "[unknown]");
    }
    
    return cmdline;
}

static void get_process_owner(pid_t pid, char* user, char* group, size_t size) {
    char stat_path[100];
    struct stat stat_buf;
    
    snprintf(stat_path, sizeof(stat_path), "/proc/%d", pid);
    
    if (stat(stat_path, &stat_buf) == 0) {
        struct passwd* pw = getpwuid(stat_buf.st_uid);
        struct group* gr = getgrgid(stat_buf.st_gid);
        
        if (pw != NULL) {
            strncpy(user, pw->pw_name, size);
            user[size - 1] = '\0';
        } else {
            snprintf(user, size, "%d", stat_buf.st_uid);
        }
        
        if (gr != NULL) {
            strncpy(group, gr->gr_name, size);
            group[size - 1] = '\0';
        } else {
            snprintf(group, size, "%d", stat_buf.st_gid);
        }
    } else {
        strncpy(user, "unknown", size);
        strncpy(group, "unknown", size);
    }
}

extern "C" void module_generate(int fd) {
    DIR* proc_dir;
    struct dirent* entry;
    char buffer[1024];
    
    write(fd, page_start, strlen(page_start));
    
#ifdef __APPLE__
    FILE* ps_pipe = popen("ps -axo pid,comm,user,group,rss", "r");
    if (ps_pipe != NULL) {
        char line[1024];
        fgets(line, sizeof(line), ps_pipe);
        
        while (fgets(line, sizeof(line), ps_pipe) != NULL) {
            pid_t pid;
            char comm[256], user[256], group[256];
            int rss;
            
            if (sscanf(line, "%d %255s %255s %255s %d", &pid, comm, user, group, &rss) == 5) {
                snprintf(buffer, sizeof(buffer),
                         "<tr><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%d</td></tr>\n",
                         pid, comm, user, group, rss);
                write(fd, buffer, strlen(buffer));
            }
        }
        pclose(ps_pipe);
    }
#else
    proc_dir = opendir("/proc");
    if (proc_dir != NULL) {
        while ((entry = readdir(proc_dir)) != NULL) {
            pid_t pid = atoi(entry->d_name);
            if (pid > 0) {
                char user[256], group[256];
                char* program;
                int rss;
                
                program = get_process_name(pid);
                get_process_owner(pid, user, group, sizeof(user));
                rss = get_process_rss(pid);
                
                snprintf(buffer, sizeof(buffer),
                         "<tr><td>%d</td><td>%s</td><td>%s</td><td>%s</td><td>%d</td></tr>\n",
                         pid, program, user, group, rss);
                write(fd, buffer, strlen(buffer));
            }
        }
        closedir(proc_dir);
    }
#endif
    
    write(fd, page_end, strlen(page_end));
}
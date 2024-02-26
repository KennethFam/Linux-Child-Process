#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

void sig_handler(int num) {
}

int main() {
    signal(SIGINT, sig_handler);
    pid_t pid;
    pid = fork();
    int status;
    int id;
    if (pid < 0) {
        printf("Fork Failed\n");
        return -1;
    }
    else if (pid == 0) {
        printf("childpid=%d\n", getpid());
        pause();
        exit(5);
    }
    else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exitstatus = WEXITSTATUS(status);
            printf("childpid=%d,exitstatus=%d\n", pid, WEXITSTATUS(status));
        }
        else {
            printf("Error: The child process exited abnormally.\n");
            return -1;
        }
    }
}

LAB 1

'''

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    pid_t child_pid;
    int status;
    printf("Parent process (PID: %d)\n", getpid());
    child_pid = fork();
    if (child_pid < 0){a
        perror("Fork failed");
        exit(1);
    }
    if (child_pid == 0){
        printf("Child process (PID: %d) is running\n", getpid());
        char *args[] = {"./child_program", NULL};
        execv(args[0], args);
        perror("Exec failed");
        exit(1);
    }
    else{
        printf("Parent process is waiting for the child to terminate...\n");
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process terminated with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not terminate normally\n");
        }
        printf("Parent process is done\n");
    }
    return 0;
}

'''

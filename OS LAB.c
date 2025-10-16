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


LAB 2 A

'''

#include <stdio.h>

void calculateFCFS(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n];
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time[i],
        turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n];
    int burst_time[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    calculateFCFS(processes, n, burst_time);
    return 0;
}

'''

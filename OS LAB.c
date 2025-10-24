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

LAB 2 B

'''

#include <stdio.h>

void findWaitingTime(int processes[], int n, int burst_time[], int waiting_time[]) {
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = 0;
        for (int j = 0; j < i; j++) {
            waiting_time[i] += burst_time[j];
        }
    }
}

void findTurnaroundTime(int processes[], int n, int burst_time[], int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}
    
void findAverageTimes(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n];
    findWaitingTime(processes, n, burst_time, waiting_time);
    findTurnaroundTime(processes, n, burst_time, waiting_time,
    turnaround_time);
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i],
        waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    findAverageTimes(processes, n, burst_time);
    return 0;
}

'''

LAB 2 C

'''

#include <stdio.h>
#define MAX_PROCESS 10

int min(int a, int b) {
    return (a < b) ? a : b;
}

void calculateTurnaroundTimeWaitingTime(int processes[], int n, int burst_time[], int time_quantum) {
    int remaining_time[MAX_PROCESS];
    int waiting_time[MAX_PROCESS] = {0};
    int turnaround_time[MAX_PROCESS] = {0};
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }
    int t = 0; 
    int done = 0;
    while (!done) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0){
                done = 0;
                int time_slice = min(time_quantum, remaining_time[i]);
                t += time_slice;
                remaining_time[i] -= time_slice;
                waiting_time[i] = t - burst_time[i];
                    if (remaining_time[i] == 0) {
                        turnaround_time[i] = t;
                    }
            }
        }
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
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i],
        waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[MAX_PROCESS], burst_time[MAX_PROCESS];
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    calculateTurnaroundTimeWaitingTime(processes, n, burst_time, time_quantum);
    return 0;
}


'''


LAB 2 D

'''

#include <stdio.h>
#define MAX_PROCESS 10

void findWaitingTimeTurnaroundTime(int processes[], int n, int burst_time[], int priority[], int waiting_time[], int turnaround_time[]) {
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = 0;
        for (int j = 0; j < i; j++) {
            waiting_time[i] += burst_time[j];
        }
        for (int i = 0; i < n; i++) {
            turnaround_time[i] = burst_time[i] + waiting_time[i];
        }
    }
}

void findAverageTimes(int processes[], int n, int burst_time[], int priority[]){
    int waiting_time[MAX_PROCESS], turnaround_time[MAX_PROCESS];
    findWaitingTimeTurnaroundTime(processes, n, burst_time, priority,
    waiting_time, turnaround_time);
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i],
        priority[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[MAX_PROCESS], burst_time[MAX_PROCESS],
    priority[MAX_PROCESS];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &priority[i]);
    }
    findAverageTimes(processes, n, burst_time, priority);
    return 0;
}

'''

LAB 3

'''

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t mutex, full, empty;
void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        pthread_exit(NULL);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}

'''

LAB 4

'''

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256

void writer_process() {
    int fd;
    char message[BUFFER_SIZE];
    mkfifo(FIFO_NAME, 0666);
    printf("Writer process opening FIFO...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("Enter a message to send to the reader process (type 'exit' to end):\n");
    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        message[strlen(message) - 1] ='\0';
        write(fd, message, strlen(message) + 1);
        if (strcmp(message, "exit") == 0)
        break;
    }
    close(fd);
    unlink(FIFO_NAME);
    printf("Writer process finished.\n");
}

void reader_process() {
    int fd;
    char message[BUFFER_SIZE];
    printf("Reader process opening FIFO...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("Reader process waiting for messages...\n");
    while (1) {
        read(fd, message, BUFFER_SIZE);
        if (strcmp(message, "exit") == 0)
            break;
            printf("Received message: %s\n", message);
        }
    close(fd);
    printf("Reader process finished.\n");
}

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        reader_process();
    } else {
        writer_process();
    }
    return 0;
}

'''

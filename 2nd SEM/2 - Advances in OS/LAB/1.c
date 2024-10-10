// 1. Develop an application using process control APIs to demonstrate virtualization of CPU and Virtualization of memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_CHILDREN 3

void cpu_intensive_task(int n) {
	// Simulate a CPU-intensive calculation (e.g., factorial)
	long result = 1;
	for (int j = 1; j <= n; j++) {
	    result *= j;
	}
	printf("Child process (PID: %d): Factorial of %d is %ld\n", getpid(), n, result);
    
}

void memory_intensive_task(int n) {
        // Simulate memory allocation and usage
        int *arr = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[j] = j;
        }
        printf("Child process (PID: %d): Memory allocated and used at %p\n", getpid(), arr);
        free(arr);
  
}

int main() {
    pid_t pids[NUM_CHILDREN];

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork failed");
            return 1;
        } 
        else if (pids[i] == 0) {
            // Child process
            if (i == 0) {
                printf("Child process (PID: %d) performing CPU-intensive task...\n\n", getpid());
                cpu_intensive_task(5);
            } 
            else if (i == 1) {
                printf("Child process (PID: %d) performing memory-intensive task...\n\n", getpid());
                memory_intensive_task(5);
            } 
            else if (i == 2) {
                printf("Child process (PID: %d) performing mixed tasks...\n\n", getpid());
                cpu_intensive_task(3);
                memory_intensive_task(2);
            }
            exit(0);
        }
        else {
            printf("Parent process (PID: %d) performing CPU-intensive task...\n\n", getpid());
            cpu_intensive_task(6);
        }
    }

    printf("All child processes completed.\n");

    return 0;
}

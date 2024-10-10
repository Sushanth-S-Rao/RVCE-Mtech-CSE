#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

// Function executed by each thread
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    int local_var = 0;

    // Print thread ID and address of local variable
    printf("Thread %d: Local variable address = %p\n", thread_id, &local_var);

    // Increment local variable in a loop
    for (int i = 0; i < 5; i++) {
        local_var++;
        printf("Thread %d: Local variable = %d\n", thread_id, local_var);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        if (result != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

/*
Explanation:
Thread Function (thread_function):

Each thread executes thread_function independently.
thread_id identifies each thread, and local_var is a local variable specific to each thread.
The address of local_var is printed to demonstrate that each thread has its own stack space.
Thread Creation (pthread_create):

pthread_create creates threads using the function thread_function.
thread_ids array is passed to uniquely identify each thread.
Thread Synchronization (pthread_join):

pthread_join waits for each thread to complete execution before the main program continues.
Output:
The output demonstrates that each thread has its own stack memory (local variables), but they share the same program code and global memory space (including static variables).

Key Concepts:
Stack Memory: Each thread has its own stack memory where local variables are stored. 
This memory is private to each thread and is not shared among threads.

Virtual Memory Space: Threads in the same process share the same virtual memory space. 
This includes the program code, static variables, and heap memory allocated using malloc or similar functions.

Thread Safety: Threads must coordinate access to shared resources 
(such as global variables or dynamically allocated memory) using synchronization mechanisms like mutexes or semaphores 
to avoid race conditions and ensure data integrity.

Practical Application:
In real-world applications, threads are used to perform concurrent tasks, such as handling multiple client requests in a server application or parallelizing computations to utilize multi-core processors effectively. Memory virtualization ensures that each thread operates in its own isolated environment (stack memory) while efficiently sharing global resources (heap memory, program code) provided by the operating system.
*/
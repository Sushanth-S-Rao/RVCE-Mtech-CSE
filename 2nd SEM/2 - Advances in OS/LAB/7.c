#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>

int futex_wait(int *addr, int val) {
    return syscall(SYS_futex, addr, FUTEX_WAIT, val, NULL, NULL, 0);
}

int futex_wake(int *addr, int val) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, val, NULL, NULL, 0);
}

// Variables
int shared_variable = 0;
int futex_lock = 0;

// Thread function
void *worker(void *arg)
{
    // Acquire the futex lock
    while (__sync_lock_test_and_set(&futex_lock, 1) == 1) {
        syscall(SYS_futex, &futex_lock, FUTEX_WAIT, 1, NULL, NULL, 0);
    }

    // Critical section
    printf("Thread %d is in the critical section.\n", pthread_self());
    shared_variable++;
    printf("Shared variable to %d.\n", shared_variable);

    // Release the futex lock
    __sync_lock_release(&futex_lock);
    syscall(SYS_futex, &futex_lock, FUTEX_WAKE, 1, NULL, NULL, 0);

    return NULL;
}

int main()
{
    pthread_t threads[3];

    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, worker, NULL);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    printf("Shared variable after both threads: %d\n", shared_variable);

    return 0;
}

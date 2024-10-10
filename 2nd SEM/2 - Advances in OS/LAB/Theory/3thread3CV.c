// LOCKS

#include<stdio.h>
#include<pthread.h>
#include<assert.h>

int x = 7;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;             // INITIALISATION Method 1
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;        // CONDITION Variable Initialisation

void* worker(void* args) {
    pthread_mutex_lock(&mu);
    x += 10;
    printf("Thread WORKER executed safely and new work done = %d\n", x);
    // SIGNAL
    pthread_cond_signal(&condition);
    // wakes the thread
    pthread_mutex_unlock(&mu);

    return NULL;
}

void* doubler(void* args) {
    pthread_mutex_lock(&mu);
    while(x < 10) {
        // WAIT
        pthread_cond_wait(&condition, &mu);
        // Puts this thread to sleep, until signal is received, and lock is released
    }
    x *= 2;
    pthread_mutex_unlock(&mu);
    return NULL;
}

int main() {
    printf("Value of x = %d\n", x);
    pthread_t p[5];
    pthread_t q[2];

    // Initialize (Method 2)
    pthread_mutex_init(&mu, NULL);
    
    for(int i = 0; i < 5; i++) {
        if(i < 2)
            pthread_create(&q[i], NULL, doubler, NULL);
        pthread_create(&p[i], NULL, worker, NULL);
        
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(p[i], NULL);
        if(i < 2)
            pthread_join(q[i], NULL);
    }

    // pthread_cond_t condition;    
    // pthread_cond_init(&condition, NULL); 
    // THEN DESTROY pthread_cond_destroy(&condition)
    pthread_mutex_destroy(&mu);

    printf("FINAL: %d\n", x);    
    return 0;
}

/*
Condition variables are useful when some kind of signaling must take place between threads, 
if one thread is waiting for another to do something before it can continue. 


*/
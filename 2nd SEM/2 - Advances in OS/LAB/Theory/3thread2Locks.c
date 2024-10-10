// LOCKS

#include<stdio.h>
#include<pthread.h>
#include<assert.h>

int x = 7;
pthread_mutex_t mu;

void* worker(void* args) {
    // LOCK
    int rc = pthread_mutex_lock(&mu);
    assert(rc == 0);
    x += 1;
    printf("Thread WORKER executed safely and new work done = %d\n", x);
    // UNLOCK
    pthread_mutex_unlock(&mu);

    return NULL;
}

int main() {
    printf("Value of x = %d\n", x);
    pthread_t p;
    pthread_t q;

    // Initialize
    pthread_mutex_init(&mu, NULL);
    pthread_create(&p, NULL, worker, NULL);
    pthread_create(&q, NULL, worker, NULL);

    pthread_join(p, NULL);
    pthread_join(q, NULL);

    // Destroy
    pthread_mutex_destroy(&mu);
    
    return 0;
}

/*
//  pthread_mutex_t used to create MUTEXES (synchronization primitive)
    
    // INITIALIZE
    pthread_mutex_t lock;

    // a) lock = PTHREAD_MUTEX_INITIALIZER;
    // b) int rc = pthread_mutex_init(&lock);

    // LOCKING: SYNTAX = int pthread_mutex_lock(pthread_mutex_t *mutex)
    pthread_mutex_lock(&lock);
    // Critical Section
    // UNLOCKING:
    pthread_mutex_unlock(&lock);
    
    // DESTROY at last using pthread_mutex_destroy(&lock);

    //---------------------------------------------------
    pthread_mutex_trylock(&mu);             // Returns -1 if lock is already held
    pthread_mutex_timedlock(&mu, TIME);     // Returns -1 if TIME is up and still lock can't be obtained
*/
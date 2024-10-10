// 6. Implement Lock With Queues, Test-and-set, Yield, and Wakeup. 
// LOCKS

#include <stdio.h>
#include <stdlib.h>        
#include <unistd.h>        // For getpid(), gettid()
#include <pthread.h>       
#include <bits/stdc++.h>   
using namespace std;

struct lock_t {
    int flag;
    int guard;
    queue<pthread_t> q;
    lock_t(int f, int g) : flag(f), guard(g) {}
};

typedef struct lock_t lock_t;

// FUNCTION DECLARATIONS
void lock(lock_t *m);
int testAndSet(int *ptr, int newVal);
void unlock(lock_t *m);
void park(lock_t *m);
void printQ(queue<pthread_t> temp);

// GLOBAL DECLARATIONS
lock_t lock_struct(0, 0);
int x = -1;
int arr[6];

void lock(lock_t *m) {
    while(testAndSet(&m -> guard, 1) == 1)  // Acquire guard by spinning (Guard is a Spin Lock)
    { continue; } 
    if(m -> flag == 0) {
        m -> flag = 1;
        m -> guard = 0;
        cout << "FIRST Lock " << pthread_self() << " Acquired\n";
    } else {
        (m -> q).push(pthread_self());
        m -> guard = 0; 
        park(m);
    }
} // Loop terminates if lock->flag is 0 (that is lock is available), otherwise it spins till other process unlocks

int testAndSet(int *ptr, int newVal) {
    int old = *ptr;
    *ptr = newVal;
    return old;
}

void unlock(lock_t *m) {
    while(testAndSet(&m->guard, 1) == 1) // Acquire Guard Lock
    { continue; }
    cout << "Lock " << pthread_self() << " Released\n";
    m -> flag = 0;
    m -> guard = 0;
}

void park(lock_t *m) {
    while( (m->q).front() != pthread_self() )          
        sleep(1);
    while(m->flag == 1)
        sleep(1);

    m -> flag = 1;
    (m->q).pop();

    cout << "\nLock " << pthread_self() << " Acquired\n";
    printQ(m->q);
}

void *worker(void *arg) {
    lock(&lock_struct);

    // Critical section: Access shared resources
    cout << "Thread " << pthread_self() << " is in critical section\n";
    x += 1;
    arr[x] = x * 10;
    sleep(1);  // Simulate some work in the critical section

    unlock(&lock_struct);
    return NULL;
}

int main() {
    pthread_t threads[6];

    for (int i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, worker, NULL);

    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    cout << "\nArray Values: "; 
    for(int j = 0; j < 5; j++) 
        cout << arr[j] << ", ";

    return 0;
}


void printQ(queue<pthread_t> temp) {
    cout << "Threads sleeping in the queue: ";
    while(!temp.empty()) {
        cout << temp.front() << ", ";
        temp.pop();
    }
    cout << "\n";
}
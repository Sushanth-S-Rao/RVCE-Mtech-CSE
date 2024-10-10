// THREADS (27. Interlude: Threads API, Page 312)

#include<stdio.h>
#include<pthread.h>

// THREAD CREATION
// In order to write multi-threaded program, we should be able to create new threads
// Thread Creation interface must exist. In POSIX, it is pthread_create

void* worker(void* args) {
    printf("Thread WORKER in execution\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, worker, NULL);


    /* pthread_create( pthread_t* thread, 
                       const pthread_attr_t* attr,
                       void* (*start_routine)(void*),   // returns void*, takes void* parameter (basically WORKER declaration)
                       void* arg
                       )
    */
    // pthread_t* thread: Pointer to pthread_t structure
    // const pthread_attr_t* attr: To specify any attributes the thread has (scheduling ppt of thread, setting stack size). The attribute is set for a thread using call pthread_attr_init()
    // start_routine: void* (*start_routine)(void*) = worker; is a Function Pointer. Which fn should this thread start running in? 
    // arg: Argument to be passed to Function. Why void*? Bcos ANY type of data can be passed
    
    // THREAD COMPLETION
    pthread_join(thread, NULL);

    /*
    pthread_join(thread_t thread, void** value_ptr)
    // thread: which thread to wait for?
    // value_ptr: Pointer to return value you expect to get back
    // It is used to wait for a thread to terminate and obtain its return value
    // Parallel Program, that uses multiple threads, uses join to make sure every all work is completed

    worker returns void* (that contains data of struct type dino)
    dino *m = {"Brachiosaurus", 1240}
    pthread_join(thread, (void **) &m);    // type cast into (void **)
    // after the routine completes, if m is changed, it is reflected
    */

    return 0;
}

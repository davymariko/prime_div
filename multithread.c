#include "multithreadFactorization.h"


void multithreadInitialization(int threadnumber, char *fileRead, char *fileWrite){
    //mutexes, semaphores and buffers intialization
    int error = pthread_mutex_init(&mutex1, NULL);
    if (error != 0){printf("Mutex Error: Couldn't create the 1st mutex.\n");}
    error = pthread_mutex_init(&mutex2, NULL);
    if (error != 0){printf("Mutex Error: Couldn't create the 2nd mutex.\n");}
    error = sem_init(&empty1, 0, 2*threadnumber);
    if (error != 0){printf("Semaphore Error: Couldn't create the 1st empty semaphore.\n");}
    error = sem_init(&empty2, 0, 2*threadnumber);
    if (error != 0){printf("Semaphore Error: Couldn't create the 2nd empty semaphore.\n");}
    error = sem_init(&full1, 0, 0);
    if (error != 0){printf("Semaphore Error: Couldn't create the 1st full semaphore.\n");}
    error = sem_init(&full2, 0, 0);
    if (error != 0){printf("Semaphore Error: Couldn't create the 2nd full semaphore.\n");}
    buffer1 = malloc(2*threadnumber*sizeof(uint64_t));
    if (buffer1 == NULL){printf("Memory Error: Couldn't allocate the memory for the 1st buffer.\n");}
    buffer2 = malloc(2*threadnumber*sizeof(uint64_t *));
    if (buffer2 == NULL){printf("Memory Error: Couldn't allocate the memory for the 2nd buffer.\n");}

    //values initializations
    buffermaxitems = 2*threadnumber;
    buffer1first = 0;
    buffer1last = 0;
    buffer2first = 0;
    buffer2last = 0;
    readnotended = 1; //true, readthread hasn't ended reading the file yet
    shutdown = 0; //false, not in multithread shutdown

    //threads creation
    threadpool = malloc(threadnumber* sizeof(pthread_t));
    if (threadpool == NULL){printf("Memory Error: Couldn't allocate the memory for the threadpool.\n");}
    error = pthread_create(&threadRead, NULL, (void *) &readthread, fileRead);
    if (error != 0){printf("Thread Error: Couldn't create the reading thread.\n");}
    for (int i = 0; i < threadnumber; ++i) {
        pthread_t threadFactorize = pthread_self();
        threadpool[i] = threadFactorize;
        error = pthread_create(&threadpool[i], NULL, (void *) &factorize, NULL);
        if (error != 0){
            if (i==0){printf("Thread Error: Couldn't create the 1st factorization thread.\n");}
            else if (i==1){printf("Thread Error: Couldn't create the 2nd factorization thread.\n");}
            else if (i==2){printf("Thread Error: Couldn't create the 3rd factorization thread.\n");}
            else{printf("Thread Error: Couldn't create the %ith factorization thread.\n", i+1);}
        }
    }
    error = pthread_create(&threadWrite, NULL, (void *) &writethread, fileWrite);
    if (error != 0){printf("Thread Error: Couldn't create the writing thread.\n");}
}

void multithreadShutDown(){
    // threads termination
    int error = pthread_join(threadRead, NULL);
    if (error != 0){printf("Thread Error: Couldn't join the reading thread.\n");}
    error = pthread_join(threadWrite, NULL);
    if (error != 0){printf("Thread Error: Couldn't join the writing thread.\n");}
    shutdown = 1; //true, we can terminate the factorization threads which may be blocked on the semaphores
    for (int i = 0; i < threadnumber; ++i) {
        error = sem_post(&full1); //unlocking of the threads blocked by the semaphores
        if (error != 0){printf("Semaphore Error: Couldn't edit the 1st full semaphore.\n");}
        }
    for (int i = 0; i < threadnumber; ++i) {
        error = pthread_join(threadpool[i], NULL);
        if (error != 0){
            if (i==0){printf("Thread Error: Couldn't join the 1st factorization thread.\n");}
            else if (i==1){printf("Thread Error: Couldn't join the 2nd factorization thread.\n");}
            else if (i==2){printf("Thread Error: Couldn't join the 3rd factorization thread.\n");}
            else{printf("Thread Error: Couldn't join the %ith factorization thread.\n", i+1);}
        }
    }

    //buffers, threadpool, mutexes and semaphores liberation
    free(threadpool);
    free(buffer1);
    free(buffer2);
    error = sem_destroy(&empty1);
    if (error != 0){printf("Semaphore Error: Couldn't free the 1st empty semaphore.\n");}
    error = sem_destroy(&empty2);
    if (error != 0){printf("Semaphore Error: Couldn't free the 2nd empty semaphore.\n");}
    error = sem_destroy(&full1);
    if (error != 0){printf("Semaphore Error: Couldn't free the 1st full semaphore.\n");}
    error = sem_destroy(&full2);
    if (error != 0){printf("Semaphore Error: Couldn't free the 2nd full semaphore.\n");}
    error = pthread_mutex_destroy(&mutex1);
    if (error != 0){printf("Mutex Error: Couldn't free the 1st mutex.\n");}
    error = pthread_mutex_destroy(&mutex2);
    if (error != 0){printf("Mutex Error: Couldn't free the 2nd mutex.\n");}
}
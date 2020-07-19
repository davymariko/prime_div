#include "multithreadFactorization.h"


void factorize(){
    int sem;
    int error = sem_getvalue(&full1, &sem);
    if (error != 0){printf("Semaphore Error: Couldn't get the value of the 1st full semaphore.\n");}
    while (sem>0||readnotended) {//check if the first buffer is empty and is the reading thread is still running
        error = sem_wait(&full1);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 1st full semaphore.\n");}
        if (shutdown){break;}//true if in multithreadShutDown, we now want to end the factorization threads
        error = pthread_mutex_lock(&mutex1);
        if (error != 0){printf("Mutex Error: Couldn't lock the 1st mutex.\n");}
        uint64_t tofactorize = modify1(0); //gets a value from the first buffer
        error = pthread_mutex_unlock(&mutex1);
        if (error != 0){printf("Mutex Error: Couldn't unlock the 1st mutex.\n");}
        error = sem_post(&empty1);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 1st empty semaphore.\n");}
        uint64_t *value = optimizedFactorization(tofactorize);
        error = sem_wait(&empty2);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 2nd full semaphore.\n");}
        error = pthread_mutex_lock(&mutex2);
        if (error != 0){printf("Mutex Error: Couldn't lock the 2nd mutex.\n");}
        modify2(value); //adds a value to the second buffer
        error = pthread_mutex_unlock(&mutex2);
        if (error != 0){printf("Mutex Error: Couldn't unlock the 2nd mutex.\n");}
        error = sem_post(&full2);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 2nd empty semaphore.\n");}
        error = sem_getvalue(&full1, &sem);
        if (error != 0){printf("Semaphore Error: Couldn't get the value of the 1st full semaphore.\n");}
    }
}

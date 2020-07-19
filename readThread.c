#include "multithreadFactorization.h"


void readthread(char *filename){
    FILE *frd = fopen(filename, "r");
    if (frd == NULL){printf("File Error: Couldn't open the file %s.\n", filename);}
    towrite = 0; //number of lines we read
    char number[23];
    while (fgets(number, 23, frd) != NULL) {
        towrite++;
        uint64_t value = getint(number); //gets a number from a string
        int error = sem_wait(&empty1);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 1st empty semaphore.\n");}
        error = pthread_mutex_lock(&mutex1);
        if (error != 0){printf("Mutex Error: Couldn't lock the 1st mutex.\n");}
        modify1(value); //adds a value to the first buffer
        error = pthread_mutex_unlock(&mutex1);
        if (error != 0){printf("Mutex Error: Couldn't unlock the 1st mutex.\n");}
        error = sem_post(&full1);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 1st full semaphore.\n");}
    }
    readnotended = 0; //false, readthread has finished reading the file
    int error = fclose(frd);
    if (error != 0){printf("File Error: Couldn't close the file %s.\n", filename);}
}
#include "multithreadFactorization.h"


void writethread(char *filename){
    FILE *fd = fopen(filename, "w");
    if (fd == NULL){printf("File Error: Couldn't open the file %s.\n", filename);}
    uint64_t written = 0;
    int sem1;
    int sem2;
    int error = sem_getvalue(&full1, &sem1);
    if (error != 0){printf("Semaphore Error: Couldn't get the value of the 1st full semaphore.\n");}
    error = sem_getvalue(&full2, &sem2);
    if (error != 0){printf("Semaphore Error: Couldn't get the value of the 2nd full semaphore.\n");}
    while (sem1>0 || sem2>0||written!=towrite){ //checks if the two buffer are empty and if we wrote as many lines as they were in the original file
        error = sem_wait(&full2);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 2nd full semaphore.\n");}
        error = pthread_mutex_lock(&mutex2);
        if (error != 0){printf("Mutex Error: Couldn't lock the 2nd mutex.\n");}
        uint64_t  *tobewritten = modify2(NULL); //retrieves a value from the second buffer
        error = pthread_mutex_unlock(&mutex2);
        if (error != 0){printf("Mutex Error: Couldn't unlock the 2nd mutex.\n");}
        error = sem_post(&empty2);
        if (error != 0){printf("Semaphore Error: Couldn't edit the 2nd empty semaphore.\n");}
        uint64_t ints = tobewritten[0]; //number of prime divisors +1
        for (int i = 1; i < ints; ++i) {
            int len = intnumber(tobewritten[i]);
            char numb[len+2];//for the space and '\0'
            error = snprintf(numb, (len+2) * sizeof(char), "%lu ", tobewritten[i]);
            if (error != len+1){printf("Write Error: Couldn't format the numbers properly.\n");}
            int writteninfile = (int) fwrite(&numb, len+1, 1, fd);
            if (writteninfile != 1){printf("Write Error: Couldn't write in the file %s.\n", filename);}
        }
        int len = intnumber(tobewritten[ints]);//gets the number of digits we have to write
        char numb[len+2]; //for the line feed and '\0'
        error = snprintf(numb, (len+2) * sizeof(char), "%lu\n", tobewritten[ints]); //if len+1, \n will not be added properly
        if (error != len+1){printf("Write Error: Couldn't format the numbers properly.\n");}
        error = (int) fwrite(&numb, len+1, 1, fd);
        if (error != 1){printf("Write Error: Couldn't write in the file %s.\n", filename);}
        free(tobewritten);
        error = sem_getvalue(&full1, &sem1);
        if (error != 0){printf("Semaphore Error: Couldn't get the value of the 1st full semaphore.\n");}
        error = sem_getvalue(&full2, &sem2);
        if (error != 0){printf("Semaphore Error: Couldn't get the value of the 2nd full semaphore.\n");}
        written++;
    }
    error = fclose(fd);
    if (error != 0){printf("File Error: Couldn't close the file %s.\n", filename);}
}
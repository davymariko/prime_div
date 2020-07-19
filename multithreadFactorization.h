#ifndef MULTITHREAD_FACTORIZATION__H
#define MULTITHREAD_FACTORIZATION__H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <time.h>

sem_t empty1;
sem_t full1;
sem_t empty2;
sem_t full2;
uint64_t towrite;
int buffermaxitems;
uint64_t  *buffer1;
int buffer1first;
int buffer1last;
int threadnumber;
uint64_t **buffer2;
int buffer2first;
int buffer2last;
int shutdown;
int readnotended;
pthread_t threadRead;
pthread_t threadWrite;
pthread_t *threadpool;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;


void multithreadInitialization(int threadnumber, char *fileRead, char *fileWrite);
void multithreadShutDown();
void readthread(char *filename);
void writethread(char *filename);
void factorize();
int intnumber(uint64_t value);
uint64_t getint (char *string);
uint64_t *optimizedFactorization(uint64_t number);
uint64_t modify1(uint64_t value);
uint64_t add1(uint64_t value);
uint64_t remove1();
uint64_t *modify2(uint64_t *value);
uint64_t *add2(uint64_t *value);
uint64_t *remove2();
#endif

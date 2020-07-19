#include "multithreadFactorization.h"


uint64_t getint (char *string){
    uint64_t value = 0;
    if (*(string) == '-'){string = string+1;}
    int i = 0;
    for (; i < strlen(string)-1 && *(string + i + 2) != '\n'; ++i) {
        value += (uint64_t )*(string + i) - '0';
        value *= 10;
    }
    value += (uint64_t) *(string + i) - '0';
    return value;
}



int intnumber(uint64_t value){
    int counter = 0;
    while (value >= 1){
        counter++;
        value/=10;
    }
    return counter;
}
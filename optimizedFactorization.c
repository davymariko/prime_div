#include "multithreadFactorization.h"


uint64_t *optimizedFactorization(uint64_t number){
    uint64_t counter = 2; //indexes 0 and 1 are always used
    uint64_t *list = malloc(counter*sizeof(uint64_t));
    uint64_t **divisors_list = &list;
    if (*divisors_list == NULL){printf("Memory Error: Couldn't allocate memory for %lu.\n", number);}
    (*divisors_list)[1] = number;
    if (number%2==0 && number !=2){
        counter++;
        uint64_t *newlist = realloc(*divisors_list,counter*sizeof(uint64_t));
        if (newlist == NULL){printf("Memory Error: Couldn't reallocate memory for %lu.\n", *divisors_list[1]);}
        else{*divisors_list = newlist;}
        (*divisors_list)[counter-1] = 2;
        while(number%2==0){number /= 2;}
    }
    for(uint64_t div=3; div*div <= number && div < 4294967296; div+=2) {    //4 294 967 296 = 2^32, the square root of 2^64

        if (number%div==0){
            counter++;
            uint64_t *newlist = realloc(*divisors_list,counter*sizeof(uint64_t));
            if (newlist == NULL){printf("Memory Error: Couldn't reallocate memory for %lu.\n", *divisors_list[1]);}
            else{*divisors_list = newlist;}
            (*divisors_list)[counter-1] = div;
            while(number%div==0){number /= div;}
        }
    }
    if (number != 1 && counter != 2){
        counter++;
        uint64_t *newlist = realloc(*divisors_list,counter*sizeof(uint64_t));
        if (newlist == NULL){printf("Memory Error: Couldn't reallocate memory for %lu.\n", *divisors_list[1]);}
        else{*divisors_list = newlist;}
        (*divisors_list)[counter-1] = number;
    }
    (*divisors_list)[0] = counter-1;
    return *divisors_list;
}

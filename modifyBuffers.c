#include "multithreadFactorization.h"


uint64_t modify1(uint64_t value){
    if (value == 0){return remove1();}
    else{return add1(value);}
}

uint64_t add1(uint64_t value){
    *(buffer1+buffer1last) = value;
    buffer1last++;
    if(buffer1last == buffermaxitems){buffer1last=0;}
    return 0;
}

uint64_t remove1(){
    uint64_t value = buffer1[buffer1first];
    buffer1first++;
    if(buffer1first == buffermaxitems){buffer1first=0;}
    return value;
}

uint64_t  *modify2(uint64_t *value){
    if (value == NULL){return remove2();}
    else{return add2(value);}
}

uint64_t *add2(uint64_t *value){
    buffer2[buffer2last] = value;
    buffer2last++;
    if(buffer2last == buffermaxitems){buffer2last=0;}
    return NULL;
}

uint64_t *remove2(){
    uint64_t *value = buffer2[buffer2first];
    buffer2first++;
    if(buffer2first == buffermaxitems){buffer2first=0;}
    return value;
}
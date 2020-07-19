#include "multithreadFactorization.h"

int main(int argc, char **argv) {
    if (argc < 3){printf("Argument Error: You gave too few arguments to the program.\n"); return -1;}
    if (argc == 3){
        threadnumber = 4;
        multithreadInitialization(threadnumber, argv[1], argv[2]);
    }
    if (argc > 3 && argc <= 5){
        char *arg = argv[1];
        if (arg[0] == '-' && arg[1] == 'N'){
            threadnumber = getint(argv[2]);
            multithreadInitialization(threadnumber, argv[3], argv[4]);
        }else{printf("Argument Error: You gave incorrect arguments to the program.\n"); return -1;}
    }else{printf("Argument Error: You gave too many arguments to the program.\n"); return -1;}
    multithreadShutDown();
    return 0;
}
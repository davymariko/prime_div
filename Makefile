.PHONY: test help clean factExec
.DEFAULT_GOAL = help
EXEC = fact
OBJ = intProcessing.o modifyBuffers.o optimizedFactorization.o factorize.o readThread.o writeThread.o multithread.o main.o
INPUT ?= example_input.txt
EASY_INPUT = easy_input.txt
OUTPUT ?= example_output.txt
EASY_OUTPUT = easy_output.txt
N ?= 4
CC=gcc
FLAGS =-lpthread -g -Wall -std=gnu99

all: fact cppcheck valgrind clear ## Run the factorization program, CppCheck tests and Valgrind test and clear temporary files

clean: ## Clear temporary files
	rm -f *.xml
	rm -f *.o
	rm -f $(EXEC) test


cppcheck: $(OBJ) ## Run CppCheck tests
	cppcheck --enable=all -v --suppress=missingIncludeSystem --inconclusive --xml --xml-version=2 $(OBJ) 2> cppcheck.xml

factExe: $(EXEC) ## Compile and run the factorization program. Arguments: [N (threadnumber), INPUT (input file), OUTPUT (output file)]
	./$(EXEC) -N $(N) $(INPUT) $(OUTPUT)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(FLAGS) 

help: ## Show help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-10s\033[0m %s\n", $$1, $$2}'


test: fact test_prime_divs.c ## Run C-unit tests
	$(CC) test_prime_divs.c intProcessing.c optimizedFactorization.c -o test -lcunit $(FLAGS)
	./test

valgrind: fact ## Run Valgrind test
	valgrind --xml=yes --xml-file="valgrind.xml" --leak-check=yes ./$(EXEC) -N $(N) $(EASY_INPUT) $(EASY_OUTPUT)

+main.o: main.c
	$(CC) -o $@ $< -c $(FLAGS)

multithread.o: multithread.c
	$(CC) -o $@ $< -c $(FLAGS)

factorize.o: factorize.c
	$(CC) -o $@ $< -c $(FLAGS)

intProcessing.o: intProcessing.c
	$(CC) -o $@ $< -c $(FLAGS)

modifyBuffers.o: modifyBuffers.c
	$(CC) -o $@ $< -c $(FLAGS)

optimizedFactorization.o: optimizedFactorization.c
	$(CC) -o $@ $< -c $(FLAGS)

readThread.o: readThread.c
	$(CC) -o $@ $< -c $(FLAGS)

writeThread.o: writeThread.c
	$(CC) -o $@ $< -c $(FLAGS)
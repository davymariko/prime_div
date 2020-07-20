# prime_div
A program wrote in C that calculates prime divisors of a list of numbers

It is a project that I developed with friends in the school setting at the "Univesithé Catholique de Louvain" in the beginning of 2020

**Collaboration tool used**: GitLab

**Environment**: Linux

**Collaborators**:

`Claessens Romain`
`Gabrys Luc`
`Jadoul Nicolas`
`Wodon Louis`

**Goal**

The main goal is to factorize numbers the most effective way by optimizing time and memory consumption.

**Installation**

You can use ``make `` or ``make help`` to have more information about what you can do with our `Makefile`

usable commands:

* ``make fact``
* ``make test``
* ``make clean``
* ``make factExe``
* ``make all``
* ``make cppcheck``
* ``make valgrind``

**Caution using the program**

If you want this program to work correctly, you are supposed to give the arguments in this order, with elements inside brackets optional:

[-N ``threadNumber``] ``FileRead`` ``FileWrite``

where ``threadNumber`` must be an integer bigger than 0,

``fileRead`` must be a valid file path, containing only integers strictly bigger than 0, strictly smaller than 
$$
2^{64}
$$
 (18,446,744,073,709,551,616), followed by a line feed (\n)

``FileWrite``must be a valid file path. 

#### ``FileWrite`` will be overwritten

**Structure**

You can find these files inside this repository:

* ``multithreadFactorization.h``: header file for our program

-> You can find more information about the different functions and what they do in these files:

* ``main.c``: launches the program and checks the arguments
* ``multithread.c``: launches and terminates the threads
* ``readThread.c``: function for the reading thread
* ``factorize.c``: function for the factorization threads
* ``writeThread.c``: function for the writing thread
* ``optimizedFactorization.c``: our factorization algorithm
* ``modifyBuffers.c``: adds or removes an item from a buffer
* ``intProcessing``: transforms a string to an integer or returns the number of digits of a number
* ``test_prime_divs.c``: tests for our program

<-

* `Makefile`

-> Basic files to the test the program

* ``example_input.txt``: contains random integers
* ``example_output.txt``: empty, hosts the results of the program
* ``easy_imput.txt``: easy input for Valgrind tests
* ``easy_output.txt``: Hosts the results of the function after Valgrind tests

<-

You can find these files in the repository *Files for performance tests*:

* ``smallrandom1000.txt``: contains 1000 integers between 2^{0} and 2^{16}
* ``smallrandom100000.txt``: contains 100,000 integers between 2^{0} and 2^{16}

* ``mediumrandom1000.txt``: contains 1000 integers between 2^{16} and 2^{32}
* ``mediumrandom100000.txt``: contains 100,000 integers between 2^{16} and 2^{32}

* ``bigrandom1000.txt``: contains 1000 integers between 2^{32} and 2^{64}
* ``bigrandom100000.txt``: contains 100,000 integers between 2^{32} and 2^{64}
* ``verybigrandom1000.txt``: contains 1000 integers between 2^{54} and 2^{64}
* ``verybigrandom100000.txt``: contains 100,000 integers between 2^{54} and 2^{64}
* ``primeFactorizationTime``: file with the time taken by our algorithm to factorize prime integers between 5\*10^{6} and 1.48\*10^{19}

**Factorization algorithm proficiency**

Our algorithm takes usually less than a second for a factorizable integer. For a prime number, it could take up to a minute.

**Dependance of the functions**

- main.c:
  - MultithreadInitialization      --> multithread.c
  - getInt                         --> intProcessing.c
  - MultithreadShutDown            --> multithread.c
- multithread.c:
  - readthread                     --> readThread.c
  - factorize                      --> factorize.c
  - writethread                    --> writeThread.c
- readThread.c:
  - getInt                         --> intProcessing.c
  - modify1                        --> modifyBuffers.c
- factorize.c:
  - modify1                        --> modifyBuffers.c
  - optimizedFactorization         --> optimizedFactorization.c
  - modify2                        --> modifyBuffers.c
- writeThread.c:
  - modify2                        --> modifyBuffers.c
  - intnumber                      --> intProcessing.c


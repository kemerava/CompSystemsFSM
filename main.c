
#include <stdio.h>
#include "utils.h"
#include "tests.h"

#define TRANSITIONSARRAYSIZEMAX 50 // the max number of transitions in the machine definitions
#define BOXSIZE 3  // one box of the array where there are the prev state, input, new state (size 3)
#define INPUTSMAX 250 // the maximum number of inputs that are in the input file

int
main(int argc, char *argv[]) {
    if (!tests()){
        printf("TestsFailedError: some tests failed, please, refer specific tests outputs for details\n");
        return 0;
    }

    char *transitionsFileName;
    char *inputFileName;
    int debug = 0;
    int *debugPointer = &debug;

    if (!parseArgs(argc, argv, &transitionsFileName, &inputFileName, debugPointer)){
        return 0;
    }

    // create the array that is going to be holding the machine definitions
    // the dimensions are originally the number of rows is not exceeding 50
    // the number of columns in each row is 3, with format {state, input, next state}
    // all are represented as the integers, so for states it remains such,
    // for the inputs needs to be converted to characters if needed to print
    int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE];

    // this is is the actual size of the populated part of the array with transitions,
    // if this is a 0 -> some error occurred in the file
    int arrayLength = createMachine(arrayTransitions, transitionsFileName);
    // this will be outputted for any error that occurred while reading transitions file
    // some errors (for example the file not opening) will have additional errors printed before that
    if (!arrayLength) {
        printf("error occurred while attempting to read the machine definition\n");
        return 0;
    } else{
        printf("FSM has %d transitions\n", arrayLength);
    }

    // go through the inputs and the states of the machines according to the machine definition
    int inputSuccess = moveInTheMachine(arrayTransitions, arrayLength, inputFileName, debug);

    // if error occurred while reading from the file and input transitions, print this error
    if (!inputSuccess) {
        printf("error occurred while attempting to move in the machine\n");
        return 0;
    }
    return 1;
}

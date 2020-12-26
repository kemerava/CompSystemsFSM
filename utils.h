#ifndef FSM_UTILS_H
#define FSM_UTILS_H

#include <stdio.h>

#define TRANSITIONSARRAYSIZEMAX 50 // the max number of transitions in the machine definitions
#define BOXSIZE 3  // one box of the array where there are the prev state, input, new state (size 3)
#define INPUTSMAX 250 // the maximum number of inputs that are in the input file

int createMachine(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE], char transitionsFileName[]);

int moveInTheMachine(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength, char inputFileName[], int debug);

void machineDefinition(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength);

void debugger(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength);

int populateMachineArray(FILE *infile, int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE]);

int mapInputs(FILE *infile, int debug, int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength);

int lookForEdge(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength, int *state, char input, int transition);

int parseArgs(int argc, char *argv[], char *transitionsFileName[], char *inputFileName[], int *debug);

int validateInput(char input);

int addEdgeIfUnique(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int prevState, char input, int nextState, int i);

#endif //FSM_UTILS_H

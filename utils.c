#include "utils.h"

// this function is the one responsible for processing the transitions file,
// that is having the machine definition
// it is responsible for getting the insides of the file into the array (returns the actual size of the array)
// if the error occurred at some point -> return 0
int createMachine(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE], char transitionsFileName[]) {
    FILE *infile;
    // try to open the file
    infile = fopen(transitionsFileName, "r");

    // exit with the 0 error code if the error occurred while opening file
    if (infile == NULL) {
        printf("FileOpenError: unable to open file with the machine definition\n");
        return 0;
    }
    printf("processing FSM definition file %s\n", transitionsFileName);

    // this is the function to populate the array that was allocated
    // for the machine definition, it returns the number of edges
    // that were added to the machine, or 0 if the error occurred
    // (which will signify error on return from this function too)
    int length = populateMachineArray(infile, array);

    // clean up, closing the file
    fclose(infile);
    // return the number of lines we read in the file,
    // which is also the true amount of slots that are filled in the array
    return length;
}

// this function is printing out the steps that are taken inside the machine
// while reading the inputs form the file,
// it is printing out what is inside this file
int moveInTheMachine(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength, char inputFileName[], int debug) {

    FILE *infile;
    infile = fopen(inputFileName, "r");

    // if the error occurred while opening the file, print the error, exit with the 0 code
    if (infile == NULL) {
        printf("FileOpenError: unable to open file with the inputs\n");
        return 0;
    }

    printf("processing FSM inputs file %s\n", inputFileName);
    // this function maps the inputs from the file and the current state with the edges,
    // if they exist in the definition, otherwise it will return 0 (error)
    int numInputs = mapInputs(infile, debug, arrayTransitions, arrayLength);

    // close the file
    fclose(infile);
    return numInputs;
}

// function that is the used for debugging, takes in the array and the length of the array,
// does not return anything, prompts user for the debug command and only exits back to caller
// if the command was 'n'
void debugger(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength){
    // get the debugger command from the user
    char debugOption;
    printf("FSM debugger>");
    scanf(" %c", &debugOption);
    // only go to looking for the transition and printing it if command 'n' was inputted
    while (debugOption!='n'){
        // if p was inputted print out the current machine state and continue prompting until 'n' would be inputted
        if (debugOption=='p'){
            machineDefinition(arrayTransitions, arrayLength);
        }
            // if not 'n' or 'p' print error anc continue prompting for command
        else {
            printf("InvalidDebuggerCommandError: command not found. Please, type 'p' to print current state or 'n' to move further\n" );
        }
        printf("FSM debugger> ");
        scanf(" %c", &debugOption);
    }
}

// debugger helper function, which is printing the current state of the machine
void machineDefinition(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength) {
    // print the number of the transition in the machine definition
    printf("FSM has %d transitions\n", arrayLength);
    int loop;
    // go though the machine and print out the transitions
    for (loop = 0; loop < arrayLength; loop++) {
        printf("transition %d: state %d with input %c goes to state %d\n", loop, arrayTransitions[loop][0],
               arrayTransitions[loop][1], arrayTransitions[loop][2]);

    }
}

int populateMachineArray(FILE *infile, int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE]){
    int i = 0;
    int prevState;
    char input;
    int nextState;
    int line = fscanf(infile, "%d:%c>%d\n", &prevState,  &input, &nextState);;

    while ((line != EOF) ){
        // if we reached the maximum amount of transitions, notify the user and omit the rest of file
        if (i >= TRANSITIONSARRAYSIZEMAX){
           printf("maximum allowed transitions limit reached, the rest of edges will be omitted\n");
           break;
        }
        // if the error occurred while retrieving the line, for example, if the format wasn't valid,
        // close the file and exit with the error code 0
        if (!line || !validateInput(input)){
            printf("LineFormatError: line in the transitions file contains errors or has an incorrect format\n");

            return 0;
        }
        // here we already know here that the format, the inputs and states are valid
        // check if the edge is unique, save and increment the count
        i = addEdgeIfUnique(array, prevState, input, nextState, i);
        // error message handled inside the function
        if (!i){
            return 0;
        }

        // the "line" variable is the indicator of if the operation finished successfully,
        // one of the reasons for this operation to fail is if the %d didn't return the number,
        // or that it did not follow the format “state:input>next state”
        line = fscanf(infile, "%d:%c>%d\n", &prevState,  &input, &nextState);
        // increment the counter of times we were in the loop
    }
    return i;
}

int mapInputs(FILE *infile, int debug, int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength){
    char input;
    // the initial state is always a 0
    int state = 0;
    int *statePointer = &state;
    int i = 0;

    // read one char at a time
    while (fscanf(infile, "%c\n", &input) != EOF) {
        // if we reached the maximum amount of transitions, notify the user and omit the rest of file
        if (i >= INPUTSMAX){
            printf("maximum allowed inputs limit reached, the rest of inputs will be omitted\n");
            break;
        }
        // enter the debugger if was started with the '-d' option
        if (debug){
            debugger(arrayTransitions, arrayLength);
        }
        // look for the edge in the array, return 1 if found, 0 if not;
        // exist if the edge wasn't found, it can be because the input is invalid,
        // but if the input is not valid it will not be found in the machine,
        // so we are not explicitly checking for it
        if (!lookForEdge(arrayTransitions, arrayLength, statePointer, input, i)) {
            printf("InvalidInputError: the input does not match to available inputs in machine definition\n");
            return 0;
        }
        i++;

    }
    printf("after %d steps, state machine finished successfully at state %d\n", i, state);
    return i;
}

int lookForEdge(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength, int *state, char input, int transition){
    // this is the loop that checks the what the the transition going to be
    // if we were not able to find the transition that means that either the input does not exist in machine
    // or there is no edge that goes from the current state with this input
    for (int j = 0; j < arrayLength; j++)
    {
        // if it was possible to find the edge in the definition,
        // assign the next state to be the state (state we are moving to)
        //set the inputFound flag to 1 (true)
        // break to stop looking
        if (arrayTransitions[j][0] == *state && ((char) arrayTransitions[j][1]) == input) {
            printf("\tat step %d, input %c transitions FSM from state %d to state %d\n", transition, input, *state, arrayTransitions[j][2]);
            *state = arrayTransitions[j][2];
            return 1;
        }
    }
    return 0;
}

int parseArgs(int argc, char *argv[], char **transitionsFileName, char **inputFileName, int *debug){
    if (argc==3){
        // strings with the argument names from the commandline
        *transitionsFileName = argv[1];
        *inputFileName = argv[2];
    }
    else if (argc==4){
        if (argv[1][0]!='-' || argv[1][1]!='d'){
            printf("InvalidArgumentError: the entered argument is invalid. Enter '-d' to enter debugger\n");
            return 0;
        }
        *debug = 1;
        // strings with the argument names from the commandline
        *transitionsFileName = argv[2];
        *inputFileName = argv[3];
    }
    else{
        printf("InsufficientNumberOfArgumentsError: the number of arguments provided is not correct\n");
        return 0;
    }
    return 1;
}

// checks if the input is the upper or lowercase letter, that is the allowed input
int validateInput(char input){
    return ((input >= 'a') && (input<= 'z')) || ((input >='A') && (input<= 'Z'));
}

// function that checks if the array of transitions already contains that edge
// if it does and the state is different -> error
// if the state is the same -> ignore that transition
// else add to the array
int addEdgeIfUnique(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int prevState, char input, int nextState, int i){
    int count = 0;
    while (count<i){
        // if this edge is already in the array
        if ((array[count][0] == prevState) && (char) array[count][1] == input){
            // if it leads to a different next state, that is the error, so return 0
            if (array[count][2] != nextState){
                printf("NondeterministicMachineError: the machine already contains the edge (%d, %c) with a different outcome %d\n",
                       array[count][0], array[count][1], array[count][2]);
                return 0;
            }
            // if it leads to the same next state, then just omit it (don't increment i)
            else{
                return i;
            }
        }
        count++;
    }
    array[i][0] = prevState;
    array[i][1] = (int) input;
    array[i][2] = nextState;
    i++;
    return i;
}

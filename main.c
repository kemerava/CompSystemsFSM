#include <stdio.h>

#define TRANSITIONSARRAYSIZEMAX 50 // the max number of transitions in the machine definitions
#define BOXSIZE 3  // one box of the array where there are the prev state, input, new state (size 3)
#define INPUTSMAX 250 // the maximum number of inputs that are in the input file

int readTransitions(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE], char transitionsFileName[]);

int moveInTheMachine(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength, char inputFileName[], int debug);

void machineDefinition(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength);


int
main(int argc, char *argv[]) {
    char *transitionsFileName;
    char *inputFileName;
    int debug = 0;
    if (argc==3){
        // strings with the argument names from the commandline
        transitionsFileName = argv[1];
        inputFileName = argv[2];
    }
    else if (argc==4){
        if (argv[1][0]!='-' || argv[1][1]!='d'){
            printf("InvalidArgumentError: the entered argument is invalid. Enter '-d' to enter debugger");
            return 0;
        }
        debug = 1;
        // strings with the argument names from the commandline
        transitionsFileName = argv[2];
        inputFileName = argv[3];
    }
    else{
        printf("InsufficientNumberOfArgumentsError: the number of arguments provided is not correct\n");
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
    int arrayLength = readTransitions(arrayTransitions, transitionsFileName);
    // this will be outputted for any error that occurred while reading transitions file
    // some errors (for example the file not opening) will have additional errors printed before that
    if (!arrayLength) {
        printf("error occurred while attempting to read the machine definition\n");
        return 0;
    }

    // go through the inputs and the states of the machines according to the machine definition
    int inputSuccess = moveInTheMachine(arrayTransitions, arrayLength, inputFileName, debug);

    // if error occurred while reading from the file and input transitions, print this error
    if (!inputSuccess) {
        printf("error occurred while attempting to move in the machine\n");
        return 0;
    }

}

// this function is the one responsible for processing the transitions file,
// that is having the machine definition
// it is responsible for getting the insides of the file into the array (returns the actual size of the array)
// if the error occurred at some point -> return 0
int readTransitions(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE], char transitionsFileName[]) {
    FILE *infile;
    infile = fopen(transitionsFileName, "r");
    int i = 0;
    int prevState;
    char input;
    int nextState;

    // exit with the 0 error code if the error occurred while opening file
    if (infile == NULL) {
        printf("FileOpenError: unable to open file with the machine definition\n");
        return 0;
    }
    printf("processing FSM definition file %s\n", transitionsFileName);
    // the "line" variable is the indicator of if the operation finished successfully,
    // one of the reasons for this operation to fail is if the %d didn't return the number,
    // or that it did not follow the format “state:input>next state”
    int line = fscanf(infile, "%d:%c>%d\n", &prevState,  &input,
                      &nextState);

    // while there was no error, we haven't reached the end of the file
    // or we haven't reached the allowed number of inputs
    // get a line from the file at a time
    while ((line!=0) && (line != EOF) && i < TRANSITIONSARRAYSIZEMAX) {
        // here we already know here that the format, the inputs and states are valid
        // store the state, int value of the input and the next state in the single row of the machine definition array
        array[i][0] = prevState;
        array[i][1] = (int) input;
        array[i][2] = nextState;
        // get the next line
        line = fscanf(infile, "%d:%c>%d\n", &prevState, &input,
                        &nextState);

        // if the error occurred while retrieving the line, for example, if the format wasn't valid,
        // close the file and exit with the error code 0
        if (!line){
            fclose(infile);
            return 0;
        }
        // increment the counter of times we were in the loop
        i++;
    }

    // clean up, closing the file
    fclose(infile);
    printf("FSM has %d transitions\n", i);
    // return the number of lines we read in the file, which is also the true amount of slots that are filled in the array
    return i;
}

// this function is printing out the steps that are taken inside the machine
// while reading the inputs form the file,
// it is printing out what is inside this file
int moveInTheMachine(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength, char inputFileName[], int debug) {
    char input;
    // in the beginning we are always starting from the state 0
    char state = 0;

    FILE *infile;
    infile = fopen(inputFileName, "r");

    int i = 0;
    // this is the flag that defines if it was possible to find the input in the machine definition
    // if it was found, the flag is set to true,
    // if we exited the loop through away with this flag being 0 -> the input was not valid
    int inputFound = 0;

    // if the error occurred while opening the file, print the error, exit with the 0 code
    if (infile == NULL) {
        printf("FileOpenError: unable to open file with the inputs\n");
        return 0;
    }

    printf("processing FSM inputs file %s\n", inputFileName);
    // read one char at a time
    while ((fscanf(infile, "%c\n", &input) != EOF) && (i < INPUTSMAX)) {
        // enter the debugger if was started with the '-d' option 
        if (debug){
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
        // this is the loop that checks the what the the transition going to be
        // if we were not able to find the transition that means that either the input does not exist in machine
        // or there is no edge that goes from the current state with this input
        for (int j = 0; j < arrayLength; j++)
        {
            // if it was possible to find the edge in the definition,
            // assign the next state to be the state (state we are moving to)
            //set the inputFound flag to 1 (true)
            // break to stop looking
            if (arrayTransitions[j][0] == state && ((char) arrayTransitions[j][1]) == input) {
                printf("\tat step %d, input %c transitions FSM from state %d to state %d\n", i, input, state, arrayTransitions[j][2]);
                state = arrayTransitions[j][2];
                inputFound = 1;
                break;
            }
        }
        // increment the count of the inputs
        i++;
        // exist if the edge wasn't found
        if (!inputFound) {
            printf("InvalidInputError: the input does not match to available inputs in machine definition\n");
            fclose(infile);
            return 0;
        }
        // reset the inputFound flag
        inputFound = 0;
    }
    // close the file
    fclose(infile);

    printf("after %d steps, state machine finished successfully at state %d\n", i, state);
    return i;
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




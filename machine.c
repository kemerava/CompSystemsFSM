#include <stdio.h>

#define TRANSITIONSARRAYSIZEMAX 50 // the max number of transitions in the machine definitions
#define BOXSIZE 3  // one box of the array where there are the prev state, input, new state (size 3)
#define TRANSITIONSLINESIZE 5 // in the file with transitions how big is one line
#define INPUTSMAX 250

int validateInput(char input);

int readTransitions(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE]);

int checkFormat(char semicolon, char greaterThan);

void printTransitionsArray(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength);

int moveInTheMachine(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength);


int
main() {
    char input; // delete, dummy variable
    int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE];

    // this is is the actual size of the populated part of the array with transitions,
    // if this is a 0 -> some error occurred in the file
    int arrayLength = readTransitions(arrayTransitions);
    // this will be outputted for any error that occurred while reading transitions file
    // some errors (for example the file not opening) will have additional errors printed before that
    if (!arrayLength) {
        printf("Error occurred while attempting to read the machine definition.\n");
        return 0;
    }
    printTransitionsArray(arrayTransitions, arrayLength);

    int inputSuccess = moveInTheMachine(arrayTransitions, arrayLength);

    if (!inputSuccess) {
        printf("Error occurred while attempting to move in the machine.\n");
        return 0;
    }
}

//    printf("Input a state: ");
//    scanf("%c", &input);


// check if the input is one of the available ones
int
validateInput(char input) {
    if (input != 'a' && input != 'b' && input != 'c' &&
        input != 'd')    // check if the state is one of the 4 valid ones
    {
        printf("IncorrectInputError: the input %c is not valid.\n", input);    // if not print the error message
        return 0;
    }
    return 1;
}

// this function is the one responsible for the transitions file
// that is having the machine definition
// it is responsible for getting the insides of the file into the array (returns 1)
// if the error occurred at some point -> return 0
int readTransitions(int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE]) {
    FILE *infile;
    infile = fopen("/Users/elizabeth/CLionProjects/Learning_C11/transitions.txt", "r");
    int i = 0;
    int prevState;
    char semicolon;
    char input;
    char greaterThan;
    int nextState;

    if (infile == NULL) {
        printf("FileOpeningError: unable to open file with the machine definition.\n");
        return 0;
    }

    // the "line" variable is the indicator of if the operation finished successfully,
    // one of the reasons for this operation to fail is if the %d didn't return the number, but a letter instead
    int line = fscanf(infile, "%d%c%c%c%d\n", &prevState, &semicolon, &input,
                       &greaterThan, &nextState);

    while ((line!=0) && (line != EOF) && i < TRANSITIONSARRAYSIZEMAX) {
        if (!checkFormat(semicolon, greaterThan)){
            return 0;
        }
        // here we already know that the format, the inputs and states are valid
        array[i][0] = prevState;
        array[i][1] = (int) input;
        array[i][2] = nextState;
        line = fscanf(infile, "%d%c%c%c%d\n", &prevState, &semicolon, &input,
                       &greaterThan, &nextState);
        i++;
    }
    if (!line){
        return 0;
    }

    // return the number of lines we read in the file, which is also the true amount of slots that are filled in the array
    return i;
}

// this function is checking if the line from the transitions file is valid
// i.e. follows the format: “state:input>next state”
// here we know that the state and the next state are both integers so we don't need to check for that
int checkFormat(char semicolon, char greaterThan) {
    if (semicolon == ':' && greaterThan == '>') {
        return 1;
    }
    printf("IncorrectFormatError: the line doesn't match 'state:input>next state' format.\n");
    return 0;

}

void printTransitionsArray(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength){
    int loop;
    for (loop = 0; loop < arrayLength; loop++) {
        printf("%d,", arrayTransitions[loop][0]);
        printf("%c,", arrayTransitions[loop][1]);
        printf("%d\n", arrayTransitions[loop][2]);

    }
}

int moveInTheMachine(int arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLength) {
    char input;
    char prevState = 0; // in the beginning we are always starting from the state 0
    FILE *infile;
    infile = fopen("/Users/elizabeth/CLionProjects/Learning_C11/inputs.txt", "r");
    int i = 0;
    int inputFound = 0;

    if (infile == NULL) {
        printf("FileOpeningError: unable to open file with the inputs.\n");
        return 0;
    }
    while ((fscanf(infile, "%c\n", &input) != EOF) && (i < INPUTSMAX)) {
        for (int i = 0; i < arrayLength; i++) // this is the loop that checks the what the the transition going to be
        {

            if (arrayTransitions[i][0] == prevState && ((char) arrayTransitions[i][1]) == input) {
                prevState = arrayTransitions[i][2];
                printf("%d\n", prevState);
                inputFound = 1;
                break;
            }
        }
        i++;
        if (!inputFound) {
            printf("InvalidInputError: the input does not match to available inputs in machine definition.\n");
            return 0;
        }
        inputFound = 0;
    }
}

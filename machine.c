#include <stdio.h>

#define TRANSITIONSARRAYSIZEMAX 16 // the max number of transitions in the machine definitions
#define BOXSIZE 3  // one box of the array where there are the prev state, input, new state (size 3)
#define TRANSITIONSLINESIZE 5 // in the file with transitions how big is one line
int validateInput (char input);
int readTransitions(char array[TRANSITIONSARRAYSIZEMAX][BOXSIZE]);
int checkFormat(char line[TRANSITIONSLINESIZE]);
int validateState(char state);

int
main ()
{
    char input; // delete, dummy variable
    char prevState = '0';
    char array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];

    // this will be outputted for any error that occurred while reading transitions file
    // some errors (for example the file not opening) will have additional errors printed before that
    if (!readTransitions(array)){
        printf("Error occurred while attempting to read the machine definition.\n");
        return 0;
    }
    char arrayTransitions[TRANSITIONSARRAYSIZEMAX][BOXSIZE] =
            { {'a', '0', '1'}, {'a', '1', '0'}, {'a', '2', '0'}, {'a', '3', '0'},
              {'b', '0', '1'}, {'b', '1', '2'}, {'b', '2', '1'}, {'b', '3', '1'}
            };

    printf ("Input a state: ");
    scanf ("%c", &input);

    if (!validateInput (input))
        return 0;			// after this point the input state is valid or the program is terminated


    for (int i = 0; i < TRANSITIONSARRAYSIZEMAX; i++) // this is the loop that checks the what the the transition going to be
    {

        if (arrayTransitions[i][0] == input && arrayTransitions[i][1] == prevState)
        {
            prevState = arrayTransitions[i][2];
            printf ("%c", prevState);
            break;
        }
    }
    return 1;
}

// check if the input is one of the available ones
int
validateInput (char input)
{
    if (input != 'a' && input != 'b' && input != 'c' && input != 'd')	// check if the state is one of the 4 valid ones
    {
        printf ("IncorrectInputError: the input is not valid.");	// if not print the error message
        return 0;
    }
    return 1;
}

// this function is the one responsible for the transitions file
// that is having the machine definition
// it is responsible for getting the insides of the file into the array (returns 1)
// if the error occurred at some point -> return 0
int readTransitions(char array[TRANSITIONSARRAYSIZEMAX][BOXSIZE]){
    FILE *infile;
    infile = fopen("/Users/elizabeth/CLionProjects/Learning_C11/transitions.txt", "r");
    int i = 0;
    char line[TRANSITIONSLINESIZE];

    if (infile==NULL){
        printf("Error with opening the file.\n");
        return 0;
    }
    while ((fscanf(infile, "%s\n", &line) != EOF) && i < TRANSITIONSARRAYSIZEMAX){
        printf("%s\n", line);
        i++;
        checkFormat(line);
    }

}

// this function is checking if the line from the transitions file is valid
// i.e. follows the format: “state:input>next state”
// here we know that the line is TRANSITIONSLINESIZE (5) characters, and not exceeding that
int checkFormat(char line[TRANSITIONSLINESIZE]){
    printf("the line: %d\n", line[0]);
    printf("validation: %d\n", validateState(line[0]));

}


int validateState(char state){
    if (state==48 || state==49 || state==50 || state==51){
        return 1;
    }
    return 0;
}

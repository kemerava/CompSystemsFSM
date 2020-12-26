#include "tests.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#define TRANSITIONSARRAYSIZEMAX 50 // the max number of transitions in the machine definitions
#define BOXSIZE 3  // one box of the array where there are the prev state, input, new state (size 3)
#define INPUTSMAX 250 // the maximum number of inputs that are in the input file
int test_file_names();
void test_machine_definition();
void test_debugger();
int test_empty_definition_file();
int test_empty_inputs_file();
int test_invalid_transition();
int test_valid_transitions();
int test_more_than_50_transitions();
int test_valid_inputs();
int test_invalid_input();
int test_invalid_edge();
int test_valid_input();
int test_more_than_250_inputs();
int test_invalid_number_args();
int test_invalid_debug_arg();
int test_not_letter_input();
int test_valid_args();
int test_letter_input();
int test_add_unique_edge();
int test_add_same_edge_diff_next_state();
int test_add_same_edge_same_next_state();



int compare_arrays(int array1[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLen1, int array2[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLen2);

int tests(){
    /*
     *  tests:
        createMachine();
            1. check for the invalid input file
        moveInTheMachine();
            2. check for the invalid input file
        machineDefinition(); // this function does not return anything, so the only way is to check the output by looking
            3. create the array and see if it prints out the right thing
        debugger(); // check for the debug options // manual check (manually input 3 types of inputs)
            4. enter invalid option
            5. enter 'p' option
            6. enter 'n' option
        populateMachineArray(); // check for the array
            7. input empty file
            8. input file with one invalid transition
            9. enter valid and check that the return array is the right one
            10. enter a file with definition with more than 50 lines (valid transitions)
        mapInputs(); // check for the inputs
            11. input empty file
            12. input the valid file and check that the number of iterations is right (+ look at output)
            13. enter the file with more than the allowed 250 lines (valid inputs)
        lookForEdge(); // check for the the edges if found
            14. input the valid array, but the invalid input (not a letter)
            15. input the valid array, but the non-existent edge (state - input pair)
            16. enter the valid array, valid input and to the edge that exists (check state and return value)
        parseArgs(); // try different arguments
            17. input invalid number of arguments
            18. input invalid debug argument
            19. input valid and check what are the values of the parameters
        validateInput();
            20. input the invalid input
            21. input a valid input
        addEdgeIfUnique():
            22. add unique edge
            23. add same edge with different next state
            24. add same edge with same next state
     */

    int count = 0;
    // tests 1 and 2
    count += test_file_names();

    // test 3
    //test_machine_definition(); // ! Uncomment this line to run the tests that need inspection !

    // test 4, 5, 6
    //test_debugger(); // ! Uncomment this line to run the tests that need inspection !

    // test 7
    count+= test_empty_definition_file();

    // test 8
    count+= test_invalid_transition();

    // test 9
    count += test_valid_transitions();

    // test 10
    count += test_more_than_50_transitions();

    // test 11
    count += test_empty_inputs_file();

    // test 12
    count+= test_valid_inputs();

    //  test 13
    count += test_more_than_250_inputs();

    // test 14
    count+= test_invalid_input();

    // test 15
    count+= test_invalid_edge();

    // test 16
    count += test_valid_input();

    // test 17
    count += test_invalid_number_args();

    // test 18
    count += test_invalid_debug_arg();

    // test 19
    count += test_valid_args();

    // test 20
    count += test_not_letter_input();

    // test 21
    count += test_letter_input();

    // test 22
    count += test_add_unique_edge();

    // test 23
    count += test_add_same_edge_diff_next_state();

    // test 24
    count += test_add_same_edge_same_next_state();

    printf("----------------------------------------------\n");
    printf("Tests finished. %d tests succeeded out of 20\n", count);
    printf("----------------------------------------------\n");

    return count;

}

int test_file_names(){
    int count = 0;
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];
    int arrayLength = TRANSITIONSARRAYSIZEMAX;
    char fileName[] = "invalid_name";
    if (!createMachine(array, fileName)){
        count++;
    }
    else{
        printf("Test for invalid filename for readTransitions() failed!\n");
    }
    if (!moveInTheMachine(array, arrayLength, fileName, 0)){
        count++;
    }
    else{
        printf("Test for invalid filename for readTransitions() failed!\n");
    }
    return count;
}

void test_machine_definition(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {
            {1, 44, 0}, {0, 50, 1}, {12, 66, 1}, {4, 71, 4}
    };
    int arrayLength = 4;
    machineDefinition(array, arrayLength);
}

void test_debugger() {
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {
            {1, 44, 0}, {0, 50, 1}, {12, 66, 1}, {4, 71, 4}
    };
    int arrayLength = 4;
    debugger(array, arrayLength);
}

int test_empty_definition_file(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];
    char fileName[] = "./transitions_empty.txt";
    FILE *infile;
    infile = fopen(fileName, "r");
    if (populateMachineArray(infile, array)){
        printf("Test for empty file for populateMachineArray() failed!\n");
        return 0;
    }
    else
        return 1;
}


int test_empty_inputs_file(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];
    char fileName[] = "./inputs_empty.txt";
    FILE *infile;
    infile = fopen(fileName, "r");
    int arrayLength = TRANSITIONSARRAYSIZEMAX;
    if (mapInputs(infile, 0, array, arrayLength)){
        printf("Test for empty file for mapInputs() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_invalid_transition(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];
    char fileName[] = "./invalid_inputs.txt";
    FILE *infile;
    infile = fopen(fileName, "r");
    if (populateMachineArray(infile, array)){
        printf("Test for invalid transition for populateMachineArray() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_valid_transitions(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];
    char fileName[] = "./transitions.txt";
    FILE *infile;
    infile = fopen(fileName, "r");
    int array_needed[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                          {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                          {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                          {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};

    int arrayLen = populateMachineArray(infile, array);
    if (!compare_arrays(array, arrayLen, array_needed, 16)){
        printf("Test for valid transition for populateMachineArray() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_more_than_50_transitions(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE];
    char fileName[] = "./transitions_over_50.txt";
    FILE *infile;
    infile = fopen(fileName, "r");

    if (populateMachineArray(infile, array) != TRANSITIONSARRAYSIZEMAX){
        printf("Test for valid transition for populateMachineArray() failed!\n");
        return 0;
    }
    else
        return 1;
}


int test_valid_inputs(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
        {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
        {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
        {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    char fileName[] = "./inputs.txt";
    FILE *infile;
    infile = fopen(fileName, "r");
    int arrayLength = 16;
    if (mapInputs(infile, 0, array, arrayLength)!= 8){
        printf("Test for valid inputs for mapInputs() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_more_than_250_inputs(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    char fileName[] = "./inputs_over_250.txt";
    FILE *infile;
    infile = fopen(fileName, "r");
    int arrayLength = 16;
    if (mapInputs(infile, 0, array, arrayLength)!= INPUTSMAX){
        printf("Test for more than 250 inputs for mapInputs() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_invalid_input(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    int arrayLength = 16;
    int state = 0;
    int *statePT = &state;
    if (lookForEdge(array, arrayLength, statePT, ']', 0)){
        printf("Test for invalid inputs for lookForEdge() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_invalid_edge(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, };
    int arrayLength = 15;
    int state = 3;
    int *statePT = &state;
    if (lookForEdge(array, arrayLength, statePT, 'd', 0)){
        printf("Test for invalid inputs for lookForEdge() failed!\n");
        return 0;
    }
    else
        return 1;
}

int test_valid_input(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    int arrayLength = 16;
    int state = 0;
    int *statePT = &state;
    if (lookForEdge(array, arrayLength, statePT, 'c', 0) && state == 2){
        return 1;
    }
    else{
        printf("Test for valid inputs for lookForEdge() failed!\n");
        return 0;
    }
}

int test_invalid_number_args(){
    int argc = 1;
    char *argv[] = {"./main"};
    char *transitionsFileName;
    char *inputFileName;
    int debug = 0;
    int *debugPointer = &debug;
    if (parseArgs(argc, argv, &transitionsFileName, &inputFileName, debugPointer)){
        printf("Test for invalid number of arguments for parseArgs() failed!\n");
        return 0;
    }
    else
        return 1;

}
int test_invalid_debug_arg(){
    int argc = 4;
    char *argv[] = {"./main", "-f", "./file1", "./file2"};
    char *transitionsFileName;
    char *inputFileName;
    int debug = 0;
    int *debugPointer = &debug;
    if (parseArgs(argc, argv, &transitionsFileName, &inputFileName, debugPointer)){
        printf("Test for debug argument for parseArgs() failed!\n");
        return 0;
    }
    else
        return 1;

}

int test_valid_args(){
    int argc = 4;
    char *transitionsFileName_proper = "./file1";
    char *inputFileName_proper = "./file2";
    char *argv[] = {"./main", "-d", transitionsFileName_proper, inputFileName_proper};
    char *transitionsFileName;
    char *inputFileName;
    int debug = 0;
    int *debugPointer = &debug;
    if (parseArgs(argc, argv, &transitionsFileName, &inputFileName, debugPointer) &&
            !strcmp(transitionsFileName_proper, transitionsFileName) &&
            !strcmp(inputFileName_proper, inputFileName) &&
            debug == 1){
        return 1;
    }
    else {
        printf("Test for valid arguments for parseArgs() failed!\n");
        return 0;
    }

}
int test_not_letter_input() {
    if (validateInput('!')){
        printf("Test for invalid input for validateInput() failed!\n");
        return 0;
    }
    else
        return 1;

}

int test_letter_input() {
    if (!validateInput('a')){
        printf("Test for invalid input for validateInput() failed!\n");
        return 0;
    }
    else
        return 1;

}

int test_add_unique_edge(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    int prevState = 4;
    char input = 'n';
    int nextState = 5;
    int i = 16;
    int expected = i + 1;
    if (addEdgeIfUnique(array, prevState, input, nextState, i) != expected){
        printf("Test for adding unique edge for addEdgeIfUnique() failed!\n");
        return 0;
    }
    return 1;
}

int test_add_same_edge_diff_next_state(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    int prevState = 2;
    char input = 'a';
    int nextState = 1;
    int i = 16;
    if (addEdgeIfUnique(array, prevState, input, nextState, i)){
        printf("Test for adding same edge with different next state for addEdgeIfUnique() failed!\n");
        return 0;
    }
    return 1;
}

int test_add_same_edge_same_next_state(){
    int array[TRANSITIONSARRAYSIZEMAX][BOXSIZE] = {{0, 'a', 1}, {0, 'b', 1}, {0,'c',2},
                                                   {0,'d',3}, {1,'a',0}, {1,'b',2}, {1,'c',2},
                                                   {1,'d',3}, {2,'a',0}, {2,'b',1}, {2,'c',2},
                                                   {2,'d',3}, {3,'a',0}, {3,'b',1}, {3,'c',0}, {3,'d',0}};
    int prevState = 2;
    char input = 'a';
    int nextState = 0;
    int i = 16;
    if (addEdgeIfUnique(array, prevState, input, nextState, i)!=i){
        printf("Test for adding same edge with different next state for addEdgeIfUnique() failed!\n");
        return 0;
    }
    return 1;
}


// util function that is comparing elements of the array
int compare_arrays(int array1[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLen1, int array2[TRANSITIONSARRAYSIZEMAX][BOXSIZE], int arrayLen2){
    if (arrayLen1 != arrayLen2){
        return 0;
    }
    for (int i=0; i<arrayLen1; i++){
        for (int j=0; j<BOXSIZE; j++){
            if (array1[i][j]!=array2[i][j])
                return 0;
        }
    }
    return 1;
}

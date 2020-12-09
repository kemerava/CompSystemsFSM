#include <stdio.h>
#include <stdlib.h>

#define TRANSITIONSARRAYSIZE 16
#define BOXSIZE 3
int validateInput (char input);

int
main ()
{
  char input;
  char prevState = '0';

  int arrayTransitions[TRANSITIONSARRAYSIZE][BOXSIZE] =
    { {'a', '0', '1'}, {'a', '1', '0'}, {'a', '2', '0'}, {'a', '3', '0'},
  {'b', '0', '1'}, {'b', '1', '2'}, {'b', '2', '1'}, {'b', '3', '1'}
  };

  printf ("Input a state: ");
  scanf ("%c", &input);

  if (!validateInput (input))
    return;			// after this point the input state is valid or the program is terminated 


  for (int i = 0; i < TRANSITIONSARRAYSIZE; i++) // this is the loop that checks the what the the transition going to be
    {

      if (arrayTransitions[i][0] == input && arrayTransitions[i][1] == prevState)
	{
	  prevState = arrayTransitions[i][2];
	  printf ("%c", prevState);
	  break;
	}
    }

}

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

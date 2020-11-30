
#include <stdio.h>
int a[] = {1, 0, 0, 0};
int b[] = {1, 2, 1, 1};
int c[] = {2, 2, 2, 0};
int d[] = {3, 3, 3, 0};

char arr[] = {'a', 'b', 'a', 'c', 'd'};

int main()
{
    int prev_state = 0;
    int *prev = &prev_state;
    int i;
    int *ptr[4];
    
    for (i=0; i < sizeof arr; i++){
        char input = arr[i]; 
          switch(input) {
                case 'a' :
                    *ptr = &a;
                    break;
                case 'b' :
                    *ptr = &b;
                    break;
                case 'c' :
                    *ptr = &c;
                    break;
                case 'd' :
                    *ptr = &d;
                    break;
          }
        int state = *ptr[prev_state];
        
        printf("%d", prev_state);
        
    }
}

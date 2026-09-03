#include <stdio.h>

int main()
{
    int number, t;
    do{
        scanf(" %d" , &number);
        if(number < 0)
        continue;
        for(t = 1 ; t <= number ; t = t + 1)
        {
            printf("%d\n" , number);
        }
    }while( number != 0);
    return 0;
}
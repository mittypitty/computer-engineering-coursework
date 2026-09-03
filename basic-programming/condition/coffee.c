#include <stdio.h>

int main()
{
    int coffee_percent, suger_percent;
    scanf("%d" , &coffee_percent);
    scanf("%d" , &suger_percent);
    if(coffee_percent < 50)
    {
        if(suger_percent > 50)
        printf("a");
    }
    if(coffee_percent < 50)
    {
        if(suger_percent < 50)
        printf("c");
    }
    if(coffee_percent > 50)
    {
        if(suger_percent < 50)
        printf("b");
    }
    if(coffee_percent >= 50)
    {
        if(suger_percent >= 50)
        {
        printf("d");
        }
    }
    return 0;
}
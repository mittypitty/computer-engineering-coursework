#include <stdio.h>

int main()

{
    int number1, number2, number3, number4, number5; 
    scanf("%d" , &number1);
    scanf("%d" , &number2);
    number3 = number1 + number2;
    number4 = number3 % 2;
    number5 = (number4 * 100) + 100;
    printf("%d" , number5);
    return 0;
}
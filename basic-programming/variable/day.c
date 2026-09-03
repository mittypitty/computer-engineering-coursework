#include <stdio.h>

int main()
{
    int day1, month1, week1, day2, month2, week2;
    scanf("%d/%d:%d" , &day1, &month1, &week1);
    scanf("%d/%d" , &day2, &month2);
    week2 = (week1 + ((month2 - 1) * 30 + day2) - ((month1 - 1) * 30 + day1))%7;
    printf("%d" , week2);
    return 0;
}
#include <stdio.h>

int main()
{
    int a, b, c, d, sum, miangin;
    scanf("%d %d %d %d" , &a , &b , &c , &d);
    sum = (96 * 4) + a + b + c + d;
    miangin = sum / 4;
    printf("%c%c%c%c%d%c" , a+96 , b+96 , c+96 , d+96 , sum , miangin);
    return 0;
}
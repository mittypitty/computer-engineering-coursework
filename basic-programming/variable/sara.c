#include <stdio.h>

int main()
{
    double a1, a2, a3, a4, b1, b2, b3, b4, sum;
    scanf("%lf" , &a1);
    scanf("%lf" , &a2);
    scanf("%lf" , &a3);
    scanf("%lf" , &a4);
    scanf("%lf" , &b1);
    scanf("%lf" , &b2);
    scanf("%lf" , &b3);
    scanf("%lf" , &b4);
    sum = a1 * b1 + a2 * b3 + a1 * b2 + a2 * b4 +a3 * b1 + a4 * b3 + a3 * b2 + a4 * b4;
    printf("%.2lf" , sum);
    return 0;
}
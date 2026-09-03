#include <stdio.h>

int main()
{
    long long unsigned int number, number2, n, m, count3, count2, count1, zerow1, zerow2, zerow3, sum1, sum2, sum3;
  int sum;
     count1 = 0;
     zerow1 = 0;
     count2 = 0;
     zerow2 = 0;
     count3 = 0;
     zerow3 = 0;
     sum = 0;
     sum1 = 0;
     sum2 = 0;
     sum3 = 0;


     


    scanf("%lld" , &number);
    for(n = 1 , m = 10 ; n <= number ; n = n * 10 , m = m * 10 )
{

    number2 = (number % m );
    number2 = number2 / n;
     if(number2 == 3)
     { 
        count3 = count3 + 1;
     }
     if(number2 == 2)
     {
        count2 = count2 + 1;
     }
     if(number2 == 1)
     {
        count1 = count1 + 1;
     }
     if(number2 == 0)
     {
       if(count3 != 0)
       zerow3 = zerow3 + 1;
       if(count2 != 0)
       zerow2 = zerow2 + 1;
       if(count1 != 0)
       zerow1 = zerow1 + 1;
     }
     while(count3 == 2)
     {
       sum3 = (zerow3 * 3) + sum3;
       count3 = count3 - 1;
       zerow3 = 0;
     }
     while(count2 == 2)
     {
       sum2 = (zerow2 * 2) + sum2;
       count2 = count2 - 1;
       zerow2 = 0;
     }
    while(count1 == 2)
    {
       sum1 = zerow1 + sum1;
       count1 = count1 - 1;
       zerow1 = 0;
     }
}

     sum = sum1 + sum2 + sum3;
     printf("%d" , sum);
     return 0;

}
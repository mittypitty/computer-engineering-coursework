#include <stdio.h>

int main()
{
     long long int  countnum, countcode, i, n, j, c, w;
     long long int bignumber;
     long long int realcode, bnumb2, second, first;
     long long int sara, main;
    scanf(" %lli", &countnum);
    scanf(" %lli", &countcode);
    i = 1;
    j = 1;
    w = 0;
    realcode = 0;
    bignumber = 0;
    main = 1;
    first = 0;
    second = 0;
    sara = 1;

    for(sara=1; sara<=countcode ;sara ++)
    {
        main = main * 10;
    }
    while(i <= countnum)
    {
        scanf("%lli" , &n);
        bignumber = (bignumber * 10) + n;
        i = i + 1;
        
    }
    i = 1;
    while(i <= countcode)
    {
        scanf("%lli" , &c);
        realcode = realcode + c * j;
        i = i + 1;
        j = j * 10;
    }

    while(bignumber >= 1)
{
         bnumb2 = bignumber % main;
         
        w = w + 1;
       if(bnumb2 == realcode)
        {
            second = countnum - w + 1;
        first  = second - countcode + 1;
        printf("%lli, %lli" , first, second);
        break;
        }
        else 
        bignumber = bignumber / 10;
        
    }  
    return 0;
}
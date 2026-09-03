#include <stdio.h>

int main()
{
    int i, t, d;
    scanf("%d" , &i );

    for ( t = 1 ; t <= (i - 1) ; t = t + 1)
    {
        printf("# ");
    }
    printf("# \n");
    t = 1;
    while ( t <= (i - 2))
    {
        printf("# ");
        for ( d = 1 ; d <= (i - 2) ; d = d + 1)
        {
            printf("@ ");
        }
        t = t + 1;
        printf("# \n");
    }

    for ( t=1 ; t <= i ; t = t + 1)
    {
        printf("# ");
    }
    return 0;
}
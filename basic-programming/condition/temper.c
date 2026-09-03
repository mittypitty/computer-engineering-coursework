#include <stdio.h>

int main()
{
    double x1, x2, x3, x4, x5, y1, y2, y3, y4, y5,xmax, xmin, ymax, ymin, temper1, temper2;
    scanf(" %lf %lf\n" , &x1, &y1);
    scanf(" %lf %lf\n" , &x2, &y2);
    scanf(" %lf %lf\n" , &x3, &y3);
    scanf(" %lf %lf\n" , &x4, &y4);
    scanf(" %lf %lf\n" , &x5, &y5);
    scanf("%lf" , &temper1);
    temper2 = temper1 - 273;
    if( x1 == x2 )
    {
        if( x4 > x1 )
        {
        xmax = x4;
        xmin = x1;
        }
        else
        {
        xmax = x1;
        xmin = x4;
        }
    }
    if( y1 == y4 )
    {
        if( y2 > y1)
        {
        ymax = y2;
        ymin = y1;
        }
        else
        {
        ymax = y1;
        ymin = y2;
        }
    }
    
    printf("%.0lf\n" , temper2);
    
    if( ( xmin <= x5 ) && ( x5 <= xmax ) && ( ymin <= y5 ) && ( y5 <= ymax ) )
{
    printf("Indoor");
}
    else
{
    printf("Outdoor");
}
    return 0;
}
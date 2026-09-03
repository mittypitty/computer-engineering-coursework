#include <stdio.h>

int main()
{
    double boudjeh;
    double pool_l1, pool_l2, pool_l3, pool_s1, pool_s2;
    char lebas1, lebas2, lebas3, shalvar1, shalvar2;
     scanf (" %lf\n" , &boudjeh);
     scanf (" %c %c %c\n" , &lebas1, &lebas2, &lebas3);
     scanf (" %lf %lf %lf\n" , &pool_l1, &pool_l2, &pool_l3 );
     scanf (" %c %c\n" , &shalvar1, &shalvar2);
     scanf (" %lf %lf" , &pool_s1, &pool_s2);
   

    if (lebas1 == 'r' && pool_l1 <= boudjeh/2)
         {
            boudjeh = boudjeh - pool_l1 ;
         }
    else if (lebas1 == 'y' && pool_l1 <= boudjeh/4)
         {
            boudjeh = boudjeh - pool_l1 ;
         }
    else if (lebas1 == 'g' && pool_l1 <= boudjeh/5)
         {
            boudjeh = boudjeh - pool_l1 ;
         }
    if (lebas2 == 'r' && pool_l2 <= boudjeh/2)
         {
            boudjeh = boudjeh - pool_l2 ;
         }
    else if (lebas2 == 'y' && pool_l2 <= boudjeh/4)
         {
            boudjeh = boudjeh - pool_l2 ;
         }
    else if (lebas2 == 'g' && pool_l2 <= boudjeh/5)
         {
            boudjeh = boudjeh - pool_l2 ;
         }
    if (lebas3 == 'r' && pool_l3 <= boudjeh/2)
         {
            boudjeh = boudjeh - pool_l3 ;
         }
    else if (lebas3 == 'y' && pool_l3 <= boudjeh/4)
         {
            boudjeh = boudjeh - pool_l3 ;
         }
    else if (lebas3 == 'g' && pool_l3 <= boudjeh/5)
         {
            boudjeh = boudjeh - pool_l3 ;
         }

    if (shalvar1 == 'b' && pool_s1 <= (3 * boudjeh)/4)
         {
            boudjeh = boudjeh - pool_s1 ;
         }
    else if (shalvar1 == 'p' && pool_s1 <= (4 * boudjeh)/5)
         {
            boudjeh = boudjeh - pool_s1 ;
         }
    if (shalvar2 == 'b' && pool_s2 <= (3 * boudjeh)/4)
         {
            boudjeh = boudjeh - pool_s2 ;
         }
    else if (shalvar2 == 'p' && pool_s2 <= (4 * boudjeh)/5)
         {
            boudjeh = boudjeh - pool_s2 ;
         }
    printf("%.2lf", boudjeh);
    return 0;
}

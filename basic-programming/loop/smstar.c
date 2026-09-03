#include <stdio.h> 
 
int main() 
{ 
int number; 
int x, i, z, y; 
 
scanf("%d" , &number); 
if( number % 2 == 0)  
{ 
for(x = 1 ; x <= number/2 ; x = x + 1) 
{ 
  for(i = 1 ; i <= x ; i = i + 1) 
    { 
     printf("*"); 
    }  
    y = number - ( x * 2 ); 
    for(i = 1 ; i <= y ; i = i + 1) 
    { 
       printf(" "); 
    } 
    for(i = 1 ; i <= x ; i = i + 1) 
    { 
      printf("*"); 
    } 
    printf("\n"); 
}  
for(y = number / 2 ; y >= 1 ; y = y - 1) 
{ 
   for(i = 1 ; i <= y ; i = i + 1) 
   { 
    printf("*"); 
   } 
   z = number - (2 * y);  
   for(i = 1 ; i <= z ; i = i + 1) 
   { 
    printf(" "); 
   } 
   for(i = 1 ; i <= y ; i = i + 1) 
   { 
    printf("*"); 
   } 
   printf("\n"); 
} 
} 
if( number % 2 == 1) 
{ 
  for(x = 1 ; x <= number / 2 ; x = x + 1) 
  { 
    for(i = 1 ; i <= x ; i = i + 1) 
    { 
      printf("*"); 
    } 
    z = number - (2 * x); 
    for(i = 1 ; i <=  z ; i = i + 1) 
    { 
      printf(" "); 
    } 
    for(i = 1 ; i <= x ; i = i + 1) 
    { 
      printf("*"); 
    } 
    printf("\n"); 
  } 
  for (i=1 ; i <= number ; i++)
  {
    printf("*");
  }
  printf("\n");
  
  for(y= number / 2 ; y >= 1 ; y = y - 1) 
  { 
   for(x = 1 ; x <= y ; x = x + 1) 
   { 
    printf("*"); 
   } 
   z = number - (2 * y); 
   for(x = 1 ; x <= z ; x = x + 1) 
   { 
    printf(" "); 
   } 
   for(x = 1 ; x <= y ; x = x + 1) 
   { 
    printf("*"); 
   } 
   printf("\n"); 
  } 
 
} 
return 0; 
}
#include <stdio.h>

int
main ()
{
  int number;
  int n1, n2, n3;


  scanf ("%d", &number);


  n1 = number % 10;
  n2 = (number / 10) % 10;
  n3 = number / 100;


  if (n1 == 0)

    {


      if (n1 == n2)
 {
   printf ("1");
 }

      else if (n2 == n3)
 {
   printf ("2");
 }

      else
 {
   printf ("4");
 }


    }


  if (n2 == 0 && n1 != 0)
    {
      if (n1 == n3)
 printf ("2");
      else
 printf ("4");
    }

  if (n2 == n3 && n1 != 0 && n1 != n2 && n1 != n3)
    printf ("3");
  if ((n1 == n2) && (n2 == n3) && (n1 == n3))
    printf ("1");

  if (n2 == n1 && n3 != 0 && n3 != n2 && n1 != n3 && n1 != 0)
    printf ("3");

  if (n1 == n3 && n2 != 0 && n1 != n2 && n2 != n3)
    printf ("3");


  else if ((n1 != 0) && (n2 != 0) && (n1 != n2) && (n3 != n2) && (n1 != n3))
    printf ("6");
  return 0;
}
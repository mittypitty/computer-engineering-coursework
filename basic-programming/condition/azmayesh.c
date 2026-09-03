#include <stdio.h>

int main ()
{
  int a, b, c;
  float e, f, g;
  char d;
  char test_a, test_b, test_c, test_d;
  float h, i;
  scanf (" %d %d %d\n", &a, &b, &c);
  scanf (" %c\n", &d);
  scanf (" %f %f %f\n", &e, &f, &g);
  scanf (" %f %f", &h, &i);
  test_d = 'n';
  
  if ((a - b) >= c)
    {
      test_a = 'p';
    }
  else
    {
      test_a = 'n';
    }

  if (d == 'T')
    {
      test_b = 'p';
    }
  else if (d == 'F')
    {
      test_b = 'n';
    }



  if (((e * f) / g) < 1000)
    {
      test_c = 'p';
    }
  else
    {
      test_c = 'n';
    }
  if( h >= i)
    {
      if((h - i) < 0.000001)
      {
      test_d = 'p';
      }
    }
  else if( h < i)
    {
      if((i - h) < 0.000001 )
      {
        test_d = 'p';
      }
    }
  if ((test_a == 'n') && (test_b == 'n') && (test_c == 'n') && (test_d == 'n'))
    {
      printf ("----------\n");
      printf ("Test A's result is: Negative\n");
      printf ("----------\n");
      printf ("Test B's result is: Negative\n");
      printf ("----------\n");
      printf ("Test C's result is: Negative\n");
      printf ("----------\n");
      printf ("Test D's result is: Negative\n");
      printf ("----------");
    }
  else if ((test_a == 'p') && (test_b == 'p') && (test_c == 'p') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'p') && (test_c == 'p') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'p') && (test_c == 'n') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'n') && (test_c == 'p') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'p') && (test_c == 'p') && (test_d = 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'p') && (test_c == 'n') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'n') && (test_c == 'p') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'p') && (test_c == 'p') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'n') && (test_c == 'n') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'p') && (test_c == 'n') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'n') && (test_c == 'p') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'p') && (test_b == 'n') && (test_c == 'n') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'p') && (test_c == 'n') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'n') && (test_c == 'p') && (test_d == 'n'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Positive\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Negative\n");
      printf ("++++++++++");
    }
  else if ((test_a == 'n') && (test_b == 'n') && (test_c == 'n') && (test_d == 'p'))
    {
      printf ("++++++++++\n");
      printf ("Test A's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test B's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test C's result is: Negative\n");
      printf ("++++++++++\n");
      printf ("Test D's result is: Positive\n");
      printf ("++++++++++");
    }
  return 0;
}

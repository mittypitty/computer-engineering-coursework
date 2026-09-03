#include <iostream>
using namespace std;
#include <cstdbool>
int i, m , sum , x;
bool AdadAval(int x)
{
for(i = 2 ; i <= x / 2 ; i = i + 1)
{
  m = x % i;
  if (m == 0)
    return false;
}
  if(x != 1)
     return true;
  else
    return false;
}
void FoqhAval(int x)
{
  while(x > 0)
  {
  if(AdadAval(x) == true)
   {
     x = x / 10;
   }
   else
   break;
   if(x == 0)
   {
    sum = sum + 1;
   }
  }
}
int main()
{
  sum = 0;
  cin >> x;
  while(x > 0)
  {
  FoqhAval(x);
  x = x - 1;
  }
  cout << sum;
  return 0;
}
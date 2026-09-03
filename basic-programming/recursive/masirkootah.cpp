#include <iostream>
using namespace std;

int Masir(int x, int y)
{
   if(x == 0 || y == 0)
   return 1;
   return Masir(x , y - 1) + Masir(x - 1 , y);
}
int main()
{
  int x, y;
 
  cin >> x >> y;

  int sum;

    sum = Masir(x , y);

  cout << sum;
    
    return 0;
}
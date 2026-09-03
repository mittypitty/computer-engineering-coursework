#include <iostream>
using namespace std;
#include <cstdbool>



  bool AdadAval(long long int number)
{
    long long int j;
    long long int num3;
    num3 = number % 10000000;
    num3 = num3 / 1000;
    if (num3 <= 1)
        return false;
    
    for (int j = 2 ; j <= num3 / 2 ; j = j + 1)
        if (num3 % j == 0)
            return false;
 
    return true;
}
 
int ShomareRond(long long int number)
{
long long int num1, num2, num3;
long long int remain = 0;
long long int reversenumber;
int digit, counting2 = 0;

for(num1 = number ; num1 > 0 ; num1 = num1 / 10)
{
    remain = num1 % 10;
    reversenumber = (reversenumber * 10) + remain;
}
for(num2 = number ; num2 > 0 ; num2 = num2 / 10)
{
   digit = num2 % 10;
   if(digit == 2)
    counting2 = counting2 + 1;

}

  AdadAval(number);

if(counting2 >= 4)
    cout << "Ronde" << endl;

else if(number == reversenumber)
    cout << "Ronde" << endl;

else if(AdadAval(number) == true)
    cout << "Ronde" << endl;

else
    cout << "Not Ronde" << endl;

  return 0;
}

int main()
{
    long long int number;
    int n, i;
    cin >> n;
    for(i= 1 ; i <= n ; i = i + 1)
    {
    cin >> number;
    ShomareRond(number);
    }
    return 0;
}
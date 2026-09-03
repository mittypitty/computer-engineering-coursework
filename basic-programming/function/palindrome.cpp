#include <iostream>
using namespace std;


int palindrome(int number)
{
    long int binarynumber = 0;
    long int reversebinary = 0;
    long int y;
    long int remain, remain2;
    long int x = 1;
    long int number1;
for(number1 = number ; number1 > 0 ;)
{
    remain = number1 % 2;
    number1 = number1 / 2;
    binarynumber = binarynumber + (remain * x);
    x = x * 10;
    
}

for(y = binarynumber ; y > 0 ;)
{
    remain2 = y % 10;
    reversebinary = (reversebinary * 10) + remain2;
    y = y / 10;
}

if(reversebinary != binarynumber)
{
    cout << "invalid\n";
}
else
{
     cout << "valid\n";
    long int sum;
    long int reversenumber = 0;
    long int number2;
    number2 = number;
    long int remain3;
        while(number2 > 0)
        {
            remain3 = number2 % 10;
            reversenumber = (reversenumber * 10) + remain3;
            number2 = number2 / 10; 
        }
    sum = number + reversenumber;

    cout << sum << endl;  
   
}

 return 0;
}

int main()
{
    long int number;
    long int binarynumber;
    int m, i;
    cin >> m;
    for(i= 1 ; i <= m ; i = i + 1)
    {
    cin >> number;
    palindrome(number);
    }
    return 0;
}

#include <iostream>
using namespace std;
#include <cmath>

double Natlog(double a, int b)
{
    if(b == 0) 
    return 0;
    return pow(-1, b - 1) * ((pow(a, b)) / b) + Natlog(a, b - 1);
}

int main()
{
    double x, finalnum;
    long int n, i, num;
    
    cin >> n;
    
    for(i = 1 ; i <= n ; i = i + 1)
    {

    cin >> x;

    finalnum = Natlog(x,3500);
    num = finalnum * 100000;
    
    cout << "0." << num <<endl;

    }
    return 0;
}
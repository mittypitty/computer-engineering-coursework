#include <iostream>
using namespace std;

int HalatKashi(int n)
{
    if((n == 1) || (n == 2))
    return n;
    return HalatKashi(n-1) + HalatKashi(n-2);
}


int main()
{
    int n;
    cin >> n;
    HalatKashi(n);
    cout << HalatKashi(n);
    return 0;
}
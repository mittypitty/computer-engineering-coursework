#include <iostream>
using namespace std;

int HalatTavalod(int number)
{
    if(number == 1 || number == 2)
    return number;
    return HalatTavalod(number - 1) + HalatTavalod(number - 2) * (number - 1);
}

int main()
{
    int number;
    cin >> number;
    cout << HalatTavalod(number);
    return 0;
}
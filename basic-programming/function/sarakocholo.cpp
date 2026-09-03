#include <iostream>
using namespace std;
int DecimalToBinary(unsigned long long int x)
{
    unsigned long long int n1, n2, n3, n4;

    n1 = x % 2;
    x = x / 2;
    n2 = x % 2;
    x = x / 2;
    n3 = x % 2;
    x = x / 2;
    n4 = x % 2;

    cout << n4;
    cout << n3;
    cout << n2;
    cout << n1;
    return 0;
}

int
main()
{
    double number;

    cin >> number;


    unsigned long long int p1num, p2num;
    double secnum;
    unsigned long long int sara;
    unsigned long long int sec2num;
    unsigned long long int r, x;
    sara = 0;
    p1num = number;
    p2num = number;

    //secnum = number - p2num;
    //sara = secnum * 1000;

    sara = number * 1000;
    sec2num = sara % 1000;

    r = 1;

    while (p1num >= 1)
    {
        r = r * 10;
        p1num = p1num / 10;

    }

    r = r / 10;



    while (p2num > 0)
    {
        x = p2num / r;
        p2num = p2num % r;
        r = r / 10;

        DecimalToBinary(x);
    }


    int p = 100;
    if (sec2num > 0)
    {
        cout << ".";
        while (sec2num)
        {
            x = sec2num / p;
            sec2num = sec2num % p;
            p = p / 10;

            DecimalToBinary(x);
        }
    }

    return 0;

}

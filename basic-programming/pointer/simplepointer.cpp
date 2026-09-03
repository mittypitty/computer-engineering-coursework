#include <iostream>
using namespace std;

int main()
{
    long long int n, i, mi, j, k, helpingv, sum;
    //const long long int number = 100000;
    long long int Arr[100000];
    sum = 0;
    helpingv = 0;

    cin >> n;
    for(i = 0 ; i < n ; i = i + 1)
    {
      cin >> mi;

      for(j = helpingv ; j < (mi + helpingv) ; j = j + 1)
      {
        cin >> Arr[j];
      }

      helpingv = helpingv + mi;
    }

    cin >> k;
    
    for(i = 0 ; i < helpingv ; i = i + 1)
    {
        long long int* pointer = &Arr[i];
        if(*pointer % k == 0)
        sum = sum + 1;
    }

    cout << sum;
    return 0;
}
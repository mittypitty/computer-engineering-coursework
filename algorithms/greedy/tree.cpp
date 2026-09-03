#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    long int a;
    long int b;
    long int c;
    cin >> a >> b >> c;

    if (a == 0 && b == 0 && c == 0) {
        cout << 0;
        return 0;
    }
    
    if ((a + 1 != c) && a != 0) {
        cout << -1;
        return 0;
    }
    if (a == 0 && c != 1) {
        cout << -1;
        return 0;
    }
    

    if( a != 0) {
        long long length_a = 0;
        long long length_b = 0;
        long long temp = a;

        while (temp > 0) {
            temp >>= 1;
            length_a += 1;
        }

        long long adjust = ((1LL << length_a) - 1) - a;
        b -= adjust;
        length_b = (b + c - 1) / c;

        long long answer = length_a + length_b;
        cout << answer;
    } else {
        cout << b;
    }
    return 0;


}
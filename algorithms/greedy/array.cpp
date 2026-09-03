#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    long int n;
    cin >> n;
    bool  found = false;

    long int *a = new long int[n];
    long int *b = new long int[n];
    long int *x = new long int[n];
    long int *y = new long int[n];


    for (long int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (long int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (long int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            x[i] = a[i];
            y[i] = b[i];
        }
        else if(i % 2 == 1) {
            y[i] = a[i];
            x[i] = b[i];
        }
    }

    long int z = -1;
    for (long int i = n - 1; i > z; i--) {
        for (long int j = i; j > z; j--) {
            if(x[i] == y[j]) {
                if(z < j) {
                    z = j;
                }
            }
            if(y[i] == x[j]) {
                if(z < j) {
                    z = j;
                }
            }
        }
    }

    long int answer = z + 1;

    cout << answer;
    return 0;
}

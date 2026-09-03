#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    if (n <= 2) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        } 
        cout << sum;
        return 0;
    }

    long long* dp = new long long[n + 5];

    for (int i = 0; i < n + 5; i++) {
        dp[i] = 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        long long a = 0;
        long long b = 0;

        if (i + 2 <= n) {
            a = dp[i + 2];
        } else {
            a = 0;
        }
        if (i + 3 <= n) {
            b = dp[i + 3];
        }
        else {
            b = 0;
        }
        long long cst = arr[i] + (a < b ? a : b);

        long long best = cst;

        if (i + 1 < n) {
            long long c = 0;
            long long d = 0;
            if (i + 3 <= n) {
                c = dp[i + 3];
            } else {
                c = 0;
            }
            if (i + 4 <= n) {
                d = dp[i + 4];
            } else {
                d = 0;
            }    
            long long cst2 = arr[i] + arr[i + 1] + (c < d ? c : d);
            
            if (cst2 < best) {
                best = cst2;
            } 
        }

        dp[i] = best;
    }
    cout << dp[0];
}


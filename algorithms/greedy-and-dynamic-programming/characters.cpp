#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n+1);

    dp[0] = 1e9;
    
    for(int i = 2; i < n + 1; i++) {
        dp[i] = i;
    }
    dp[1] = 0;

    for(int i = 2; i < n + 1; i++) {
        for(int j = 1; j * j <= i; j++) {
            if((i % j) == 0) {
                //dp[i] = min(dp[i], (dp[j] + (i / j)), (dp[i / j] + (i / (i / j))));
                dp[i] = min(dp[i], (dp[j] + (i / j)));
                dp[i] = min(dp[i], (dp[i / j] + (i / (i / j))));
            }
        }
    }

    cout << dp[n];
    return 0;
}
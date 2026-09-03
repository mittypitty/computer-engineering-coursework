#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >>n;

    vector<long long> places(n);

    for(int i = 0; i < n; i++) {
        cin >> places[i];
    }

    if(n == 1) {
        cout << places[0];
        return 0;
    }

    vector<long long> dp(n);

    dp[0] = places[0];
    dp[1] = max(places[0] , places[1]);

    //int max_stealed = max(dp[i - 1], places[i] + dp[i - 2]);

    for(int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], (places[i] + dp[i - 2]));
    }

    cout << dp[n - 1];
    return 0;
}

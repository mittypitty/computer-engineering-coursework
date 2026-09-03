#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;

    // int max_bwr = 0;
    // int max_wrb = 0;
    // int max_rbw = 0;    
    vector<int> dp(3);

    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 0;
    //dp[0] for B , dp[1] for W , dp[2] for R


    for(int i = 0; i < n; i++) {
        if(s[i] == 'B') {
            dp[0] = max({dp[0] + 1, dp[2] + 1, 1});
        }
        else if(s[i] == 'W') {
            dp[1] = max({dp[0] + 1, dp[1] + 1, 1});
            
        }
        else if(s[i] == 'R') {
            dp[2] = max({dp[1] + 1, dp[2] + 1, 1});
        }
    }

    // for(int i = 0; i < n; i++) {
    //     if(s[i] == 'B') {
    //         dp[0] = dp[0] + 1;
    //     }
    //     else if(s[i] == 'W') {
    //         dp[1] = max(dp[0], dp[1]) + 1;
            
    //     }
    //     else if(s[i] == 'R') {
    //         dp[2] = max(dp[1], dp[2]) + 1;
    //     }
    // }
    // max_bwr = max({dp[0], dp[1], dp[2]});


    // dp[0] = 0;
    // dp[1] = 0;
    // dp[2] = 0;
    //dp[0] for W , dp[1] for R , dp[2] for B

    // for(int i = 0; i < n; i++) {
    //     if(s[i] == 'W') {
    //         dp[0] = dp[0] + 1;
    //     }
    //     else if(s[i] == 'R') {
    //         dp[1] = max(dp[0], dp[1]) + 1;
            
    //     }
    //     else if(s[i] == 'B') {
    //         dp[2] = max(dp[1], dp[2]) + 1;
    //     }
    // }
    // max_wrb = max({dp[0], dp[1], dp[2]});


    // dp[0] = 0;
    // dp[1] = 0;
    // dp[2] = 0;
    //dp[0] for R , dp[1] for B , dp[2] for W

    // for(int i = 0; i < n; i++) {
    //     if(s[i] == 'R') {
    //         dp[0] = dp[0] + 1;
    //     }
    //     else if(s[i] == 'B') {
    //         dp[1] = max(dp[0], dp[1]) + 1;
            
    //     }
    //     else if(s[i] == 'W') {
    //         dp[2] = max(dp[1], dp[2]) + 1;
    //     }
    // }
    // max_rbw = max({dp[0], dp[1], dp[2]});

    
    int answer = max({dp[0], dp[1], dp[2]});

    cout << answer;
    
}
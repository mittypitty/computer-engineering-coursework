#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Person {
    long long w, t;
};


bool dp_check(double x, int W, const vector<Person>& person, int n) {
    vector<double> dp(W + 1, -1e18);
    dp[0] = 0;

    for(int i = 0; i < n ; i++) {
        double value = (double)person[i].t - x * (double)person[i].w;
        long long weight = person[i].w;

        for (int v = W; v >= 0; v--) {
            if (dp[v] < -1e17) {
                continue;
            }
            int next_value = min((long long)W, v + weight);

            if (dp[v] + value > dp[next_value]) {
                dp[next_value] = dp[v] + value;
            }
        }
    }

    if (dp[W] >= 0) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    int n;
    int W;
    cin >> n >> W;

    double low = 0.0;
    double high = 1e6;
    double mid;
    vector<Person> person(n);
    for(int i = 0; i < n; i++) {
        cin >> person[i].w >> person[i].t;
    }

    double answer = 0.0;
    for(int i = 0; i < 60; i++) {
        mid = ((high - low) / 2.0) + low;

        if(dp_check(mid, W, person, n)) {
            answer = mid;
            low = mid;
        } 
        else {
            high = mid;
        }
    }

    cout << (long long)floor(answer * 1000.0 + 1e-7);;
    return 0;

}

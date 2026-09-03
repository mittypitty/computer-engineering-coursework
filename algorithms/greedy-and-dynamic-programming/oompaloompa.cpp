#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
    vector<long long> prices;
};

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<Box> boxes(m + 1);
    vector<long long> b(m + 1);

    int box_num;
    long long item_price;

    for(int i = 0; i < n; i++) {
        cin >> box_num >> item_price;
        boxes[box_num].prices.push_back(item_price);
    }

    for (int i = 1; i < m + 1; i++) {
        cin >> b[i];
    }


    vector<int> dp(p + 1, -1);
    dp[0] = 0;
    
    for (int i = 1; i <= m; i++) {
        sort(boxes[i].prices.begin(), boxes[i].prices.end());

        vector<pair<long long, int>> options;
        options.push_back({0, 0});

        long long sum = 0;
        int cnt = boxes[i].prices.size();

        for (int k = 1; k <= cnt; k++) {
            sum += boxes[i].prices[k - 1];

            long long cost = sum;

            if (k == cnt) {
                cost = min(cost, b[i]);
            }

            options.push_back({cost, k});
        }

        vector<int> next_dp = dp;

        for (int money = 0; money <= p; money++) {
            if (dp[money] == -1) continue;

            for (auto [cost, count] : options) {
                if (money + cost <= p) {
                    next_dp[money + cost] = max(
                        next_dp[money + cost],
                        dp[money] + count
                    );
                }
            }
        }

        dp = next_dp;
    }

    int answer = 0;

    for(int i = 0; i < p + 1; i++) {
        answer = max(answer, dp[i]);
    }

    cout << answer;
}
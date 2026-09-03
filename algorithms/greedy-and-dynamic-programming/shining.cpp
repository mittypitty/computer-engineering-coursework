#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> d(n, vector<long long>(n));
    vector<int> order(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    for(int i = 0; i < n; i++) {
        cin >> order[i];
    }

    for(int i = 0; i < n; i++) {
        order[i]--;
    }

    reverse(order.begin(), order.end());

    vector<bool> is_active(n, false);
    vector<long long> final_order;

    for (int k : order) {
        is_active[k] = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }

        long long current_sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (is_active[i] && is_active[j]) {
                    current_sum += d[i][j];
                }
            }
        }
        final_order.push_back(current_sum);
    }

    reverse(final_order.begin(), final_order.end());

    for(int i = 0; i < n; i++) {
        cout << final_order[i];
        if(i == n - 1) {
            cout << "";
        }
        else {
            cout << " ";
        }
    }

    cout << "\n";
    return 0;
}
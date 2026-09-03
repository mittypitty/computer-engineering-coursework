#include <iostream>
#include <vector>

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long V;
    cin >> n >> V;

    vector<long long> h(n), v(n);
    vector<int> index(n);

    for(int i = 0; i < n; i++) {
        cin >> h[i] >> v[i];
    }

    for (int i = 0; i < n; i++) {
        index[i] = i;
    }
    
    sort(index.begin(), index.end(), [&](int a, int b) {
        return h[a] * v[b] > h[b] * v[a];
    });

    double total = 0;
    long long remain = V;

    for (int i = 0; i < n && remain > 0; i++) {
        int id = index[i];
        long long take = min(remain, v[id]);

        total += (double)h[id] * take / v[id];
        remain -= take;
    }

    cout << fixed << setprecision(1) << total << endl;
}

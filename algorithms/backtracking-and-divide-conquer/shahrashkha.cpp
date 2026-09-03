#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll limitValue;
vector<ll> pref, bufferArray;

ll solveRange(int left, int right) {
    if (right - left < 2) {
        return 0;
    }

    int middle = left + (right - left) / 2;
    ll total = solveRange(left, middle) + solveRange(middle, right);
    int pointer = left;

    for (int idx = middle; idx < right; idx++) {
        while (pointer < middle && pref[pointer] <= pref[idx] - limitValue) {
            pointer++;
        }

        total += middle - pointer;
    }

    int i = left;
    int j = middle;
    int pos = left;

    while (i < middle || j < right) {
        if (j == right || (i < middle && pref[i] <= pref[j])) {
            bufferArray[pos++] = pref[i++];
        } else {
            bufferArray[pos++] = pref[j++];
        }
    }

    for (int k = left; k < right; k++) {
        pref[k] = bufferArray[k];
    }

    return total;
}

int main() {
    cin >> n >> limitValue;

    pref.assign(n + 1, 0);
    bufferArray.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        ll value;
        cin >> value;
        pref[i] = pref[i - 1] + value;
    }

    cout << solveRange(0, n + 1) << '\n';

    return 0;
}
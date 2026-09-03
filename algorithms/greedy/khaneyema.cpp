#include <bits/stdc++.h>
using namespace std;

void mergeSort(vector<pair<long long,int>>& a, int l, int r) {

    if (l >= r)
        return;

    int mid = (l + r) / 2;

    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);

    vector<pair<long long,int>> temp;

    int i = l;
    int j = mid + 1;

    while (i <= mid && j <= r) {

        if (a[i].first <= a[j].first) {
            temp.push_back(a[i]);
            i++;
        }
        else {
            temp.push_back(a[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(a[i]);
        i++;
    }

    while (j <= r) {
        temp.push_back(a[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        a[l + k] = temp[k];
    }
}

int main() {
    int n;
    cin >> n;

    vector<long long> cost(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    vector<pair<long long,int>> roofs;

    for (int i = 1; i <= n; i++) {
        roofs.push_back({cost[i], i});
    }

    mergeSort(roofs, 0, n - 1);

    long long ans = 0;

    int cur = 0;

    while (cur < n) {

        int nextRoof = n;

        for (int i = 0; i < n; i++) {

            int idx = roofs[i].second;

            if (idx > cur) {
                nextRoof = idx;
                break;
            }
        }

        ans += cost[nextRoof] * (nextRoof - cur);

        cur = nextRoof;
    }

    cout << ans;
}

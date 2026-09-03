#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 50005;
const int MAXK = 105;
vector<int> adj[MAXN];

long long answer = 0;
int n, k;
int dp[MAXN][MAXK];

void DFS(int u, int parent) {
    dp[u][0] = 1;
    for (int v : adj[u]) {
        if (v == parent) 
            continue;

        DFS(v, u);

        for (int i = 0; i < k; ++i) {
            answer += 1LL * dp[u][i] * dp[v][k - i - 1];
        }
        for (int j = 1; j <= k; ++j) {
            dp[u][j] += dp[v][j - 1];
        }
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1, -1);

    cout << answer << "\n";
    return 0;
}
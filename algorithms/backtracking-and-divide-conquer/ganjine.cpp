#include <bits/stdc++.h>
using namespace std;

int n;
int board[25][25];
bool seen[25][25];
vector<pair<int, int>> rout;

bool inside(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

bool dfs(int r, int c) {
    rout.push_back({r, c});
    seen[r][c] = true;

    int target = n / 2;

    if (r == target && c == target) {
        return true;
    }

    int step = board[r][c];
    int nextR[] = {r + step, r - step, r, r};
    int nextC[] = {c, c, c + step, c - step};

    for (int i = 0; i < 4; i++) {
        int nr = nextR[i];
        int nc = nextC[i];

        if (inside(nr, nc) && !seen[nr][nc]) {
            if (dfs(nr, nc)) {
                return true;
            }
        }
    }

    seen[r][c] = false;
    rout.pop_back();

    return false;
}

int main() {
    cin>> n;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cin >> board[row][col];
        }
    }

    if (!dfs(0, 0)) {
        cout << "Impossible\n";
        return 0;
    }

    cout << rout.size() << '\n';

    for (auto cell : rout) {
        cout << cell.first << ' ' << cell.second << '\n';
    }

    return 0;
}
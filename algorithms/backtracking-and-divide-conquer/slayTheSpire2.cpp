#include <bits/stdc++.h>
using namespace std;

const int SZ = 100000 + 10;
int n, q;
int startValue[SZ];
vector<int> kids[SZ];

int father[SZ];
int heightLevel[SZ];
int subtreeCount[SZ];
int mainChild[SZ];

int lineStart[SZ];
int orderId[SZ];
int orderValue[SZ];
int orderTimer = 0;

int compressedLimit[2];
int fixedPrefix[2][SZ];

struct XorFenwick {
    int bit[SZ];

    void applyPoint(int index, int value) {
        while (index < SZ) {
            bit[index] ^= value;
            index += index & -index;
        }
    }

    int readPoint(int index) {
        int answer = 0;

        while (index > 0) {
            answer ^= bit[index];
            index -= index & -index;
        }

        return answer;
    }

    void applyRange(int left, int right, int value) {
        if (left > right) return;

        applyPoint(left, value);
        applyPoint(right + 1, value);
    }
};

XorFenwick fenwick[2][2];

int compactId(int realIndex) {
    return (realIndex + 1) / 2;
}

void updateSameKind(
    int layer,
    int left,
    int right,
    int wantedKind,
    int value
) {
    if (left > right) return;

    if ((left & 1) != wantedKind) left++;
    if ((right & 1) != wantedKind) right--;

    if (left > right) return;

    fenwick[layer][wantedKind].applyRange(
        compactId(left),
        compactId(right),
        value
    );
}

void updateCompactLine(int layer, int left, int right, int value) {
    if (left > right) return;

    updateSameKind(layer, left, right, left & 1, value);

    if ((right - left + 1) & 1) {
        updateSameKind(layer, right + 1, compressedLimit[layer], 0, value);
        updateSameKind(layer, right + 1, compressedLimit[layer], 1, value);
    }
}

int prefixCompact(int layer, int index) {
    if (index <= 0) return 0;

    int kind = index & 1;

    return fixedPrefix[layer][index] ^
           fenwick[layer][kind].readPoint(compactId(index));
}

int queryCompact(int layer, int left, int right) {
    if (left > right) return 0;

    return prefixCompact(layer, right) ^
           prefixCompact(layer, left - 1);
}

void updateRealPositions(int left, int right, int value) {
    for (int kind = 0; kind <= 1; kind++) {
        int l = left;
        int r = right;

        if ((l & 1) != kind) l++;
        if ((r & 1) != kind) r--;

        if (l <= r) {
            updateCompactLine(
                kind,
                compactId(l),
                compactId(r),
                value
            );
        }
    }
}

int queryRealPositions(int left, int right, int wantedKind) {
    if ((left & 1) != wantedKind) left++;
    if ((right & 1) != wantedKind) right--;

    if (left > right) return 0;

    return queryCompact(
        wantedKind,
        compactId(left),
        compactId(right)
    );
}

void prepareTreeInfo() {
    vector<int> order;
    order.reserve(n);

    order.push_back(0);

    for (int i = 0; i < (int)order.size(); i++) {
        int node = order[i];

        for (int child : kids[node]) {
            heightLevel[child] = heightLevel[node] + 1;
            order.push_back(child);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int node = order[i];

        subtreeCount[node] = 1;
        mainChild[node] = -1;

        for (int child : kids[node]) {
            subtreeCount[node] += subtreeCount[child];

            if (
                mainChild[node] == -1 ||
                subtreeCount[child] > subtreeCount[mainChild[node]]
            ) {
                mainChild[node] = child;
            }
        }
    }
}

void splitToLines() {
    stack<pair<int, int>> pending;

    pending.push({0, 0});

    while (!pending.empty()) {
        auto [node, top] = pending.top();
        pending.pop();

        while (node != -1) {
            lineStart[node] = top;
            orderId[node] = ++orderTimer;
            orderValue[orderTimer] = startValue[node];

            for (int child : kids[node]) {
                if (child != mainChild[node]) {
                    pending.push({child, child});
                }
            }

            node = mainChild[node];
        }
    }
}

void changePath(int a, int b, int value) {
    while (lineStart[a] != lineStart[b]) {
        if (heightLevel[lineStart[a]] < heightLevel[lineStart[b]]) {
            swap(a, b);
        }

        int top = lineStart[a];

        updateRealPositions(orderId[top], orderId[a], value);

        a = father[top];
    }

    if (heightLevel[a] > heightLevel[b]) {
        swap(a, b);
    }

    updateRealPositions(orderId[a], orderId[b], value);
}

int askPathFromSecondEvenDistance(int x, int y) {
    int a = x;
    int b = y;
    int answer = 0;

    int yParity = heightLevel[y] & 1;

    while (lineStart[a] != lineStart[b]) {
        if (heightLevel[lineStart[a]] < heightLevel[lineStart[b]]) {
            swap(a, b);
        }

        int top = lineStart[a];

        int wantedOrderParity =
            yParity ^ (heightLevel[top] & 1) ^ (orderId[top] & 1);

        answer ^= queryRealPositions(
            orderId[top],
            orderId[a],
            wantedOrderParity
        );

        a = father[top];
    }

    if (heightLevel[a] > heightLevel[b]) {
        swap(a, b);
    }

    int top = lineStart[a];

    int wantedOrderParity =
        yParity ^ (heightLevel[top] & 1) ^ (orderId[top] & 1);

    answer ^= queryRealPositions(
        orderId[a],
        orderId[b],
        wantedOrderParity
    );

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    startValue[0] = 0;
    father[0] = -1;
    heightLevel[0] = 0;

    for (int node = 1; node < n; node++) {
        int parent, value;
        cin >> parent >> value;

        father[node] = parent;
        startValue[node] = value;

        kids[parent].push_back(node);
    }

    prepareTreeInfo();
    splitToLines();

    compressedLimit[0] = n / 2;
    compressedLimit[1] = (n + 1) / 2;

    for (int kind = 0; kind <= 1; kind++) {
        for (int i = 1; i <= compressedLimit[kind]; i++) {
            int realPosition;

            if (kind == 1) {
                realPosition = 2 * i - 1;
            } else {
                realPosition = 2 * i;
            }

            fixedPrefix[kind][i] =
                fixedPrefix[kind][i - 1] ^ orderValue[realPosition];
        }
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int x, y;
            cin >> x >> y;

            cout << askPathFromSecondEvenDistance(x, y) << '\n';
        } else {
            int a, b, z;
            cin >> a >> b >> z;

            changePath(a, b, z);
        }
    }

    return 0;
}
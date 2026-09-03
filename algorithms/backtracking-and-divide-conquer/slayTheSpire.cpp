#include <bits/stdc++.h>
using namespace std;

const int LIM = 100000 + 10;

int n, q;
int firstValue[LIM];

vector<int> sons[LIM];

int up[LIM];
int levelOf[LIM];
int amount[LIM];
int bigSon[LIM];

int groupRoot[LIM];
int idOf[LIM];
int lineValue[LIM];
int idCounter = 0;

int basePrefix[LIM];

struct XorDiff {
    int data[LIM];

    void touch(int index, int value) {
        while (index <= n + 2) {
            data[index] ^= value;
            index += index & -index;
        }
    }

    void put(int left, int right, int value) {
        if (left > right) return;

        touch(left, value);
        touch(right + 1, value);
    }

    int read(int index) {
        int result = 0;

        while (index > 0) {
            result ^= data[index];
            index -= index & -index;
        }

        return result;
    }
};

XorDiff oddPlace;
XorDiff evenPlace;

int halfIndex(int x) {
    return (x + 1) / 2;
}

void addOnOneColor(int left, int right, int wanted, int value) {
    if (left > right) return;

    while (left <= right && left % 2 != wanted) left++;
    while (right >= left && right % 2 != wanted) right--;

    if (left > right) return;

    if (wanted == 0) {
        evenPlace.put(halfIndex(left), halfIndex(right), value);
    } else {
        oddPlace.put(halfIndex(left), halfIndex(right), value);
    }
}

int changedPrefix(int index) {
    if (index <= 0) return 0;

    int parity = index % 2;

    if (parity == 0) {
        return basePrefix[index] ^ evenPlace.read(halfIndex(index));
    }

    return basePrefix[index] ^ oddPlace.read(halfIndex(index));
}

int askLine(int left, int right) {
    return changedPrefix(right) ^ changedPrefix(left - 1);
}

void changeLine(int left, int right, int value) {
    addOnOneColor(left, right, left % 2, value);

    int len = right - left + 1;

    if (len % 2 == 1) {
        addOnOneColor(right + 1, n, 0, value);
        addOnOneColor(right + 1, n, 1, value);
    }
}

void collectInfo(int root) {
    stack<int> st;
    vector<int> order;

    st.push(root);
    up[root] = -1;
    levelOf[root] = 0;

    while (!st.empty()) {
        int v = st.top();
        st.pop();

        order.push_back(v);

        for (int u : sons[v]) {
            up[u] = v;
            levelOf[u] = levelOf[v] + 1;
            st.push(u);
        }
    }

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];

        amount[v] = 1;
        bigSon[v] = -1;

        for (int u : sons[v]) {
            amount[v] += amount[u];

            if (bigSon[v] == -1 || amount[u] > amount[bigSon[v]]) {
                bigSon[v] = u;
            }
        }
    }
}

void makeLines(int root) {
    stack<pair<int, int>> pending;
    pending.push({root, root});

    while (!pending.empty()) {
        int start = pending.top().first;
        int head = pending.top().second;
        pending.pop();

        int v = start;

        while (v != -1) {
            groupRoot[v] = head;
            idOf[v] = ++idCounter;
            lineValue[idCounter] = firstValue[v];

            for (int u : sons[v]) {
                if (u != bigSon[v]) {
                    pending.push({u, u});
                }
            }

            v = bigSon[v];
        }
    }
}

int pathAsk(int a, int b) {
    int answer = 0;

    while (groupRoot[a] != groupRoot[b]) {
        if (levelOf[groupRoot[a]] < levelOf[groupRoot[b]]) {
            swap(a, b);
        }

        int top = groupRoot[a];

        answer ^= askLine(idOf[top], idOf[a]);

        a = up[top];
    }

    if (levelOf[a] > levelOf[b]) {
        swap(a, b);
    }

    answer ^= askLine(idOf[a], idOf[b]);

    return answer;
}

void pathChange(int a, int b, int value) {
    while (groupRoot[a] != groupRoot[b]) {
        if (levelOf[groupRoot[a]] < levelOf[groupRoot[b]]) {
            swap(a, b);
        }

        int top = groupRoot[a];

        changeLine(idOf[top], idOf[a], value);

        a = up[top];
    }

    if (levelOf[a] > levelOf[b]) {
        swap(a, b);
    }

    changeLine(idOf[a], idOf[b], value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    firstValue[0] = 0;

    for (int node = 1; node < n; node++) {
        int parent, value;
        cin >> parent >> value;

        firstValue[node] = value;
        sons[parent].push_back(node);
    }

    collectInfo(0);
    makeLines(0);

    for (int i = 1; i <= n; i++) {
        basePrefix[i] = basePrefix[i - 1] ^ lineValue[i];
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int x, y;
            cin >> x >> y;

            cout << pathAsk(x, y) << '\n';
        } else {
            int a, b, z;
            cin >> a >> b >> z;

            pathChange(a, b, z);
        }
    }

    return 0;
}
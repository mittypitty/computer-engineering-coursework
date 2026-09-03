#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// struct DSU {
//     vector<int> parent;
//     DSU(int n) {
//         parent.resize(n + 1);
//         for (int i = 1; i <= n; ++i) {
//             parent[i] = i;
//         }
//     }
//     int find(int i) {
//         if (parent[i] == i)
//             return i;
//         return parent[i] = find(parent[i]);
//     }
//     void unite(int i, int j) {
//         int root_i = find(i);
//         int root_j = find(j);
//         if (root_i != root_j) {
//             parent[root_i] = root_j;
//         }
//     }
// };

struct DSU {
    vector<int> parent;
    vector<int> size;

    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); 
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            if (size[root_i] < size[root_j]) {
                swap(root_i, root_j);
            }
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
        }
    }
};


struct Query {
    int u, v, h, id;
    bool operator<(const Query& other) const {
        return h > other.h;
    }
};

struct Road {
    int u, v, h;
    bool operator<(const Road& other) const {
        return h > other.h;
    }
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int m;

    cin >> n >> m;

    vector<Road> roads(m);
    for(int i = 0; i < m; i++) {
        cin >> roads[i].u >> roads[i].v >> roads[i].h;
    }

    int q;
    cin >> q;

    vector<Query> queries(q);
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].u >> queries[i].v >> queries[i].h;
        queries[i].id = i;
    }

    sort(roads.begin(), roads.end());
    sort(queries.begin(), queries.end());


    DSU dsu(n);
    vector<bool> answer(q);
    int roadIdx = 0;

    for (int i = 0; i < q; ++i) {
        while (roadIdx < m && roads[roadIdx].h >= queries[i].h) {
            dsu.unite(roads[roadIdx].u, roads[roadIdx].v);
            roadIdx++;
        }

        if (dsu.find(queries[i].u) == dsu.find(queries[i].v)) {
            answer[queries[i].id] = true;
        } 
        else {
            answer[queries[i].id] = false;
        }
    }
    
    for (int i = 0; i < q; ++i) {
        if (answer[i]) {
            cout << "YES\n";
        } 
        else {
            cout << "NO\n";
        }
    }

    return 0;
}
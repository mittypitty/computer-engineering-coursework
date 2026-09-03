#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); 
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            if (size[root_i] < size[root_j]) {
                swap(root_i, root_j);
            }
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            return true;
        }
        return false;
    }
};

struct Edge {
    int u, v;
    long long w;

    bool operator<(const Edge& other) const {
        return w > other.w; 
    }
};


template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1);
    vector<T> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] < R[j] || (!(R[j] < L[i]) && true)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left >= right)
        return;
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    int n;
    cin >> n;

    //int A[n][n];
    //int B[n][n];
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<long long>> B(n, vector<long long>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n;j++) {
            cin >> A[i][j];
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n;j++) {
            cin >> B[i][j];
        }
    }

    int i_xor;
    int j_xor;
    
    for(int i = 0; i < n; i++) {
        cin >> i_xor;
    }
    for(int i = 0; i < n; i++) {
        cin >> j_xor;
    }

    vector<Edge> edges;
    long long total_cost = 0;
    long long max_forest_weight = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] == -1) {
                int u = i;
                int v = n + j;
                long long weight = B[i][j];
                edges.push_back({u, v, weight});
                total_cost += weight;
            }
        }
    }

    DSU dsu(2 * n);

    if(!edges.empty()) {
        mergeSort(edges, 0, edges.size() - 1);
    }

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            max_forest_weight += edge.w;
        }
    }
    
    cout << total_cost - max_forest_weight;

    return 0;
}
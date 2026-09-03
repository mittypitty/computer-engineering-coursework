#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


struct edge {
    int u, v, w;
};

struct dsu {
    int *p;
    int n;

    dsu(int n) : n(n) {
        p = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }

    bool unit(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) {
            return false;
        }

        p[b] = a;
        return true;
    }

    int find(int x) {
        if(p[x] == x) {
            return x;
        }
        else {
            return p[x] = find(p[x]);
        }
    }
};


int main() {
    int n;
    cin >> n;


    int **a = new int *[n];
    int **b = new int *[n];

    int *row = new int[n];
    int *column = new int[n];

    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
        b[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> row[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> column[i];
    }

    int edgecnt;
    //edge *edges = new edge[edgecnt];
    edgecnt = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(a[i][j] == -1) {
                edgecnt += 1;
            }
        }
    }

    edge *edges = new edge[edgecnt];
    long long sum = 0;
    long long keep = 0;
    int index = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(a[i][j] == -1) {
                edges[index++] = { 
                    i, n + j, b[i][j] 
                };
                sum += b[i][j];
            }
        }
    }


    sort(edges,(edges + edgecnt), 
    [](const edge &x, const edge &y){
        return x.w > y.w;
    });

    dsu dsu(2 * n);

    long long answer;

    for (int i = 0; i < edgecnt; i++) {
        edge &e = edges[i];
        if (dsu.unit(e.u, e.v)) {
            keep += e.w;
        }
    }

    answer = sum - keep;
    cout << answer;

    return 0;

}



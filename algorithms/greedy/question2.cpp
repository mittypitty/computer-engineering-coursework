#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;


int  main() {
    int n;
    cin >> n;

    int sum = 0;
    int max = 0;

    //int graph[200005][2];
    vector<vector<int>> graph(n + 1);
    //int deg[200005];
    //int leafcnt[200005];
    vector<int> leafcnt(n + 1, 0);

    if(n == 2) {
        cout << 0;
        return 0;
    }
        for (int i = 0; i < n - 1; i++) {
            int u;
            int v;
            cin >> u >> v;

            graph[u].push_back(v);

            graph[v].push_back(u);
            // if(deg[u] < 2) {
            //     graph[u][deg[u]] = v;
            // }
            // deg[u]++;
            // if(deg[v] < 2) {
            //     graph[v][deg[v]] = u;
            // }
            // deg[v]++;
        }

        int parent;
        for (int i = 1; i <= n; i++) {
            if(graph[i].size() == 1) {
                sum += 1;
                parent = graph[i][0];
                leafcnt[parent] += 1;
            }
        }

        for (int i = 1; i <= n; i++) {
            if(leafcnt[i] > max) {
                max = leafcnt[i];
            }
        }


        int answer = sum - max;
        cout << answer;
        return 0;
    

    
}
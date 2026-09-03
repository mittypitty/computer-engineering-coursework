#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm> 

using namespace std;

const long long infinite = numeric_limits<long long>::max();

struct Edge {
    int u, v;
    long long w;
};

struct Neighbor {
    int to;
    long long w_neighbor;
};

vector<Edge> MWSP(int num, const vector<vector<Neighbor>>& adj, int start) {
    vector<long long> dist(num + 1, infinite);
    dist[start] = 0;

    priority_queue<
        pair<long long, int>, 
        vector<pair<long long, int>>, 
        greater<pair<long long, int>>
    > pq;
    
    pq.push({0, start});

    while (!pq.empty()) {
        long long current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (current_dist > dist[u]) {
            continue;
        }

        for (const auto& neighbor : adj[u]) {
            int v = neighbor.to;
            long long w = neighbor.w_neighbor;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    vector<Edge> E1;

    for (int v = 1; v <= num; ++v) {
        if (v == start || dist[v] == infinite) {
            continue;
        }

        int best_u = -1;
        long long min_edge_weight = infinite;

        for (const auto& neighbor : adj[v]) {
            int u = neighbor.to;
            long long w = neighbor.w_neighbor;

            if (dist[u] + w == dist[v]) {
                if (w < min_edge_weight) {
                    min_edge_weight = w;
                    best_u = u;
                }
            }
        }

        if (best_u != -1) {
            E1.push_back({min(best_u, v), max(best_u, v), min_edge_weight});
        }
    }

    return E1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Neighbor>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int u_start;
    cin >> u_start;

    vector<Edge> e1 = MWSP(n, adj, u_start);

    long long cost = 0;
    for (const auto& edge : e1) {
        cost += edge.w;
    }

    cout << cost << "\n";

    for (const auto& edge : e1) {
        cout << edge.u << " " << edge.v << " ";
    }

    return 0;
}

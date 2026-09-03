#include <iostream>
#include <vector>

std::vector<std::vector<int>> connections;
std::vector<int> cat_status;
int reachable_paths;
int max_consecutive_cats;
int num_nodes;

void explore_tree(int current_node, int parent_node, int current_consecutive_cats) {
    bool is_leaf = (current_node != 1 && connections[current_node].size() == 1) || connections[current_node].empty();

    if (is_leaf && current_consecutive_cats <= max_consecutive_cats)
        reachable_paths++;

    for (int neighbor_node : connections[current_node]) {
        if (neighbor_node != parent_node) {
            int next_consecutive_cats;

            if (cat_status[neighbor_node] == 1)
                next_consecutive_cats = current_consecutive_cats + 1;
            else
                next_consecutive_cats = 0;

            if (next_consecutive_cats <= max_consecutive_cats) {
                explore_tree(neighbor_node, current_node, next_consecutive_cats);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> num_nodes >> max_consecutive_cats;
    cat_status.resize(num_nodes + 1);

    for (int i = 1; i <= num_nodes; ++i)
        std::cin >> cat_status[i];

    connections.resize(num_nodes + 1);
    for (int i = 0; i < num_nodes - 1; ++i) {
        int node_u, node_v;
        std::cin >> node_u >> node_v;
        connections[node_u].push_back(node_v);
        connections[node_v].push_back(node_u);
    }

    reachable_paths = 0;
    explore_tree(1, -1, cat_status[1]);

    std::cout << reachable_paths << std::endl;

    return 0;
}
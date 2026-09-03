#include <iostream>
#include <vector>

std::vector<std::vector<int>> connection_graph;
std::vector<int> ancestor_map;
std::vector<int> subtree_leaf_count;

void traverse_and_count_leaves(int current_branch, int parent_branch) {
    ancestor_map[current_branch] = parent_branch;
    bool is_a_leaf = true;

    for (int neighbor_branch : connection_graph[current_branch]) {
        if (neighbor_branch != parent_branch) {
            is_a_leaf = false;
            traverse_and_count_leaves(neighbor_branch, current_branch);
            subtree_leaf_count[current_branch] += subtree_leaf_count[neighbor_branch];
        }
    }
    
    if (is_a_leaf && current_branch != 1)
        subtree_leaf_count[current_branch] = 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int test_cases;
    std::cin >> test_cases;

    for (int loop_iter_t = 0; loop_iter_t < test_cases; ++loop_iter_t) {
        int node_quantity;
        std::cin >> node_quantity;

        connection_graph.assign(node_quantity + 1, std::vector<int>());
        subtree_leaf_count.assign(node_quantity + 1, 0);
        ancestor_map.assign(node_quantity + 1, 0);

        for (int loop_iter_j = 0; loop_iter_j < node_quantity - 1; ++loop_iter_j) {
            int node_u, node_v;
            std::cin >> node_u >> node_v;
            connection_graph[node_u].push_back(node_v);
            connection_graph[node_v].push_back(node_u);
        }

        traverse_and_count_leaves(1, -1);

        int query_count;
        std::cin >> query_count;
        for (int loop_iter_j = 0; loop_iter_j < query_count; ++loop_iter_j) {
            int node_x, node_y;
            std::cin >> node_x >> node_y;

            std::cout << (long long)subtree_leaf_count[node_x] * subtree_leaf_count[node_y] << "\n";
        }
    }

    return 0;
}
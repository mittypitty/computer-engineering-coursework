#include <iostream>
#include <vector>
#include <algorithm> 


class PathSegment {
public:
    int destination_node;
    long long travel_duration;

    PathSegment(int dest, long long dur) : destination_node(dest), travel_duration(dur) {}
};

std::vector<std::vector<PathSegment>> adjacency_list;
std::vector<int> visit_tracker;
long long maximum_reach = 0;
int farthest_point = 0;
int traversal_id = 1;

void explore_paths(int current_node, long long current_distance) {
    visit_tracker[current_node] = traversal_id;
    if (current_distance > maximum_reach) {
        maximum_reach = current_distance;
        farthest_point = current_node;
    }
    for (const auto& segment : adjacency_list[current_node]) {
        if (visit_tracker[segment.destination_node] != traversal_id) {
            explore_paths(segment.destination_node, current_distance + segment.travel_duration);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int node_count;
    std::cin >> node_count;

    adjacency_list.resize(node_count + 1);
    visit_tracker.resize(node_count + 1);

    long long total_duration_sum = 0;
    for (int i = 0; i < node_count - 1; ++i) {
        int node_a, node_b;
        long long duration_val;
        std::cin >> node_a >> node_b >> duration_val;
        adjacency_list[node_a].push_back(PathSegment(node_b, duration_val));
        adjacency_list[node_b].push_back(PathSegment(node_a, duration_val));
        total_duration_sum += duration_val;
    }

    explore_paths(1, 0);
    traversal_id++;
    maximum_reach = 0;

    explore_paths(farthest_point, 0);
    std::cout << (total_duration_sum * 2) - maximum_reach << std::endl;

    return 0;
}
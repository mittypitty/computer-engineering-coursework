import pandas as pd
import numpy as np
import heapq
from collections import defaultdict


# --------------------------------------------------
# Load CSV and build cost matrix for (weekday, hour)
# --------------------------------------------------
def load_cost_matrix(csv_path, weekday, hour, n_nodes=20):
    df = pd.read_csv(csv_path)

    subset = df[
        (df["weekday"] == weekday) &
        (df["hour"] == hour)
    ]

    cost_matrix = np.zeros((n_nodes, n_nodes))

    for _, row in subset.iterrows():
        i = int(row["i"])
        j = int(row["j"])
        cost_matrix[i, j] = row["traffic"]

    return cost_matrix


# --------------------------------------------------
# Build graph: (neighbor, base_cost, traffic_delay)
# --------------------------------------------------
def build_graph_from_matrix(cost_matrix):
    graph = defaultdict(list)
    n = cost_matrix.shape[0]

    for i in range(n):
        for j in range(n):
            if i != j and cost_matrix[i, j] > 0:
                base_cost = 1
                traffic_delay = cost_matrix[i, j]
                graph[i].append((j, base_cost, traffic_delay))

    return graph


# --------------------------------------------------
# Heuristic (admissible)
# --------------------------------------------------
def heuristic(node, goal):
    return 0


# --------------------------------------------------
# A* Search
# Returns: path, total_cost, t
# --------------------------------------------------
def a_star_search(graph, start, goal):

    # (f, g, t, node, path)
    open_list = []
    heapq.heappush(open_list, (0, 0, 0, start, [start]))

    best_g = {start: 0}

    while open_list:
        f, g, t, current, path = heapq.heappop(open_list)

        if current == goal:
            return path, g, t

        for neighbor, base_cost, traffic_delay in graph[current]:
            new_g = g + base_cost + traffic_delay
            new_t = t + traffic_delay

            if neighbor not in best_g or new_g < best_g[neighbor]:
                best_g[neighbor] = new_g
                new_f = new_g + heuristic(neighbor, goal)

                heapq.heappush(
                    open_list,
                    (new_f, new_g, new_t, neighbor, path + [neighbor])
                )

    return [], float("inf"), float("inf")


# --------------------------------------------------
# Main
# --------------------------------------------------
if __name__ == "__main__":

    CSV_PATH = "traffic_4weeks_clean.csv"

    weekday = 1   # Monday
    hour = 8      # 8 AM
    start = 0
    goal = 15

    cost_matrix = load_cost_matrix(CSV_PATH, weekday, hour)
    graph = build_graph_from_matrix(cost_matrix)

    path, total_cost, t = a_star_search(graph, start, goal)

    print("Path:", path)
    print("Total Cost:", total_cost)
    print("Traffic Delay t:", t)


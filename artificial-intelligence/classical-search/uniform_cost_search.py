import pandas as pd
import heapq
from collections import defaultdict
import numpy as np


def load_and_prepare_data(csv_path):
    df = pd.read_csv(csv_path)

    traffic_data = df.groupby(['weekday', 'hour', 'i', 'j'])['traffic'].last().reset_index()
    
    cost_matrices = {}
    
    for weekday in range(1, 8):  # Weekdays 1-7
        for hour in range(24):   # Hours 0-23
            subset = traffic_data[(traffic_data['weekday'] == weekday) & 
                                   (traffic_data['hour'] == hour)]
            
            # Build cost matrix
            matrix = np.zeros((20, 20))
            for _, row in subset.iterrows():
                matrix[int(row['i']), int(row['j'])] = row['traffic']
            
            cost_matrices[(weekday, hour)] = matrix
    
    print(f"Number of cost matrices: {len(cost_matrices)}")
    return cost_matrices


def build_graph_from_matrix(cost_matrix):
    graph = defaultdict(list)
    n = cost_matrix.shape[0]
    
    for i in range(n):
        for j in range(n):
            if i != j and cost_matrix[i, j] > 0:  # Valid edge
                graph[i].append((j, cost_matrix[i, j]))
    
    return graph


def uniform_cost_search(graph, start, goal):

    counter = 0
    priority_queue = [(0, counter, start)]
    visited = set()

    while priority_queue:
        current_cost, _, current_node = heapq.heappop(priority_queue)

        if current_node in visited:
            continue

        visited.add(current_node)

        if current_node == goal:
            return current_cost

        for neighbor, edge_cost in graph[current_node]:
            if neighbor not in visited:
                counter += 1
                heapq.heappush(
                    priority_queue,
                    (current_cost + edge_cost, counter, neighbor)
                )

    return float('inf')



def find_all_paths_ucs(graph, start, goal, num_nodes=20, k=3):

    paths = []
    excluded_edges = set()
    
    for _ in range(k):
        modified_graph = defaultdict(list)
        for node in graph:
            for neighbor, cost in graph[node]:
                if (node, neighbor) not in excluded_edges:
                    modified_graph[node].append((neighbor, cost))
        
        cost, path, _ = uniform_cost_search(modified_graph, start, goal, num_nodes)
        
        if cost == float('inf'):
            break
        
        paths.append((cost, path))
        if len(path) > 1:
            excluded_edges.add((path[-2], path[-1]))
    return paths


def predict_traffic_for_future_week(cost_matrices, weekday, hour, start, goal):

    if (weekday, hour) not in cost_matrices:
        print(f"No data for day {weekday} hour {hour}!")
        return None
    
    cost_matrix = cost_matrices[(weekday, hour)]
    graph = build_graph_from_matrix(cost_matrix)
    total_cost, path, nodes_expanded = uniform_cost_search(graph, start, goal)
    
    return {
        'weekday': weekday,
        'hour': hour,
        'start': start,
        'goal': goal,
        'total_cost': total_cost,
        'path': path,
        'nodes_expanded': nodes_expanded
    }


def visualize_path(path, cost_matrix):

    print("\n" + "="*50)
    print("Path Details:")
    print("="*50)
    
    total = 0
    for i in range(len(path) - 1):
        from_node = path[i]
        to_node = path[i + 1]
        cost = cost_matrix[from_node, to_node]
        total += cost
        print(f"  Node {from_node} -> Node {to_node} : Cost = {cost}")
    
    print("-"*50)
    print(f"  Total Cost: {total}")
    print("="*50)


def main():
    csv_path = "traffic_4weeks_clean.csv"
    cost_matrices = load_and_prepare_data(csv_path)

    weekday = 1
    hour = 8
    start = 0
    goal = 15

    cost_matrix = cost_matrices[(weekday, hour)]
    graph = build_graph_from_matrix(cost_matrix)

    min_cost = uniform_cost_search(graph, start, goal)

    print("Minimum Cost:", min_cost)



def interactive_mode():
    """
    Interactive mode for user
    """
    csv_path = "traffic_4weeks_clean.csv"
    cost_matrices = load_and_prepare_data(csv_path)
    
    while True:
        print("\n" + "="*50)
        print("Traffic Prediction with Uniform Cost Search")
        print("="*50)
        
        try:
            weekday = int(input("Weekday (1=Saturday to 7=Friday): "))
            hour = int(input("Hour (0-23): "))
            start = int(input("Origin node (0-19): "))
            goal = int(input("Destination node (0-19): "))
            
            if not (1 <= weekday <= 7 and 0 <= hour <= 23 and 
                    0 <= start <= 19 and 0 <= goal <= 19):
                print("Invalid values!")
                continue
            
            result = predict_traffic_for_future_week(cost_matrices, weekday, hour, start, goal)
            
            if result:
                print(f"\nBest Path: {' -> '.join(map(str, result['path']))}")
                print(f"Total Cost: {result['total_cost']}")
                
                cost_matrix = cost_matrices[(weekday, hour)]
                visualize_path(result['path'], cost_matrix)
            
        except ValueError:
            print("Please enter a number!")
        except KeyboardInterrupt:
            print("\nGoodbye!")
            break


if __name__ == "__main__":
    import sys
    
    if len(sys.argv) > 1 and sys.argv[1] == "-i":
        interactive_mode()
    else:
        main()

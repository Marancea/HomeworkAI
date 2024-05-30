#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;
// Define a structure for a node in the search tree
struct Node {
    int level;                // Current level (or depth) in the search tree
    int current_city;         // Current city
    int cost;                 // Cost to reach this node
    int heuristic;            // Heuristic estimate of the cost to complete the tour
    vector<bool> visited; // Vector to keep track of visited cities
    vector<int> path;    // Path taken to reach this node

    // Constructor to initialize the node
    Node(int lvl, int city, int cst, int h, vector<bool> vis, vector<int> p)
        : level(lvl), current_city(city), cost(cst), heuristic(h), visited(vis), path(p) {}

    // Comparator for the priority queue (min-heap)
    bool operator>(const Node& other) const {
        return cost + heuristic > other.cost + other.heuristic;
    }
};

// Function to calculate the heuristic (minimum edge cost of unvisited cities)
int calculateHeuristic(const vector<vector<int>>& distances, const vector<bool>& visited) {
    int min_edge = INT_MAX;
    for (int i = 0; i < distances.size(); ++i) {
        if (!visited[i]) {
            for (int j = 0; j < distances.size(); ++j) {
                if (!visited[j] && i != j) {
                    min_edge = min(min_edge, distances[i][j]);
                }
            }
        }
    }
    return min_edge == INT_MAX ? 0 : min_edge;
}

// Function to perform A* Search for TSP
int astar_tsp(int n, const vector<vector<int>>& distances) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<bool> initial_visited(n, false);
    initial_visited[0] = true; // Start from city 0

    vector<int> initial_path = { 0 }; // Path starts from city 0
    int initial_heuristic = calculateHeuristic(distances, initial_visited);
    Node start(0, 0, 0, initial_heuristic, initial_visited, initial_path);
    pq.push(start);

    int min_cost = INT_MAX; // Initialize the minimum cost to a large value
    vector<int> best_path;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.level == n - 1) {
            int return_cost = distances[node.current_city][0];
            if (node.cost + return_cost < min_cost) {
                min_cost = node.cost + return_cost;
                best_path = node.path;
                best_path.push_back(0); // Return to the starting city
            }
            continue;
        }

        for (int i = 0; i < n; ++i) {
            if (!node.visited[i]) {
                vector<bool> new_visited = node.visited;
                new_visited[i] = true;
                vector<int> new_path = node.path;
                new_path.push_back(i);
                int new_cost = node.cost + distances[node.current_city][i];
                int new_heuristic = calculateHeuristic(distances, new_visited);
                Node next_node(node.level + 1, i, new_cost, new_heuristic, new_visited, new_path);
                pq.push(next_node);
            }
        }
    }

    // Print the best path found
    cout << "The best path using ASTAR is: ";
    for (int city : best_path) {
        cout << city << " ";
    }
    cout << endl;

    return min_cost;
}

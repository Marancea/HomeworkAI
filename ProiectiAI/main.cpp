#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;


// Function declarations for BFS, UCS, and A* search
int bfs_tsp(int n, const vector<vector<int>>& distances);
int ucs_tsp(int n, const std::vector<std::vector<int>>& distances);
int astar_tsp(int n, const std::vector<std::vector<int>>& distances);

// Function to generate a random distance matrix
void generateRandomMatrix(int n, vector<vector<int>>& distances) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (i == j) {
                distances[i][j] = 0;
            }
            else {
                int random_distance = rand() % 101; // Random distance between 0 and 100
                distances[i][j] = random_distance;
                distances[j][i] = random_distance; // Ensure symmetry
            }
        }
    }
}


// Function to print the distance matrix
void printMatrix(const vector<vector<int>>& distances) {
    for (const auto& row : distances) {
        for (const auto& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {

    // Number of cities variable
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;
    vector<vector<int>> distances(n, vector<int>(n));

    // Choice variable for the input matrix
    cout << "Choose 1 to generete the matrix by hand or Choose 2 to generate the matrix randomly: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        // User enters the distance matrix manually
        cout << "Enter the distance matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> distances[i][j];
            }
        }
    }
    else if (choice == 2)
    {
        // User generates the distance matrix randomlly
        generateRandomMatrix(n, distances);
        std::cout << "Generated distance matrix:\n";
        printMatrix(distances);
    }
    else 
    {
        cout << "Invalid choice!" << std::endl;
        return 1;
    }

        // Measure the execution time of the BFS algorithm and output the results
        cout << "\n";
        cout << "==========================BFS=================================\n";
        auto start1 = chrono::high_resolution_clock::now();
        int result1 = bfs_tsp(n, distances);
        cout << "The minimum cost to visit all cities using BFS_TSP is: " << result1 << endl;
        auto end1 = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed1 = end1 - start1;
        cout << "Time taken: " << elapsed1.count() << " seconds" << endl;

        // Measure the execution time of the UCS algorithm and output the results
        cout << "==========================UCS=================================\n";
        auto start2 = chrono::high_resolution_clock::now();
        int result2 = ucs_tsp(n, distances);        
        cout << "The minimum cost to visit all cities using UCS_TSP is: " << result2 << endl;
        auto end2 = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed2 = end2 - start2;
        cout << "Time taken: " << elapsed2.count() << " seconds" << endl;

        // Measure the execution time of the A* algorithm and output the results
        cout << "==========================A*==================================\n";
        auto start3 = chrono::high_resolution_clock::now();
        int result3 = ucs_tsp(n, distances);
        cout << "The minimum cost to visit all cities using ASTAR_TSP is: " << result3 << endl;
        auto end3 = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed3 = end3 - start3;
        cout << "Time taken: " << elapsed3.count() << " seconds" << endl;

    return 0;
}
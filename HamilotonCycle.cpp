#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int v, vector<vector<int>>& graph, vector<int>& path, int pos) {
    // Check if the vertex is adjacent to the previously added vertex
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if the vertex has already been included in the path
    for (int i = 0; i < pos; i++) {
        if (path[i] == v)
            return false;
    }

    return true;
}

bool hamiltonianCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos) {
    // Base case: If all vertices are included in the path
    if (pos == graph.size()) {
        // Check if the last vertex is adjacent to the first vertex
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as the next candidate in the path
    for (int v = 1; v < graph.size(); v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(graph, path, pos + 1))
                return true;

            path[pos] = -1; // Backtrack
        }
    }

    return false;
}

bool hamiltonianCycle(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);

    // Start from the first vertex
    path[0] = 0;

    if (hamiltonianCycleUtil(graph, path, 1)) {
        cout << "Hamiltonian cycle exists:" << endl;
        for (int i = 0; i < V; i++)
            cout << path[i] << " ";
        cout << path[0] << endl;
        return true;
    } else {
        cout << "Hamiltonian cycle does not exist." << endl;
        return false;
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    hamiltonianCycle(graph);

    return 0;
}
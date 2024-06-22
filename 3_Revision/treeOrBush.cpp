#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool dfs(unordered_map<int, vector<int>>&, unordered_set<int>&, int, int);

bool isTree(int n, vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> graph;
    unordered_set<int> visited;
    
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    int root = -1;
    for (auto& node : graph) {
        if (node.second.size() == 1) {
            root = node.first;
            break;
        }
    }

    if (root == -1) return false;

    if (!dfs(graph, visited, root, -1)) return false;

    if (visited.size() != n) return false;

    return true;
}

bool dfs(unordered_map<int, vector<int>>& graph, unordered_set<int>& visited, int node, int parent) {
    visited.insert(node);

    for (auto& neighbor : graph[node]) {
        if (neighbor != parent) { 
            if (visited.find(neighbor) != visited.end()) return false; 
            if (!dfs(graph, visited, neighbor, node)) return false;
        }
    }

    return true;
}

int main() {
    int E;
    cin >> E;
    vector<vector<int>> edges(E, vector<int>(2));
    for (int i = 0; i < E; ++i) {
        cin >> edges[i][0] >> edges[i][1];
    }

    int maxNode = 0;
    for (auto edge : edges) {
        maxNode = max(maxNode, max(edge[0], edge[1]));
    }

    if (isTree(maxNode, edges)) {
        cout << "Pohon\n";
    } else {
        cout << "Semak-semak\n";
    }

    return 0;
}

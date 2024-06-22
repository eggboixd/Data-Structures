#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<int> parent, rankVector;

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        if (rankVector[rootU] > rankVector[rootV]) {
            parent[rootV] = rootU;
        } else if (rankVector[rootU] < rankVector[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rankVector[rootU]++;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end());
    
    parent.resize(n);
    rankVector.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
    
    long long totalDistance = 0;
    for (const auto& edge : edges) {
        if (find(edge.u) != find(edge.v)) {
            unite(edge.u, edge.v);
            totalDistance += edge.weight;
        }
    }
    
    cout << totalDistance << '\n';

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};

bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

int find(vector<int>& parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);

    for (int i = 0; i < M; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(N + 1);
    vector<int> rank(N + 1, 0);
    
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    int totalCost = 0;
    int edgesUsed = 0;

    for (Edge& edge : edges) {
        if (find(parent, edge.u) != find(parent, edge.v)) {
            unionSets(parent, rank, edge.u, edge.v);
            edgesUsed++;
        } else {
            totalCost += edge.w;
        }
        
        if (edgesUsed == N - 1) {
            break;
        }
    }

    for (Edge& edge : edges) {
        if (find(parent, edge.u) != find(parent, edge.v)) {
            totalCost += edge.w;
        }
    }

    cout << totalCost << endl;

    return 0;
}

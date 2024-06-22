#include <bits/stdc++.h>
using namespace std;

struct Graph {
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    map<string, long> vertexMap; // Maps vertex names to indices
    vector<string> indexToVertex; // Maps indices to vertex names

    void init(const vector<string>& vertices) {
        vertexCount = vertices.size();
        edgeCount = 0;
        adjList.resize(vertexCount);
        indexToVertex = vertices;

        for (long i = 0; i < vertexCount; i++) {
            vertexMap[vertices[i]] = i;
        }
    }

    void add_edge(const string& vertex1, const string& vertex2) {
        long index1 = vertexMap[vertex1];
        long index2 = vertexMap[vertex2];
        adjList[index1].push_back(index2);
        adjList[index2].push_back(index1);
        edgeCount++;
    }

    bool bfs(const string& start, const string& end) {
        vector<bool> visited(vertexCount, false);
        queue<long> q;
        long startIndex = vertexMap[start];
        long endIndex = vertexMap[end];

        q.push(startIndex);
        visited[startIndex] = true;

        while (!q.empty()) {
            long temp = q.front();
            q.pop();

            if (temp == endIndex) {
                return true;
            }

            for (auto vertex : adjList[temp]) {
                if (!visited[vertex]) {
                    q.push(vertex);
                    visited[vertex] = true;
                }
            }
        }
        return false;
    }
};

int main() {
    int T;
    cin >> T;
    vector<string> friends(T);

    for (int i = 0; i < T; i++) {
        cin >> friends[i];
    }

    Graph g;
    g.init(friends);

    string command;
    while (cin >> command) {
        if (command == "ADD") {
            string V, W;
            cin >> V >> W;
            g.add_edge(V, W);
        } else if (command == "CHECK") {
            string V, W;
            cin >> V >> W;
            if (g.bfs(V, W)) {
                cout << "Healthy circle!" << endl;
            } else {
                cout << "Toxic circle, be friends please!" << endl;
            }
        } else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}

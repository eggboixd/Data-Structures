#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

class Graph {
public:
    Graph() {}

    void addNode(const string& node) {
        if (adjList.find(node) == adjList.end()) {
            adjList[node] = vector<string>();
        }
    }

    void addEdge(const string& node1, const string& node2) {
        addNode(node1);
        addNode(node2);

        adjList[node1].push_back(node2);
        adjList[node2].push_back(node1);
    }

    bool isConnected() {
        if (adjList.empty()) return true;

        unordered_map<string, bool> visited;
        string startNode = adjList.begin()->first;
        bfs(startNode, visited);

        // Check if all nodes were visited
        for (const auto& pair : adjList) {
            if (!visited[pair.first]) {
                return false;
            }
        }
        return true;
    }

    int countNodes() const {
        return adjList.size();
    }

private:
    unordered_map<string, vector<string>> adjList;

    void bfs(const string& startNode, unordered_map<string, bool>& visited) {
        queue<string> q;
        q.push(startNode);
        visited[startNode] = true;

        while (!q.empty()) {
            string currentNode = q.front();
            q.pop();

            for (const string& neighbor : adjList[currentNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    
    
    int t;
    cin >> t;
    
    if( t <= 10 && t > 0){
        for(int i = 0; i < t; i++){
            Graph g;
            int v, e;
            cin >> v >> e;

            for(int j = 0; j < e; j++){
                string v1, v2;
                cin >> v1 >> v2;
                g.addEdge(v1, v2);
            }

            //cout << g.countNodes() << endl;
            
            //if(g.isConnected()) cout << "true" << endl;
            //if(g.countNodes() < v) cout << "its less than v" << endl;

            if(g.isConnected() && g.countNodes() < v){
                cout << "Menyirkel" << endl;
            } else {
                cout << "Tidak Menyirkel" << endl;
            }
        }
    
    
    }
    



    /*
    cout << "The graph has " << g.countNodes() << " nodes." << endl;
    
    if (g.isConnected()) {
        cout << "The graph is connected." << endl;
    } else {
        cout << "The graph is not connected." << endl;
    }*/

    return 0;
}

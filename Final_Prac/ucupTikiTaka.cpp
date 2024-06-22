#include <bits/stdc++.h>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    
    void init(long v){
        vertexCount = v;
        edgeCount = 0;

        for(int i=0; i<vertexCount; i++){
            adjList.push_back({}); 
        }
    }

    void add_edge(long vertex1, long vertex2){
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    int bfs(long start, long end){
        vector<bool> visited(vertexCount, false);
        vector<long> distance(vertexCount, 0);
        queue<long> q;

        q.push(start);
        visited[start] = true;

        while(!q.empty()){
            long temp = q.front();
            q.pop();

            if (temp == end)
                return distance[temp];

            for(auto vertex:adjList[temp]){
                if (!visited[vertex]){
                    q.push(vertex);
                    visited[vertex] = true;
                    distance[vertex] = distance[temp] + 1;
                }
            }
        }
        return -1; 
    }
};

int main(){
    graph g;

    int n, e, q;
    cin >> n >> e >> q;

    g.init(n);

    for(int i = 0; i < e; i++){
        int a, b;
        cin >> a >> b;
        g.add_edge(a, b);
    }

    for(int i = 0; i < q; i ++){
        int check1, check2;
        cin >> check1 >> check2;
        cout << g.bfs(check1, check2) << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int dijkstra(int x, const vector<vector<pair<int, int>>> &adj, int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(x + 1, INF);
    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int d, u;
        tie(d, u) = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto &edge : adj[u]) {
            int v, weight;
            tie(v, weight) = edge;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist[end];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int x, y;
        cin >> x >> y;

        vector<vector<pair<int, int>>> adj(x + 1);

        for (int i = 0; i < y; ++i) {
            int pi, qi, ri;
            cin >> pi >> qi >> ri;
            adj[pi].emplace_back(qi, ri);
            adj[qi].emplace_back(pi, ri);  // Assuming undirected roads
        }

        int start, end;
        cin >> start >> end;

        int result = dijkstra(x, adj, start, end);

        if (result == INF) {
            cout << "I can't meet you baby :(" << endl;
        } else {
            cout << result << endl;
        }
    }

    return 0;
}

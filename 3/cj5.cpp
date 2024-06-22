#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 100

typedef struct {
    int dest;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAXV];
    int edgeCount;
} Vertex;

Vertex graph[MAXV];
int dist[MAXV];
int distWithFlight[MAXV];
int visited[MAXV];

void initializeGraph(int v) {
    for (int i = 0; i < v; i++) {
        graph[i].edgeCount = 0;
        dist[i] = INT_MAX;
        distWithFlight[i] = INT_MAX;
        visited[i] = 0;
    }
}

void addEdge(int src, int dest, int weight) {
    graph[src].edges[graph[src].edgeCount].dest = dest;
    graph[src].edges[graph[src].edgeCount].weight = weight;
    graph[src].edgeCount++;
}

void dijkstra(int v) {
    dist[0] = 0;
    distWithFlight[0] = 0;

    for (int i = 0; i < v; i++) {
        int u = -1;

        for (int j = 0; j < v; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        for (int j = 0; j < graph[u].edgeCount; j++) {
            Edge edge = graph[u].edges[j];
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }

            if (distWithFlight[u] + weight < distWithFlight[v]) {
                distWithFlight[v] = distWithFlight[u] + weight;
            }

            if (dist[u] < distWithFlight[v]) {
                distWithFlight[v] = dist[u];
            }
        }
    }
}

int main() {
    int v, e;
    scanf("%d %d", &v, &e);

    initializeGraph(v);

    for (int i = 0; i < e; i++) {
        int p, q, w;
        scanf("%d %d %d", &p, &q, &w);
        addEdge(p, q, w);
    }

    dijkstra(v);

    printf("%d\n", distWithFlight[v-1]);

    return 0;
}

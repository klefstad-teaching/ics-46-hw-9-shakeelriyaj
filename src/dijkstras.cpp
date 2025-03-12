#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"
    
using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);

    previous.resize(n);
    for (int i = 0; i < n; i++) {
        previous[i] = -1;
    }
    distance[source] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int minDist = INF;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && distance[v] < minDist) {
                minDist = distance[v];
                u = v;
            }
        }
        if (u == -1) {
            break; }

        visited[u] = true;

        for (size_t j = 0; i < G[u].size(); j++) {
            int v = G[u][j].dst;
            int w = G[u][j].weight;
            if (!visited[v] && distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (destination < 0 || destination >= (int)distances.size() || distances[destination] == INF) {
        return path;
    }

    int curr = destination;
    while (curr != -1) {
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
    }
    cout << "\n" << "Total Cost is " << total << "\n";
}

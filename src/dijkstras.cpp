#include "dijkstras.h"
#include <iostream>
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;

    vector<int> distance;
    // resize distance
    distance.assign(n, INF);

    // previous resize to -1
    previous.assign(n, -1);

    // graph visiteed resize to false
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source}); // {distance, vertex}
    distance[source] = 0;
    
    while (!pq.empty()) {
        // Extract vertex with minimum distance
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        // Mark true since visited
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                // Update distance of v
                distance[v] = distance[u] + weight;
                // Update prev vertex
                previous[v] = u;
                // Last add to pq
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

void print_path(const vector<int>& v, int total) {
    stack<int> path_stack;
    int current = total;
    while (current != -1) {
        path_stack.push(current);
        if (current >= 0 && current < v.size()) {
            current = v[current];
        } else {
            break; // Break if index is out of bounds
        }
    }
    while (!path_stack.empty()) {
        cout << path_stack.top() << " ";
        path_stack.pop();
    }
    cout << endl;
}

// Extracts the shortest path from source to destination
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (previous[destination] == -1 && distances[destination] == INF) {
        return path; 
    }
    
    stack<int> path_stack;
    int curr = destination;
    
    while (curr != -1) {
        path_stack.push(curr);

        curr = previous[curr];
    }
    
    while (!path_stack.empty()) {
        path.push_back(path_stack.top());
        path_stack.pop();
    }

    return path;
}
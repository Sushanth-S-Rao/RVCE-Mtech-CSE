// Bellman Ford

#include <bits/stdc++.h>
using namespace std;

// Bellman Ford function
void BellmanFord(int graph[][3], int V, int E, int src) {
	int dis[V];
    // Initialize distance of all vertices as infinite.
	for (int i = 0; i < V; i++)
		dis[i] = INT_MAX;

	// initialize distance of source as 0
	dis[src] = 0;

	// Relax all edges |V| - 1 times
	for (int i = 0; i < V - 1; i++) {
		for (int j = 0; j < E; j++) {
			if (dis[graph[j][0]] != INT_MAX && dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
				dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
		}
	}

	// Check for negative-weight cycles
	for (int i = 0; i < E; i++) {
		int x = graph[i][0];
		int y = graph[i][1];
		int weight = graph[i][2];
		if (dis[x] != INT_MAX && dis[x] + weight < dis[y])
			cout << "Graph contains negative weight cycle" << endl;
	}

	cout << "Vertex Distance from Source" << endl;
	for (int i = 0; i < V; i++)
		cout << i << "\t\t" << dis[i] << endl;
}


int main()
{
	int V = 8; // Number of vertices in graph
	int E = 11; // Number of edges in graph

	// Every edge has three values (u, v, w) where the edge is from vertex u to v. And weight of the edge is w.
	/*int graph[][3] = { { 0, 1, -1 }, { 0, 2, 4 },
					{ 1, 2, 3 }, { 1, 3, 2 }, 
					{ 1, 4, 2 }, { 3, 2, 5 }, 
					{ 3, 1, 1 }, { 4, 3, -3 } }; */

	int graph[][3] = { {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7}, {2, 5, 4}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1} };

	BellmanFord(graph, V, E, 0);
	return 0;
}

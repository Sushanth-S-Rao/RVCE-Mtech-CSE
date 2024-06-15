/* Open Ended Lab Program 6
You have a business with several offices; you want to lease phone lines to connect them up with each other, and the phone company charges different 
amounts of money to connect different pairs of cities. You are assigned the task of designing a telephone network. You want a set of lines that connects 
all your offices with a minimum total cost. Design an efficient network to remove some edges in the telephone and save money, say, for example, the 
telephone network looks like the one given below. Calculate the minimum total cost of the telephone network. */

// Technique: PRIM's Algorithm

#include <bits/stdc++.h>
#include<chrono>
using namespace std;
#define V 5

// Find the vertex with minimum key value, from the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// Print the constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V])
{
	auto start = chrono::high_resolution_clock::now();
	cout << "Edge \tWeight\n";
    int minT = 0;
	for (int i = 1; i < V; i++) {
		cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
        minT += graph[i][parent[i]];
    }
    cout << "Minimum Cost: " << minT;
}

// Construct and print MST for a graph represented using adjacency matrix representation
void primMST(int graph[V][V])
{
	// Array to store constructed MST
	int parent[V];

	// Key values used to pick minimum weight edge in cut
	int key[V];

	// To represent set of vertices included in MST
	bool mstSet[V];

	// Initialize all keys as INFINITE
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST
	key[0] = 0;

	// First node is always root of MST
	parent[0] = -1;

	// The MST will have V vertices
	for (int count = 0; count < V - 1; count++) {
		
		// Pick the minimum key vertex from the set of vertices not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not yet included in MST
		for (int v = 0; v < V; v++)

			// graph[u][v] is non zero only for adjacent vertices of m mstSet[v] is false for vertices not yet included in MST Update the key only
			// if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// Print the constructed MST
	printMST(parent, graph);
}


int main()
{      
	auto start = chrono::high_resolution_clock::now();                   
	int graph[V][V] = { { 0, 6, 3, 2, 0 },
						{ 6, 0, 5, 0, 1 },
						{ 3, 5, 0, 4, 5 },
						{ 2, 4, 4, 0, 6 },
						{ 0, 1, 5, 6, 0 } };


	// Print the solution
	primMST(graph);

	auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
	
	return 0;
}

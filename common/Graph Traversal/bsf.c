//
// Created by gaven on 2024/11/28.
//

/*
 * breadth-first search (BFS)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// BFS from given source s
void bfs(int adj[MAX][MAX], int V, int s) {
    // Create a queue for BFS
    int q[MAX], front = 0, rear = 0;

    // Initially mark all the vertices as not visited
    // When we push a vertex into the q, we mark it as
    // visited
    bool visited[MAX] = {false};

    // Mark the source node as visited and enqueue it
    visited[s] = true;
    q[rear++] = s;

    // Iterate over the queue
    while (front < rear) {
        // Dequeue a vertex and print it
        int curr = q[front++];
        printf("%d ", curr);

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent has not been visited, mark it visited and enqueue it
        for (int i = 0; i < V; i++) {
            if (adj[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                q[rear++] = i;
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(int adj[MAX][MAX], int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1; // Undirected graph
}

int main() {
    // Number of vertices in the graph
    int V = 5;

    // Adjacency matrix representation of the graph
    int adj[MAX][MAX] = {0};

    // Add edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    // Perform BFS traversal starting from vertex 0
    printf("BFS starting from 0:\n");
    bfs(adj, V, 0);

    return 0;
}

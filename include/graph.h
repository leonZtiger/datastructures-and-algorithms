#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include "malloc.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include <stdbool.h>
#include <float.h> // for FLT_MAX
#include "linkedlist.h"

#define INFINITY FLT_MAX

struct Graph
{
    size_t dim;
    float *matrix; // changed from bool to float
} typedef Graph;

inline size_t xy_to_index(size_t x, size_t y, size_t dim)
{
    return x + y * dim;
}

// Create and return a graph containing n vertices (each vertex is an integer between 1 and n)
Graph createGraph(size_t n)
{
    Graph g;
    g.dim = n;
    g.matrix = (float *)malloc(sizeof(float) * n * n);
    for (size_t i = 0; i < n * n; i++)
    {
        g.matrix[i] = INFINITY; // no connection initially
    }
    return g;
}

// Returns the number of vertices in graph G
size_t getNumVertices(Graph G)
{
    return G.dim;
}

// Returns the total number of edges of graph G
size_t getNumEdges(Graph G)
{
    size_t edge_count = 0;
    for (size_t i = 0; i < G.dim; i++)
    {
        for (size_t j = i + 1; j < G.dim; j++)
        {
            edge_count += (G.matrix[xy_to_index(j, i, G.dim)] != INFINITY) ||
                          (G.matrix[xy_to_index(i, j, G.dim)] != INFINITY);
        }
    }
    return edge_count;
}

// Returns all vertices connected to node v with any edge
void getNeighbors(Graph G, size_t v, size_t **outNeighbors, size_t *outCount)
{
    assert(outNeighbors != NULL);
    (*outNeighbors) = (size_t *)malloc(sizeof(size_t) * G.dim);
    (*outCount) = 0;
    for (size_t i = 0; i < G.dim; i++)
    {
        bool isJoinedFrom = G.matrix[xy_to_index(v, i, G.dim)] != INFINITY;
        bool isJoinedTo = G.matrix[xy_to_index(i, v, G.dim)] != INFINITY;

        if (isJoinedFrom || isJoinedTo)
        {
            (*outNeighbors)[*outCount] = i;
            ++(*outCount);
        }
    }
}

// Returns a list of all vertices v2 connected to node v with an edge (v2, v)
void getInNeighbors(Graph G, size_t v, size_t **outInNeighbors, size_t *outCount)
{
    assert(outInNeighbors != NULL);
    (*outInNeighbors) = (size_t *)malloc(sizeof(size_t) * G.dim);
    (*outCount) = 0;
    for (size_t v2 = 0; v2 < G.dim; v2++)
    {
        bool isJoined = G.matrix[xy_to_index(v2, v, G.dim)] != INFINITY;

        if (isJoined)
        {
            (*outInNeighbors)[*outCount] = v2;
            ++(*outCount);
        }
    }
}

// Returns a list of all vertices v2 connected to node v with an edge (v, v2)
void getOutNeighbors(Graph G, size_t v, size_t **outOutNeighbors, size_t *outCount)
{
    assert(outOutNeighbors != NULL);
    (*outOutNeighbors) = (size_t *)malloc(sizeof(size_t) * G.dim);
    (*outCount) = 0;
    for (size_t v2 = 0; v2 < G.dim; v2++)
    {
        bool isJoined = G.matrix[xy_to_index(v, v2, G.dim)] != INFINITY;

        if (isJoined)
        {
            (*outOutNeighbors)[*outCount] = v2;
            ++(*outCount);
        }
    }
}

// Create a directed edge between two vertices, v1 to v2
void addDirectedEdge(Graph G, size_t v1, size_t v2)
{
    G.matrix[xy_to_index(v1, v2, G.dim)] = 1.0f; // default weight = 1.0
}

// Create an undirected edge between two vertices
void addUndirectedEdge(Graph G, size_t v1, size_t v2)
{
    addDirectedEdge(G, v1, v2);
    addDirectedEdge(G, v2, v1);
}

// Returns true if there is an edge between v1 and v2 and false otherwise
bool hasEdge(Graph G, size_t v1, size_t v2)
{
    bool hasEdgeV1 = G.matrix[xy_to_index(v1, v2, G.dim)] != INFINITY;
    return hasEdgeV1;
}

// Initializes distances and visited arrays
void initialize_single_source(Graph g, size_t start, float *distances, bool *visited) {
    for (size_t i = 0; i < g.dim; i++) {
        distances[i] = INFINITY;
        visited[i] = false;
    }
    distances[start] = 0.0f;
}

// Returns the index of the unvisited vertex with the smallest distance
size_t extract_min_distance_vertex(float *distances, bool *visited, size_t dim) {
    float minDist = INFINITY;
    size_t minIndex = dim;

    for (size_t i = 0; i < dim; i++) {
        if (!visited[i] && distances[i] < minDist) {
            minDist = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Updates the distances of neighbors if a shorter path is found
void relax_neighbors(Graph g, size_t u, float *distances, bool *visited) {
    for (size_t v = 0; v < g.dim; v++) {
        float weight = g.matrix[xy_to_index(u, v, g.dim)];
        if (!visited[v] && weight != INFINITY) {
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }
}

void shortest_path_to_all(Graph g, size_t vert_start, float *distances)
{
   bool *visited = (bool *)malloc(sizeof(bool) * g.dim);
    initialize_single_source(g, vert_start, distances, visited);

    for (size_t i = 0; i < g.dim; i++) {
        size_t u = extract_min_distance_vertex(distances, visited, g.dim);
        if (u == g.dim) break; 
        visited[u] = true;
        relax_neighbors(g, u, distances, visited);
    }

    free(visited);
}

#endif

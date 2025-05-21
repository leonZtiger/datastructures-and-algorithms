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

float shortest_path_to_all(Graph g, size_t v_start, float *distances)
{
    size_t N = g.dim;
    bool *visited = (bool *)calloc(N, sizeof(bool));

    for (size_t i = 0; i < N; i++)
        distances[i] = FLT_MAX;

    distances[v_start] = 0;

    for (size_t i = 0; i < N; i++)
    {
        float minDist = FLT_MAX;
        size_t u = N;

        for (size_t j = 0; j < N; j++)
        {
            if (!visited[j] && distances[j] < minDist)
            {
                minDist = distances[j];
                u = j;
            }
        }

        if (u == N)
            break;
        visited[u] = true;

        for (size_t v = 0; v < N; v++)
        {
            float w = g.matrix[xy_to_index(u, v, N)];
            if (w != FLT_MAX && !visited[v])
            {
                float alt = distances[u] + w;
                if (alt < distances[v])
                    distances[v] = alt;
            }
        }
    }

    float total = 0.0f;
    for (size_t i = 0; i < N; i++)
    {
        if (i != v_start && distances[i] != FLT_MAX)
            total += distances[i];
    }

    free(visited);
    return total;
}

#endif

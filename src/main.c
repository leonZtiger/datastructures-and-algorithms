#include <assert.h>
#include <stdio.h>
#include "graph.h"

void test_create_and_vertex_count()
{
    size_t N = 100;
    Graph g = createGraph(N);
    assert(getNumVertices(g) == N);
    for (size_t i = 0; i < N * N; i++)
    {
        assert(g.matrix[i] == INFINITY);
    }
    free(g.matrix);
    printf("test_create_and_vertex_count passed.\n");
}

void test_add_edges()
{
    const size_t N = 100;
    Graph g = createGraph(N);

    for (size_t i = 0; i < N - 1; i++)
    {
        addDirectedEdge(g, i, i + 1);
    }

    for (size_t i = 0; i < N - 1; i++)
    {
        assert(hasEdge(g, i, i + 1) == true);
        assert(hasEdge(g, i + 1, i) == false);
    }

    assert(getNumEdges(g) == N - 1);

    free(g.matrix);

    g = createGraph(N);

    for (size_t i = 0; i < N - 1; i++)
    {
        addUndirectedEdge(g, i, i + 1);
    }

    for (size_t i = 0; i < N - 1; i++)
    {
        assert(hasEdge(g, i, i + 1) == true);
        assert(hasEdge(g, i + 1, i) == true);
    }

    assert(getNumEdges(g) == N - 1);
    printf("test_add_edges passed.\n");
}

void test_in_out_neighbors()
{
    const size_t N = 100;
    Graph g = createGraph(N);

    for (size_t i = 0; i < N - 1; i++)
    {
        addDirectedEdge(g, i, i + 1);
    }

    // Test out-neighbors
    for (size_t i = 0; i < N; i++)
    {
        size_t *out = NULL;
        size_t count = 0;
        getOutNeighbors(g, i, &out, &count);

        if (i < N - 1)
        {
            assert(count == 1);
            assert(out[0] == i + 1);
        }
        else
        {
            assert(count == 0);
        }
        free(out);
    }

    // Test in-neighbors
    for (size_t i = 0; i < N; i++)
    {
        size_t *in = NULL;
        size_t count = 0;
        getInNeighbors(g, i, &in, &count);

        if (i > 0)
        {
            assert(count == 1);
            assert(in[0] == i - 1);
        }
        else
        {
            assert(count == 0);
        }
        free(in);
    }

    free(g.matrix);
    printf("test_in_out_neighbors passed.\n");
}

void test_undirected_edges()
{
    const size_t N = 5;
    Graph g = createGraph(N);

    for (size_t i = 0; i < N - 1; i++)
    {
        addUndirectedEdge(g, i, i + 1);
    }

    for (size_t i = 0; i < N - 1; i++)
    {
        assert(hasEdge(g, i, i + 1) == true);
        assert(hasEdge(g, i + 1, i) == true);
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (i != j && !(i == j - 1 || i == j + 1))
            {
                assert(hasEdge(g, i, j) == false);
            }
        }
    }

    free(g.matrix);
    printf("test_undirected_edges passed.\n");
}

void test_dijkstras_algo()
{
    // Chatgpt generated code to see the matrix visually, easier to see the connections
    float INF = INFINITY;
    float weights[10][10] = {
        // 0     1     2     3     4     5     6     7     8     9
        {INF, 2.0f, 4.0f, INF, INF, INF, INF, INF, INF, INF},  // 0
        {INF, INF, INF, 1.0f, INF, INF, INF, INF, INF, 15.0f}, // 1
        {INF, INF, INF, 2.0f, INF, INF, INF, INF, INF, INF},   // 2
        {INF, INF, INF, INF, 3.0f, INF, INF, INF, INF, INF},   // 3
        {INF, INF, INF, INF, INF, 2.0f, INF, INF, INF, INF},   // 4
        {INF, INF, INF, INF, INF, INF, 1.0f, INF, INF, INF},   // 5
        {INF, INF, INF, INF, INF, INF, INF, 2.0f, INF, INF},   // 6
        {INF, INF, INF, INF, INF, INF, INF, INF, 1.0f, INF},   // 7
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, 3.0f},   // 8
        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}     // 9
    };
    // =============================================================

    const size_t N = 10;
    Graph g = createGraph(N);
    for (size_t y = 0; y < N; y++)
    {
        for (size_t x = 0; x < N; x++)
        {
            g.matrix[xy_to_index(x, y, g.dim)] = weights[x][y];
        }
    }

    float distances[10];
    float len = shortest_path_to_all(g, 0, distances);

    for (size_t i = 0; i < N; i++) {
        if (distances[i] == FLT_MAX)
            printf("Node 0 to %zu: Unreachable\n", i);
        else
            printf("Node 0 to %zu: %.2f\n", i, distances[i]);
    }

    printf("\n total path length: ");
    printf("%d",len);
    free(g.matrix);

}

int main(int argc, char *argv[])
{
    test_create_and_vertex_count();
    test_add_edges();
    test_in_out_neighbors();
    test_undirected_edges();

    test_dijkstras_algo();

    return 0;
}

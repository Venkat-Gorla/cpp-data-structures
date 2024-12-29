
//----------------------------------------
// - Directed graph cycle detection
// - you will need this skill to solve many graph questions, so let's do it

#include <iostream>
#include <vector>
using namespace std;

// This class is not general purpose, it focuses more on the algorithm rather than
// the inner representation; for simplicity, it uses numbers (0..N-1) for vertices
// and an edge list that represents the neighbors for every vertex.
class DirectedGraph
{
  public:
    DirectedGraph(const int N)
      : m_vertices(N)
      , m_connections(N)
    {
    }

    // for simplicity, no input validation and no dupe handling when adding neighbors
    void addEdge(int source, int dest)
    {
        m_connections[source].push_back(dest);
    }

    bool hasCycle() const;

  private:
    bool hasCycle(int source, vector<bool> & visited, vector<bool> & recStack) const;

  private:
    const int m_vertices;
    vector<vector<int>> m_connections;

    // disable copy ctor
    DirectedGraph(const DirectedGraph &) = delete;
};

bool DirectedGraph::hasCycle() const
{
    vector<bool> visited(m_vertices, false);
    vector<bool> recStack(m_vertices, false);

    for(int source = 0; source < m_vertices; source++)
    {
        if (!visited[source])
            if (hasCycle(source, visited, recStack))
                return true;
    }

    return false;
}

// the idea is to maintain an active list of vertices that are in the recursive call stack
// of DFS; if a vertex is already visited, part of the recursive stack and occurs again, you
// have a cycle
bool DirectedGraph::hasCycle(
    int source, 
    vector<bool> & visited, 
    vector<bool> & recStack) const
{
    visited[source] = true;
    recStack[source] = true;

    for (auto neighbor : m_connections[source])
    {
        if (!visited[neighbor])
        {
            if (hasCycle(neighbor, visited, recStack))
                return true;
        }
        else if (recStack[neighbor])
            return true;
    }

    recStack[source] = false;

    return false;
}
// end DirectedGraph implementation

// fwd declarations
void testHasCycle();
// end fwd declarations

int main(int argc, char *argv[])
{
    {
        testHasCycle();
    }

    return 0;
}

void testHasCycle()
{
    DirectedGraph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 3);
    if (g1.hasCycle())
    {
        cout << "Graph g1 contains cycle\n";
    }

    DirectedGraph g2(1);
    g2.addEdge(0, 0); // self loop from vertex 0 to itself
    if (g2.hasCycle())
    {
        cout << "Graph g2 contains cycle\n";
    }

    // Positive test case
    DirectedGraph g3(4);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(0, 3);
    g3.addEdge(3, 2);
    if (!g3.hasCycle())
    {
        cout << "Graph g3 *does Not* contain cycle\n";
    }
}

/*
Output:
Graph g1 contains cycle
Graph g2 contains cycle
Graph g3 *does Not* contain cycle

*/


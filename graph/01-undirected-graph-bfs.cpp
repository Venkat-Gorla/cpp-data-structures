
//----------------------------------------
// - Undirected graph representation and BFS

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // std::find
using namespace std;

// This class is not general purpose, it focuses more on the algorithm rather than
// the inner representation; for simplicity, it uses numbers (0..N-1) for vertices
// and an edge list that represents the neighbors for every vertex.
class UndirectedGraph
{
  public:
    UndirectedGraph(const int N)
      : m_vertices(N)
      , m_connections(N)
    {
    }

    // for simplicity, no input validation and no dupe handling when
    // adding neighbors
    void addEdge(int source, int dest)
    {
        m_connections[source].push_back(dest);
        m_connections[dest].push_back(source);
    }

    bool isConnected() const;

  private:
    void bfs(int source, vector<bool> & visited) const;

  private:
    const int m_vertices;
    vector<vector<int>> m_connections;

    // disable copy ctor
    UndirectedGraph(const UndirectedGraph &) = delete;
};

bool UndirectedGraph::isConnected() const
{
    vector<bool> visited(m_vertices, false);
    bfs(0, visited);

    auto it = std::find(visited.begin(), visited.end(), false);
    return it == visited.end();
}

void UndirectedGraph::bfs(int source, vector<bool> & visited) const
{
    queue<int> vertexQueue;
    vertexQueue.push(source);
    visited[source] = true;

    while (!vertexQueue.empty())
    {
        int current = vertexQueue.front();
        vertexQueue.pop();

        for (auto neighbor : m_connections[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                vertexQueue.push(neighbor);
            }
        }
    }
}
// end UndirectedGraph implementation

// fwd declarations
void testcase(const UndirectedGraph & g);
// end fwd declarations

int main(int argc, char *argv[])
{
    {
        UndirectedGraph g(4);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 2);
        g.addEdge(2, 2);
        g.addEdge(3, 3); // Disconnected vertex.

        testcase(g);
    }

    {
        UndirectedGraph g1(5);
        g1.addEdge(0, 1);
        g1.addEdge(1, 2);
        g1.addEdge(2, 3);
        g1.addEdge(3, 0);
        g1.addEdge(2, 4);
        g1.addEdge(4, 2);

        testcase(g1);
    }

    return 0;
}

void testcase(const UndirectedGraph & g)
{
    if (g.isConnected())
    {
        cout << "The Graph is Connected" << endl;
    }
    else
    {
        cout << "The Graph is **Not Connected" << endl;
    }
}

/*
Output:
The Graph is **Not Connected
The Graph is Connected

*/


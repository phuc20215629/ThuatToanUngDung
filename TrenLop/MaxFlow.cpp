#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <vector>

using namespace std;

/* Returns true if there is a path from source 's' to sink
't' in residual graph. Also fills parent[] to store the
path */
bool bfs(vector<vector<int>> &rGraph, int s, int t, vector<int> &parent)
{
    int V = rGraph.size();
    // Create a visited array and mark all vertices as not visited
    vector<bool> visited(V, false);

    // Create a queue, enqueue source vertex and mark source vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                // If we find a connection to the sink node, then there is no point in BFS anymore.
                // We just have to set its parent and can return true
                if (v == t)
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // We didn't reach the sink in BFS starting from the source, so return false
    return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int>> &graph, int s, int t)
{
    int V = graph.size();
    // Create a residual graph and fill the residual graph with given capacities in the original graph as
    // residual capacities in residual graph
    vector<vector<int>> rGraph(V, vector<int>(V, 0));
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            rGraph[u][v] = graph[u][v];
        }
    }

    vector<int> parent(V); // This array is filled by BFS and to store the path

    int max_flow = 0;

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find the minimum residual capacity of the edges along the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to the overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N, vector<int>(N, 0));
    int source, target;
    cin >> source >> target;

    for (int i = 0; i < M; i++)
    {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        graph[u - 1][v - 1] = capacity;
    }

    int maxFlowValue = fordFulkerson(graph, source - 1, target - 1);
    cout << maxFlowValue << endl;

    return 0;
}
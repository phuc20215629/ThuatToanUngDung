#include <bits/stdc++.h>
using namespace std;

int V, E;

void BFS(int start, const vector<vector<int>> &adj, vector<bool> &visited)
{

    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (auto v : adj[u])
        {
            if (!visited[v] && v != 0)
            {
                q.push(v);
                visited[v] = true;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> V >> E;

    vector<vector<int>> adj(V + 1, vector<int>(V + 1, 0));
    for (int i = 1; i <= V; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= V; i++)
    {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<bool> visited(V + 1, false);
    for (int i = 1; i <= V; i++)
    {
        if (!visited[i])
            BFS(i, adj, visited);
    }
    return 0;
}
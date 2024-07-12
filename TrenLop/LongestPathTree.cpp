#include <bits/stdc++.h>
using namespace std;

int V;
vector<vector<pair<int, int>>> adj;
vector<bool> visited;
vector<int> d;

void DFS(int p)
{
    visited.clear();
    d.clear();
    visited.resize(V + 1, false);
    d.resize(V + 1, 0);
    stack<int> s;
    s.push(p);
    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        visited[u] = true;
        for (auto v : adj[u])
        {
            if (!visited[v.first] && d[v.first] == 0)
            {
                s.push(v.first);
                d[v.first] = d[u] + v.second;
            }
        }
    }
}

// Idea: First DFS is to find the farthest edge x from a random edge, second DFS is to find the farthest edge y from x
// -> the farthest path is the path from x -> y
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> V;
    adj.resize(V + 1);
    visited.resize(V + 1, false);
    d.resize(V + 1, 0);
    for (int i = 0; i < V; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int x = 1;
    DFS(x);
    for (int i = 1; i <= V; i++)
    {
        if (d[i] > d[x])
        {
            x = i;
        }
    }

    DFS(x);
    for (int i = 1; i <= V; i++)
    {
        if (d[i] > d[x] && i != x)
        {
            x = i;
        }
    }

    cout << d[x] << '\n';
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;

int V;
vector<int> d(MAX, 0);
vector<bool> visited(MAX, false);
vector<vector<pair<int, int>>> adj(MAX);

void DFS(int u)
{
    visited[u] = true;
    for (auto &edge : adj[u])
    {
        int x = edge.first;
        int weight = edge.second;
        if (d[x] == 0 && !visited[x])
        {
            d[x] = d[u] + weight;
            DFS(x);
        }
    }
}

// Idea: First DFS is to find the farthest edge x from a random edge, second DFS is to find the farthest edge y from x
// -> the farthest path is the path from x -> y
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> V;

    for (int i = 0; i < V - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int x = 1, tmp1 = -1;
    DFS(x);

    for (int i = 1; i <= V; i++)
    {
        if (d[i] > tmp1)
        {
            x = i;
            tmp1 = d[i];
        }
    }

    visited.assign(V + 1, false);
    d.assign(V + 1, 0);
    DFS(x);

    int y, tmp2 = -1;
    for (int i = 1; i <= V; i++)
    {
        if (d[i] > tmp2 && i != x)
        {
            y = i;
            tmp2 = d[i];
        }
    }

    cout << d[y] << '\n';

    return 0;
}
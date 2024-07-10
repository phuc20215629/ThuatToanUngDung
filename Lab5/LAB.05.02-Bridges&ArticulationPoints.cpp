#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
int N, M, cur_num = 1, bridges_cnt = 0, artic_point_cnt = 0;
bool isArtic[MAX];
int num[MAX], low[MAX];
vector<vector<int>> adj;

void findBridgesAndArticPoint(int v, int pv)
{
    low[v] = num[v] = cur_num++;
    int children = 0;
    for (auto u : adj[v])
    {
        if (u == pv)
            continue;
        if (num[u] == -1)
        {
            children++;
            findBridgesAndArticPoint(u, v);
            low[v] = min(low[v], low[u]);

            if (low[u] > num[v])
                bridges_cnt++;

            if (low[u] >= num[v] && v != pv)
            {
                isArtic[v] = true;
            }
            if (v == pv && children > 1)
                isArtic[v] = true;
        }
        else
            low[v] = min(low[v], num[u]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    adj.resize(N + 1);
    fill(num, num + N + 1, -1);

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; i++)
        findBridgesAndArticPoint(i, i);

    for (int i = 1; i <= N; i++)
    {
        if (isArtic[i])
            artic_point_cnt++;
    }
    cout << artic_point_cnt << " " << bridges_cnt << "\n";
    return 0;
}
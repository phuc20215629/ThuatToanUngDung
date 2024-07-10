#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
int N, M, cur_num = 1, ans = 0;
bool onstack[MAX] = {false};
int num[MAX], low[MAX];
vector<vector<int>> adj;
stack<int> s;

void scc(int v)
{
    low[v] = num[v] = cur_num++;
    s.push(v);
    onstack[v] = true;
    for (auto u : adj[v])
    {
        if (num[u] == -1)
        {
            scc(u);
            low[v] = min(low[v], low[u]);
        }
        else if (onstack[u])
            low[v] = min(low[v], num[u]);
    }
    if (num[v] == low[v])
    {
        ans++;
        while (1)
        {
            int tmp = s.top();
            s.pop();
            onstack[tmp] = false;
            if (tmp == v)
                break;
        }
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
    }

    for (int i = 1; i <= N; i++)
    {
        if (num[i] == -1)
        {
            scc(i);
        }
    }

    cout << ans << "\n";

    return 0;
}
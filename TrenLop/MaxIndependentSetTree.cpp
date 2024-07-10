#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000001;
vector<int> graph[MAX];
int w[MAX];
int dp[MAX][2];

void dfs(int u, int parent)
{
    dp[u][0] = 0;
    dp[u][1] = w[u];

    for (int v : graph[u])
    {
        if (v != parent)
        {
            dfs(v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]); // u is not chosen
            dp[u][1] += dp[v][0];                // u is chosen
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
    }

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);

    int maxWeight = max(dp[1][0], dp[1][1]);
    cout << maxWeight << endl;

    return 0;
}
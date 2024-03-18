#include <bits/stdc++.h>
using namespace std;

int n, k, sol = INT_MAX, cmin = INT_MAX;
vector<bool> visited;
vector<vector<int>> C;
vector<int> x;
int f = 0;

bool check(int v, int load)
{
    if (visited[v])
        return false;
    if (v > n)
    {
        if (!visited[v - n])
            return false; // to visit city v (v > n), city v - n must be visited before
    }
    else
    {
        if (load + 1 > k)
            return false; // if the bus is already full
    }
    return true;
}

int tryPath(int k, int load)
{
    if (k == 2 * n) // Reached the last city, updateBest
    {
        if (f + C[x[k - 1]][0] < sol)
        {
            sol = f + C[x[k - 1]][0];
        }
        return sol;
    }

    int minCost = INT_MAX;
    for (int v = 1; v <= 2 * n; v++)
    {
        if (check(v, load))
        {
            x[k] = v;
            f += C[x[k - 1]][v];
            visited[v] = true;
            if (v <= n)
                load++;
            else
                load--;

            if (f + cmin * (2 * n + 1 - k) < sol) // Prune unpromising paths
            {
                int cost = tryPath(k + 1, load);
                minCost = min(minCost, cost);
            }

            visited[v] = false;
            if (v <= n)
                load--;
            else
                load++;
            f -= C[x[k - 1]][v];
        }
    }

    return minCost;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    int m = 2 * n + 1;
    C.resize(m, vector<int>(m, 0));
    visited.resize(m, false);
    x.resize(m, 0);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> C[i][j];
            cmin = min(C[i][j], cmin);
        }
    }

    tryPath(1, 0);
    cout << sol << endl;
    return 0;
}
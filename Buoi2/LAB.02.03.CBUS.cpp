#include <bits/stdc++.h>
using namespace std;

int n, k, f = 0, sol = INT_MAX, cmin = INT_MAX;
vector<bool> visited;
vector<vector<int>> C;
vector<int> x;

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

void tryPath(int k, int load)
{
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
            if (k == 2 * n) //updateBest
            {
                if (f + C[v][0] < sol)
                {
                    sol = f + C[v][0];
                }
            }
            else
            {
                if (f + cmin * (2 * n + 1 - k) < sol)
                    tryPath(k + 1, load);
            }

            //Return the status before backtracking
            f -= C[x[k - 1]][v];
            visited[v] = false;
            if (v <= n)
                load--;
            else
                load++;
        }
    }
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
            if(i != j) cmin = min(C[i][j], cmin);
        }
    }

    tryPath(1, 0);
    cout << sol << endl;
    return 0;
}
// C++
#include <bits/stdc++.h>
using namespace std;

int n, k, f = 0, sol = INT_MAX, cmin = INT_MAX;
vector<vector<int>> C;
vector<bool> visited;
vector<int> trace;

bool check(int city, int load)
{
    if (visited[city])
        return false;
    if (city > n) // drop passenger
    {
        if (!visited[city - n]) // to visit city v (v > n), city v - n must be visited before
            return false;
    }
    else // pick up passenger
    {
        if (load + 1 > k) // if the bus is already full
            return false;
    }
    return true;
}

void trySol(int k, int load)
{
    for (int city = 1; city <= 2 * n; city++)
    {
        if (check(city, load))
        {
            trace[k] = city;
            visited[city] = true;
            f += C[trace[k - 1]][city];
            if (city <= n)
                load++;
            else
                load--;

            if (k == 2 * n) // every passenger is picked up and dropped
            {
                if (f + C[city][0] < sol)
                    sol = f + C[city][0];
            }
            else
            {
                if (f + cmin * (2 * n - k + 1) < sol)
                    trySol(k + 1, load);
            }

            // trace[k] = 0;
            visited[city] = false;
            f -= C[trace[k - 1]][city];
            if (city <= n)
                load--;
            else
                load++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    int m = 2 * n + 1;
    C.resize(m, vector<int>(m, 0));
    visited.resize(m, false);
    trace.resize(m, 0);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> C[i][j];
            if (i != j)
                cmin = min(cmin, C[i][j]);
        }
    }

    trySol(1, 0);
    cout << sol << "\n";
    return 0;
}
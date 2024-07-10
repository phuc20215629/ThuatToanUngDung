#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int hungarian(vector<vector<int>> &costMatrix)
{
    int n = costMatrix.size();
    int m = costMatrix[0].size();

    vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, INF);
        vector<bool> used(m + 1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= m; ++j)
            {
                if (!used[j])
                {
                    int cur = costMatrix[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j])
                    {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta)
                    {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= m; ++j)
            {
                if (used[j])
                {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    return -v[0];
}

int main()
{
    int n, m;
    cin >> n >> m;

    // Input the cost matrix
    vector<vector<int>> costMatrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> costMatrix[i][j];
        }
    }

    int maxMatchingCost = hungarian(costMatrix);
    cout << maxMatchingCost << endl;

    return 0;
}
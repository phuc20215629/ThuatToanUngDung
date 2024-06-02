#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> maze(n + 1, vector<int>(m + 1));
    vector<vector<int>> pref(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> maze[i][j];
    }

    for (int i = 0; i <= n; i++)
    {
        maze[i][0] = 0;
        pref[i][0] = 0;
    }
    for (int j = 0; j <= m; j++)
    {
        maze[0][j] = 0;
        pref[0][j] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + maze[i][j];
        }
    }
    int num;
    cin >> num;
    while (num-- != 0)
    {
        int startR, endR, startC, endC;
        cin >> startR >> startC >> endR >> endC;
        cout << pref[endR][endC] - pref[endR][startC - 1] - pref[startR - 1][endC] + pref[startR - 1][startC - 1] << endl;
    }
    return 0;
}

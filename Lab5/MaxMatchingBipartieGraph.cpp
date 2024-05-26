#include <bits/stdc++.h>
using namespace std;

int n, m;

bool findAugmentingPath(int u, const vector<vector<int>> &graph, vector<int> &match, vector<bool> &visited)
{
    for (int v : graph[u])
    {
        if (!visited[v])
        {
            visited[v] = true;
            if (match[v] == -1 || findAugmentingPath(match[v], graph, match, visited))
            {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxMatching(const vector<vector<int>> &taskStaffs)
{
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++)
    {
        for (int staff : taskStaffs[i])
        {
            graph[i].push_back(staff);
        }
    }

    vector<int> match(m + 1, -1);
    int maxTasksAssigned = 0;

    for (int i = 0; i < n; i++)
    {
        vector<bool> visited(m + 1, false);
        if (findAugmentingPath(i, graph, match, visited))
        {
            maxTasksAssigned++;
        }
    }

    return maxTasksAssigned;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    vector<vector<int>> taskStaffs(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        taskStaffs[i].resize(k);
        for (int j = 0; j < k; j++)
        {
            cin >> taskStaffs[i][j];
        }
    }

    cout << maxMatching(taskStaffs) << endl;

    return 0;
}
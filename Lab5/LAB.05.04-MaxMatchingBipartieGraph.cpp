#include <bits/stdc++.h>
using namespace std;

/*
There are  n tasks 1,. . .,n and m staffs 1, . . , m.
T(i) is the set of staffs that can perform the task i (i=1, . . ., n).
Compute an assignment of staffs to tasks such that each task is assigned to at most one staff
and each staff cannot be assigned to more than one task and the number of tasks assigned is maximal.
Input
Line 1: contains 2 positive integer n và m (1 <=  n,m <= 10000)
Line i+1 (i=1, . . .,n) contains a positive integer k and k integer of T(i)
*/

int n, m;

bool findAugmentingPath(int u, const vector<vector<int>> &graph, vector<int> &match, vector<bool> &visited)
{
    for (int v : graph[u])
    {
        if (!visited[v])
        {
            visited[v] = true;
            // if task is already assigned or is assigned to another person -> reassign it
            if (match[v] == -1 || findAugmentingPath(match[v], graph, match, visited))
            {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxMatching(const vector<vector<int>> &staffForTask)
{
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++)
    {
        for (int staff : staffForTask[i])
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

    vector<vector<int>> staffForTask(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        staffForTask[i].resize(k);
        for (int j = 0; j < k; j++)
        {
            cin >> staffForTask[i][j];
        }
    }

    cout << maxMatching(staffForTask) << endl;

    return 0;
}
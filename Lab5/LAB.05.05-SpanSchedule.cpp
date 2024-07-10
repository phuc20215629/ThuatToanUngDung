#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<int> durations(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> durations[i];
    }

    vector<pair<int, int>> constraints(m);
    for (int i = 0; i < m; i++)
    {
        cin >> constraints[i].first >> constraints[i].second;
    }

    // start finding earliest completion time
    vector<int> inDegree(n + 1, 0);       // InDegree of each task
    vector<int> completionTime(n + 1, 0); // Earliest completion time of each task
    vector<vector<int>> adjList(n + 1);   // Adjacency list representation of the graph

    // Build the adjacency list and calculate the inDegree of each task
    for (const auto &constraint : constraints)
    {
        int i = constraint.first;
        int j = constraint.second;
        adjList[i].push_back(j);
        inDegree[j]++;
    }

    queue<int> q;

    // Enqueue tasks with inDegree 0
    for (int i = 1; i <= n; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
            completionTime[i] = durations[i]; // Set the completion time of initial tasks to their duration
        }
    }

    // Perform a topological sort and calculate the earliest completion time for each task
    // Why using topological sort: to calculate the maximum continuos plan of scheduling, ensuring all tasks are completed and no delays appeared
    while (!q.empty())
    {
        int task = q.front();
        q.pop();

        for (int adjTask : adjList[task])
        {
            inDegree[adjTask]--;

            // Update the completion time if a shorter path is found
            completionTime[adjTask] = max(completionTime[adjTask], completionTime[task] + durations[adjTask]);

            if (inDegree[adjTask] == 0)
            {
                q.push(adjTask);
            }
        }
    }

    // Find the maximum completion time among all tasks
    int earliestCompletionTime = 0;
    for (int i = 1; i <= n; i++)
    {
        earliestCompletionTime = max(earliestCompletionTime, completionTime[i]);
    }

    cout << earliestCompletionTime << '\n';
    return 0;
}
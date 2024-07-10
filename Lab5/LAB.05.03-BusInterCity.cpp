#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int n, m;

struct City
{
    int cost;
    int maxCities;
};

// use BFS to find shortest path between 2 cities
void calculateShortestDistances(const vector<City> &cities, vector<vector<int>> &dist)
{
    int n = cities.size();

    for (int u = 0; u < n; u++)
    {
        vector<int> minDist(n, INT_MAX); // min distance between u and i
        vector<bool> visited(n, false);
        minDist[u] = 0;
        visited[u] = true;

        queue<int> q;
        q.push(u);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (int i = 0; i < n; i++)
            {
                if (dist[v][i] > 0 && !visited[i])
                {
                    minDist[i] = minDist[v] + dist[v][i];
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        dist[u] = minDist;
    }
}

int findShortestPath(const vector<City> &cities, const vector<vector<int>> &dist)
{
    int n = cities.size();

    vector<int> minCost(n, INT_MAX); // minCost[i]: min cost to travel to city i (exclude the city i cost)
    minCost[0] = 0;                  // start from city 0

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (mincost[city], city)
    pq.push(make_pair(0, 0));

    while (!pq.empty())
    {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == n - 1)
        {
            return cost;
        }

        if (cost > minCost[u])
        {
            continue;
        }

        for (int v = 0; v < n; v++)
        {
            if (dist[u][v] > 0 && dist[u][v] <= cities[u].maxCities && cost + cities[u].cost < minCost[v])
            {
                minCost[v] = cost + cities[u].cost;
                pq.push(make_pair(minCost[v], v));
            }
        }
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    vector<City> cities(n);
    for (int i = 0; i < n; i++)
    {
        cin >> cities[i].cost >> cities[i].maxCities;
    }

    vector<vector<int>> dist(n, vector<int>(n, 0)); // dist[u][v]: will store the minimum distance between city u and v
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        dist[u - 1][v - 1] = 1;
    }

    calculateShortestDistances(cities, dist);

    cout << findShortestPath(cities, dist) << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
Có n thành phố 1, 2, ..., n. Giữa 2 thành phố i và j có thể có 1 con đường (2 chiều) kết nối giữa chúng.
Mỗi thành phố i có tuyến buýt i với C[i] là giá vé mỗi khi lên xe và D[i] là số thành phố tối đa mà buýt i có thể đi đến trên 1 hành trình đi qua các con đường kết nối.
Hãy tìm cách đi từ thành phố 1 đến thành phố n với số tiền phải trả là ít nhất
Input
Dòng 1: chứa 2 số nguyên dương n và m trong đó n là số thành phố và m là số con đường kết nối các thành phố (1 <= n <= 5000, 1 <= m <= 10000)
Dòng i+1 (i = 1,2,...,n): chứa 2 số nguyên dương C[i] và D[i] (1 <= C[i] <= 10000, 1 <= D[i] <= 100)
Dòng n+1+i (i = 1, 2, ..., m): chứa 2 số nguyên dương i và j trong đó giữa thành phố i và j có con đường kết nối
*/

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

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // (mincost[city], city) in ascending order of cost
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
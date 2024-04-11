#include <bits/stdc++.h>
using namespace std;

unsigned int n;
unsigned int **c, *path, *route, minCost = INT_MAX;

void TSP(int start)
{
    bool visited[n + 1] = {false};
    int cost = 0;

    route = new unsigned int[n + 1];
    route[1] = start;
    visited[start] = true;

    for (int i = 2; i <= n; i++)
    {
        int minCur = INT_MAX;
        int index = 0;
        unsigned int *nextCities = c[route[i - 1]];
        // find path to other city from city route[i - 1] that has the neareast distance
        for (int j = 1; j <= n; j++)
        {
            if (!visited[j] && nextCities[j] < minCur)
            {
                minCur = nextCities[j];
                index = j;
            }
        }

        route[i] = index;
        visited[index] = true;
        cost += minCur;
        if (cost >= minCost)
            return;
    }

    if (cost + c[route[n]][start] < minCost)
    {
        minCost = cost + c[route[n]][start];
        for (int i = 1; i <= n; i++)
        {
            path[i] = route[i];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    c = new unsigned int *[n + 1];
    path = new unsigned int[n + 1];

    for (int i = 1; i <= n; i++)
    {
        c[i] = new unsigned int[n + 1];
        for (int j = 1; j <= n; j++)
        {
            cin >> c[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        TSP(i);
    }

    cout << n << "\n";
    for (int i = 1; i <= n; i++)
    {
        cout << path[i] << " ";
    }

    return 0;
}
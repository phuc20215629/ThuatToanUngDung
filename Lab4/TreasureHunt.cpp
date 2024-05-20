#include <bits/stdc++.h>
using namespace std;

struct City
{
    int x, y;
    long long gold;
};

bool compareCity(const City &t1, const City &t2)
{
    if (t1.x == t2.x)
        return t1.y < t2.y;
    return t1.x < t2.x;
}

int main()
{
    int n;
    cin >> n;

    vector<City> city(n);
    for (int i = 0; i < n; i++)
    {
        cin >> city[i].x >> city[i].y >> city[i].gold;
    }

    // cities are sorted by increasing x and y
    sort(city.begin(), city.end(), compareCity);

    vector<long long> dp(n); // maximum gold mined from city 1 -> i including city i
    dp[0] = city[0].gold;    // start with the city with the lowest location

    for (int i = 1; i < n; i++)
    {
        // find the maximum gold mined from city 1 -> i - 1 including city i - 1 which location is lower than that of city i
        long long maxGold = 0;
        for (int j = 0; j <= i - 1; j++)
        {
            if (city[j].x <= city[i].x && city[j].y <= city[i].y)
            {
                maxGold = max(maxGold, dp[j]);
            }
        }

        dp[i] = maxGold + city[i].gold;
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, dp[i]);

    cout << ans << endl;

    return 0;
}
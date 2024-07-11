#include <bits/stdc++.h>
using namespace std;

/*
Vương quốc này có những kho báu bí ẩn, mỗi kho chứa một lượng vàng khổng lồ ciđược đặt tại các vị trí kỳ diệu có toạ độ (xi, yi).
Những người đi tìm kho báu chỉ có thể bắt đầu hành trình từ (0,0) và theo một quy tắc đặc biệt:
họ chỉ được phép di chuyển theo hướng không giảm của cả hai toạ độ x và y - để tìm đến các kho báu.
Điều này nghĩa là từ kho báu tại (xi, yi), người ta chỉ có thể tiếp tục hành trình đến kho báu (xj, yj) nếu xi ≤ xj và yi ≤ yj.
Kẻ tìm kho báu phải sắp xếp một lộ trình khôn ngoan để thu thập được nhiều vàng nhất.
*/

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
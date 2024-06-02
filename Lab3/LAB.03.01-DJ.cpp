#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> segment;
int n, minBound = INT_MAX, res = 1;

// Consider earlier ending segments first (proved to be optimal)
bool compare(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second < b.second;
}

void tryRes(int upperBound, int k)
{
    if (k == n)
        return;
    if (segment[k].first > upperBound)
    {
        res++;
        // cout << segment[k].first << " " << segment[k].second << endl;
        tryRes(segment[k].second, k + 1);
    }
    else
        tryRes(upperBound, k + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    segment.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> segment[i].first >> segment[i].second;
    }

    sort(segment.begin(), segment.end(), compare);

    tryRes(segment[0].second, 1);
    cout << res;
    return 0;
}
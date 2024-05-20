#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, L1, L2;
    cin >> n >> L1 >> L2;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    vector<int> F(n + 1); // F[i]: maximum gold mined from city 1->i include city i
    deque<int> dq;

    // since minimum hop is L1, cities from 1->L1 are the only ones in F[i]
    for (int i = 1; i <= L1; i++)
    {
        F[i] = a[i];
        dq.push_front(i);
    }

    for (int i = L1 + 1; i <= n; i++)
    {
        // get the city with the highest gold mined end with that city within the range of L1
        while (!dq.empty() && F[dq.front()] <= F[i - L1])
        {
            dq.pop_front();
        }
        dq.push_front(i - L1);

        // only cities in the range from L1 to L2 for each city i are included in the dq
        while (!dq.empty() && dq.back() < i - L2)
        {
            dq.pop_back();
        }

        // F[dq.back()] is the city with the highest gold mined end with that city within the range [L1, L2]
        F[i] = a[i] + F[dq.back()];
    }

    int ans = 0;
    // only look for the last F[i] since the input only consists of positive numbers and the more cities visited the more gold is mined
    for (int i = n - L1 + 1; i <= n; i++)
    {
        ans = max(ans, F[i]);
    }

    cout << ans << '\n';

    return 0;
}
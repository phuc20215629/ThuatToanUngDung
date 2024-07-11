#include <bits/stdc++.h>
using namespace std;

/*
Given a sequence of n integers a=a1,..., an.
A subsequence of a consists of contiguous elements of a (for example, ai, ai+1,... ,aj).
The weight of a subsequence is defined to be the sum of its elements.
A subsequence is called even-subsequnce if its weight is even. Find the even-subsequence of a having largest weight.
*/

const int MAX = 1000005;
long long s0[MAX] = {}; // s0[i] max even weight that ends with a[i]
long long s1[MAX] = {}; // s1[i] max odd weight that ends with a[i]
long long a[MAX] = {};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    s0[1] = -1e10;
    s1[1] = a[1];
    if (a[1] % 2 == 0)
    {
        s0[1] = a[1];
        s1[1] = -1e10;
    }

    for (int i = 2; i <= n; i++)
    {
        if (a[i] % 2 == 0)
        {
            s0[i] = max(s0[i - 1] + a[i], a[i]);
            if (s1[i - 1] == -1e10)
                s1[i] = -1e10;
            else
                s1[i] = s1[i - 1] + a[i];
        }
        else
        {
            s1[i] = max(s0[i - 1] + a[i], a[i]);
            if (s1[i - 1] == -1e10)
                s0[i] = -1e10;
            else
                s0[i] = s1[i - 1] + a[i];
        }
    }

    long long res = 0;
    for (int i = 1; i <= n; i++)
    {
        res = max(res, s0[i]);
    }

    cout << res << '\n';
    return 0;
}
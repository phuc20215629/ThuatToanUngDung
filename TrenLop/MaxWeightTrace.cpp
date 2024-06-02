#include <bits/stdc++.h>
using namespace std;

int n, a[100], mem[100] = {}, mark[100] = {};

int maxW(int k)
{
    if (k == 0)
        return a[k];
    if (mark[k])
        return mem[k];
    int res = max(a[k], maxW(k - 1) + a[k]);
    mark[k] = 1;
    mem[k] = res;
    return res;
}

void trace(int i)
{
    if (i != 0 && mem[i] == mem[i - 1] + a[i])
    {
        trace(i - 1);
        cout << a[i] << " ";
    }
}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    int ans = INT_MIN, pos = 0;
    maxW(n - 1);
    for (int i = 0; i < n; i++)
    {
        if (ans < mem[i])
        {
            ans = mem[i];
            pos = i;
        }
    }

    trace(pos);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

/*
Given a positive integer n and n positive integers a1, a2,..., an.
Compute the number of positive integer solutions to the equation:
    a1X1 + a2X2 + ... + anXn = M
*/

int res = 0;

void findSol(int n, int M, vector<int> &a)
{
    if (n < 0)
    {
        if (M == 0)
            ++res;
        return;
    }

    int x = 1;
    while (x <= M / a[n])
    {
        findSol(n - 1, M - x * a[n], a);
        ++x;
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, M;
    cin >> n >> M;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    findSol(n - 1, M, a);
    cout << res << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// Given a sequence of positive integers a1, a2, ..., an.
// Select the subset of elements such that the sum is maximal and no 2 adjacent elements are selected.

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, a[100010], maxSum[100010];
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    maxSum[0] = a[0];
    maxSum[1] = max(a[0], a[1]);

    for (int i = 2; i < n; i++)
    {
        maxSum[i] = max(maxSum[i - 1], maxSum[i - 2] + a[i]);
    }

    cout << maxSum[n - 1] << "\n";
    return 0;
}
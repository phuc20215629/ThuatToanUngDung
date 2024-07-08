// C++
#include <bits/stdc++.h>
using namespace std;

const int MAX = 100010;
int T, N, C, arr[MAX];

// find the c - 1 elements that satisfy the condition
bool check(int dis)
{
    int count = 1;
    int chosenIndex = 0;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] - arr[chosenIndex] >= dis)
        {
            count++;
            chosenIndex = i;
        }
        if (count == C)
            return true;
    }

    return false;
}

// loop till maximum of distance is reached
int TrySol(int loDis, int hiDis)
{
    int res = 0;
    while (loDis <= hiDis)
    {
        int midDis = (loDis + hiDis) / 2;
        if (check(midDis))
        {
            res = midDis;
            loDis = midDis + 1;
        }
        else
        {
            hiDis = midDis - 1;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T-- != 0)
    {
        cin >> N >> C;
        for (int i = 0; i < N; i++)
            cin >> arr[i];
        sort(arr, arr + N);
        cout << TrySol(0, arr[N - 1] - arr[0]) << "\n";
    }

    return 0;
}
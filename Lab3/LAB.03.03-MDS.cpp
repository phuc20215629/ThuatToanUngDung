#include <bits/stdc++.h>
using namespace std;

// divide to conquer
const int MAX = 100000;
int arr[MAX];
int n, c, res = 0;

bool check(int start, int end, int midDis)
{ // find the c - 1 element
    int count = 1;
    int chosenIndex = start;
    for (int i = start; i <= end; i++)
    {
        if (arr[i] - arr[chosenIndex] >= midDis)
        {
            chosenIndex = i;
            count++;
            if (count == c)
            {
                return true;
            }
        }
    }
    return false;
}

// divide by the distance
void trySub(int start, int end, int loDis, int hiDis)
{
    while (loDis <= hiDis)
    {
        int midDis = (loDis + hiDis) / 2;
        if (check(start, end, midDis))
        {
            res = midDis;
            loDis = midDis + 1;
        }
        else
        {
            hiDis = midDis - 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;

    while (t-- != 0)
    {
        cin >> n >> c;

        for (int i = 0; i < n; i++)
            cin >> arr[i];
        sort(arr, arr + n);
        trySub(0, n - 1, 0, arr[n - 1] - arr[0]);
        cout << res << "\n";
    }
}
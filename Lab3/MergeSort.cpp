#include <bits/stdc++.h>
using namespace std;

int arr[100], tmp[100];

void merge(int l, int m, int r)
{
    int i = l, k = l, j = m + 1;

    while (i <= m && j <= r)
    {
        if (arr[i] <= arr[j])
        {
            tmp[k] = arr[i];
            ++i;
        }
        else
        {
            tmp[k] = arr[j];
            ++j;
        }
        ++k;
    }

    while (i <= m)
    {
        tmp[k] = arr[i];
        ++i;
        ++k;
    }

    while (j <= r)
    {
        tmp[k] = arr[j];
        ++j;
        ++k;
    }

    for (int p = l; p <= r; p++)
    {
        arr[p] = tmp[p];
    }
}

void mergeSort(int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    mergeSort(0, n - 1);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
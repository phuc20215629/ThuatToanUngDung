#include <bits/stdc++.h>
using namespace std;

int n, m, sum = 0, sol;
int a[10000];

bool isPossible(int mid)
{
    int subSum = 0, segs = 1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > mid)
            return false;
        if (subSum + a[i] > mid)
        {
            segs++;
            // chi can check so doan chia co > m hay khong,
            // con neu nho hon m thi luon co the chia nho them cac doan da chia de thu duoc dung m doan nhu yeu cau
            if (segs > m)
                return false;
            subSum = a[i];
        }
        else
        {
            subSum += a[i];
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    int start = a[n - 1], end = sum;
    // tuong tu nhu tim kiem nhi phan nhung doi voi trong so cua doan
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (isPossible(mid)) // tim duoc 1 cach thi giam end di cho toi khi tim duoc min trong so
        {
            sol = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    cout << sol << "\n";
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int N, T, D, a[1001], t[1001], goodsPickedUp[1001][101], maxGoodsPickedUp = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> T >> D;
    for (int i = 1; i <= N; i++)
        cin >> a[i];
    for (int i = 1; i <= N; i++)
        cin >> t[i];

    for (int i = 1; i <= N; i++)
    {
        int farthestDest = max(0, i - D);
        for (int j = 1; j <= T; j++)
        {
            for (int k = farthestDest; k < i; k++)
            {
                if (t[i] <= j)
                {
                    goodsPickedUp[i][j] = max(goodsPickedUp[k][j - t[i]] + a[i], goodsPickedUp[i][j]);
                }
            }
            maxGoodsPickedUp = max(maxGoodsPickedUp, goodsPickedUp[i][j]);
        }
    }

    cout << maxGoodsPickedUp << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int N, T, D, a[1001], t[1001], maxGoodsPickedUp = 0;
int goodsPickedUp[1001][101]; // goodsPickedUp[i][j]: max goods picked up in time j that ends at city i

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

    // for (int i = 1; i <= N; i++)
    // {
    //     goodsPickedUp[i][t[i]] = a[i];
    // }

    for (int i = 1; i <= N; i++) // loop for all stations
    {
        int farthestDest = max(0, i - D); // farthest destination that can be reached from station i
        for (int j = 1; j <= T; j++)      // loop for all time duration possible for different combinations of routes
        {
            for (int k = farthestDest; k < i; k++) // loop for all stations satisfy the condition D
            {
                if (t[i] <= j) // if the current time duration is enough to pick up goods at station i
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
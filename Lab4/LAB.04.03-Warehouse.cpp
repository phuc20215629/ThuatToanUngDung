#include <bits/stdc++.h>
using namespace std;

/*
A truck is planned to arrive at some stations among N stations 1, 2, . . ., N located on a line.
Station i (i = 1,…,N) has coordinate i and has following information
ai: amount of goods
ti: pickup time duration for taking goods
The route of the truck is a sequence of stations x1 < x2 < . . . < xk (1 ≤ xj ≤ N, j = 1,…, k).
Due to technical constraints, the distance between two consecutive stations that the truck arrives xi and xi+1 is less than or equal to D
and the total pickup time duration cannot exceed T. Find a route for the truck such that total amount of goods picked up is maximal.
*/

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
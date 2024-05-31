#include <bits/stdc++.h>
using namespace std;

int H, W, n, sol = 0;
int h[15], w[15];
int marked[30][30];

bool check(int wk, int hk, int x, int y)
{
    // if (wk + x > W || hk + y > H) // if that rect is out of range
    //     return false;

    for (int i = x; i < x + wk; i++) // check for overlapping rect
    {
        for (int j = y; j < y + hk; j++)
        {
            if (marked[i][j])
                return false;
        }
    }

    return true;
}

void mark(int wk, int hk, int x, int y, bool markVal)
{
    for (int i = x; i < x + wk; i++)
    {
        for (int j = y; j < y + hk; j++)
        {
            marked[i][j] = markVal;
        }
    }
}

void trySol(int k)
{
    if (sol == 1)
        return; // no need for further backtracking since we only need to know if it is possible to cut into n pieces or not

    for (int rotate = 0; rotate <= 1; rotate++)
    {
        int wk = w[k], hk = h[k];
        if (rotate == 1)
        { // rotate 90°
            wk = h[k];
            hk = w[k];
        }
        for (int x = 0; x <= W - wk; x++)
        {
            for (int y = 0; y <= H - hk; y++)
            {
                if (check(wk, hk, x, y))
                {
                    mark(wk, hk, x, y, true); // mark all the unit inside the rect to avoid overlapping

                    if (k == n - 1)
                    {
                        sol = 1;
                        return;
                    }
                    else
                        trySol(k + 1);

                    mark(wk, hk, x, y, false); // unmark for backtracking
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> H >> W;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> h[i] >> w[i];
    }

    trySol(0);

    cout << sol;
    return 0;
}
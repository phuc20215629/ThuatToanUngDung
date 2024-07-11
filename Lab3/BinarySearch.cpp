#include <bits/stdc++.h>
using namespace std;

/*Find square root of x with EPS approximately*/

int main()
{
    double x = 9.2;
    double EPS = 1e-10, lo = -1000, hi = 1000;
    while (hi - lo >= EPS)
    {
        double mid = (lo + hi) / 2;
        // cout << mid << "\n";
        if (mid * mid > x)
        {
            hi = mid;
        }
        else
        {
            lo = mid;
        }
    }
    cout << lo;
    return 0;
}
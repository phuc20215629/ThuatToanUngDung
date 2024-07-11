#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

struct Point
{
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

Point points[N];
int n, k;
vector<Point> C;
Point O; // goc

long long dist2(const Point &A, const Point &B)
{
    long long x = A.x - B.x;
    long long y = A.y - B.y;
    return (long long)x * x + (long long)y * y;
}

long long cross_product(const Point &O, const Point &A, const Point &B)
{
    long long xa = A.x - O.x;
    long long ya = A.y - O.y;
    long long xb = B.x - O.x;
    long long yb = B.y - O.y;
    return (long long)xa * yb - (long long)xb * ya;
}

bool cmp(const Point &A, const Point &B)
{
    long long cp = cross_product(O, A, B);
    return cp == 0 ? dist2(O, A) < dist2(O, B) : cp > 0;
}

int ccw(const Point &A, const Point &B, const Point &C)
{
    long long cp = cross_product(A, B, C);
    return cp == 0 ? 0 : (cp < 0 ? -1 : 1);
}

void compute_convex_hull(Point *P)
{
    C.clear();

    // update goc la diem thap nhat
    int k = 0;
    for (int i = 1; i < n; i++)
    {
        if (P[i].y < P[k].y || (P[i].y == P[k].y && P[i].x < P[k].x))
            k = i;
    }
    swap(P[0], P[k]);
    O = P[0];

    sort(P + 1, P + n, cmp);
    C.push_back(P[0]);
    C.push_back(P[1]);
    for (int i = 2; i < n; i++)
    {
        while (C.size() >= 2 && ccw(C[C.size() - 2], C[C.size() - 1], P[i]) <= 0)
            C.pop_back();
        C.push_back(P[i]);
    }
}

bool same_side(const Point &A, const Point &B, const Point &C, const Point &D)
{
    int sc = ccw(A, B, C);
    int sd = ccw(A, B, D);
    return sc * sd >= 0;
}

int check_in_convex_hull(const Point &T)
{
    for (const auto &p : C)
    {
        if (p.x == T.x && p.y == T.y)
            return 1;
    }

    int last = C.size() - 1;
    if (same_side(C[0], C[1], C[last], T) && same_side(C[0], C[last], C[1], T))
    {
        int l = 1, r = C.size() - 1;
        while (r - l > 1)
        {
            int m = (l + r) / 2;
            if (same_side(C[0], C[m], C[last], T))
                l = m;
            else
                r = m;
        }
        if (!same_side(C[l], C[r], C[0], T))
            return 0;
        else
            return 1;
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    compute_convex_hull(points);
    // check if Pi form a convex hull
    int res = 1;
    if (C.size() != n)
        res = 0;

    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int x, y, isInside = 0;
        cin >> x >> y;
        Point T(x, y);
        if (res == 1)
            isInside = check_in_convex_hull(T);
        cout << isInside << "\n";
    }

    return 0;
}
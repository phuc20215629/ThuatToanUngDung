#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

struct Point
{
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

Point P[N];
int n;
vector<Point> C;

// binh phuong khoanc cach AB
long long dist2(const Point &a, const Point &b)
{
    long long x = a.x - b.x;
    long long y = a.y - b.y;
    return (long long)x * x + (long long)y * y;
}

// tich vo huong OA x OB
long long cross_product(const Point &O, const Point &A, const Point &B)
{
    long long xa = A.x - O.x;
    long long ya = A.y - O.y;
    long long xb = B.x - O.x;
    long long yb = B.y - O.y;
    return (long long)xa * yb - (long long)ya * xb;
}

// sap xep P theo chieu kim dong ho theo thu tu giam dan cua OA x OB
bool cmp(const Point &A, const Point &B)
{
    long long cp = cross_product(P[0], A, B);
    return cp == 0 ? dist2(P[0], A) < dist2(P[0], B) : cp > 0;
}

// tinh chieu quay OA den OB (= 0 : OA x OB = 0, = 1 : OA x OB > 0, = -1 : OA x OB < 0)
int ccw(const Point &A, const Point &B, const Point &C)
{
    long long cp = cross_product(A, B, C);
    return cp == 0 ? 0 : (cp < 0 ? -1 : 1);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> P[i].x >> P[i].y;
    }

    // let P[0] be the lowest point
    int k = 0;
    for (int i = 1; i < n; i++)
    {
        if (P[i].y < P[k].y || (P[i].y == P[k].y && P[i].x < P[k].x))
            k = i;
    }
    swap(P[0], P[k]);

    sort(P + 1, P + n, cmp);

    C.push_back(P[0]);
    C.push_back(P[1]);
    for (int i = 2; i < n; i++)
    {
        while (C.size() >= 2 && ccw(C[C.size() - 2], C[C.size() - 1], P[i]) <= 0)
            C.pop_back();
        C.push_back(P[i]);
    }

    int m = C.size();
    cout << m << '\n';
    for (int i = 0; i < m; i++)
    {
        cout << C[i].x << ' ' << C[i].y << '\n';
    }
}
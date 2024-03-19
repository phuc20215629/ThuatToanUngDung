#include<bits/stdc++.h>
using namespace std;

int res = 0;

void findSol(int n, int M, vector<int> &a) {
    if (n < 0) {
        if (M == 0) ++res;
        return;
    }

    int i = 1;
    while (i <= M / a[n]) {
        findSol(n - 1, M - i * a[n], a);
        ++i;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, M;
    cin >> n >> M;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    findSol(n - 1, M, a);
    cout << res << endl;
    return 0;
}
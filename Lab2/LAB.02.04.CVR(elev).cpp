#include<bits/stdc++.h>
using namespace std;

int n, K, Q, sol = INT_MAX, cmin = INT_MAX, sum = 0;
int dd[100], st[100];
int x[100], load[100], d[100], c[100][100];

void Try(int u, int v) {
    for(int i = 1; i <= n; i++) {
        if(!dd[i]) {
            int j = v;
            if(load[j] + d[i] <= Q) {
                if(u == 1) st[j] = i;
                dd[i] = 1;
                x[u] = i;
                sum += c[x[u - 1]][i];
                load[j] += d[i];
                if(u == n) {
                    sol = min(sol, sum + c[x[u]][0]);
                } else {
                    if(sum + cmin * (n - u + 1) < sol) Try(u + 1, j);
                }

                dd[i] = 0;
                sum -= c[x[u - 1]][i];
                load[j] -= d[i];
            }

            j++;
            if(j <= K) {
                if(load[j] + d[i] <= Q && i > st[j - 1]) {
                    st[j] = i;
                    dd[i] = 1;
                    x[u] = i;
                    sum += c[x[u - 1]][0] + c[0][i];
                    load[j] += d[i];
                    if(u == n) {
                        sol = min(sol, sum + c[x[u]][0]);
                    } else {
                        if(sum + cmin * (n - u + 1) < sol) Try(u + 1, j);
                    }

                    dd[i] = 0;
                    sum -= c[x[u - 1]][0] + c[0][i];
                    load[j] -= d[i];
                }
            }
        }
    }
}




int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> K >> Q; //(2≤n≤12,1≤K≤5,1≤Q≤50)
    
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            cin >> c[i][j];
            if(i != j && cmin > c[i][j]) cmin = c[i][j];
        }
    }

    Try(1, 1);

    cout << sol;
    return 0;
}
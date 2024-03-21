//C++ 
#include <bits/stdc++.h> 
using namespace std;

int n, K, load = 0, currL = 0, sol = INT_MAX, cmin = INT_MAX;
int c[25][25] = { 0 }, curr[25] = { 0 };
bool visited[25] = { false };

bool check(int i) {
    if(visited[i]) return false;
    if(i > n) {
        if(!visited[i - n]) return false; 
    }
    else {
        if(load == K) return false;
    }
    
    return true;
}

void tryRoute(int k) {
    for(int i = 1; i <= 2 * n; i++) {
        if(check(i)) {
            curr[k] = i;
            visited[i] = true;
            currL += c[curr[k - 1]][i];
            if(i <= n) load++;
            else load--;
            
            if(k == 2 * n) {
                if(sol > currL + c[i][0]) sol = currL + c[i][0];
            }
            else {
                if(currL + cmin*(2*n - k + 1) < sol) tryRoute(k + 1); 
            }
            
            visited[i] = false;
            currL -= c[curr[k - 1]][i];
            if(i <= n) load--;
            else load++;
        }
    }
}

int main() 
{ 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> K;
    
    for(int i = 0; i <= 2*n; i++) {
        for(int j = 0; j <= 2*n; j++) {
            cin >> c[i][j];
            if(i != j) cmin = min(cmin, c[i][j]);
        }
    }
    
    tryRoute(1);
    cout << sol;
}
#include<bits/stdc++.h>
using namespace std;

int n, K, Q, sol = INT_MAX, cmin = INT_MAX, f = 0, segments = 0, nbR = 0;
int y[10], x[15], load[10], d[15], c[15][15];
bool visited[15] = { false };

bool checkX(int v, int k) {
    if(v == 0) return true;
    if(v > 0 && visited[v]) return  false;
    if(load[k] + d[v] > Q) return false;

    return true;
}

void tryX(int s, int k) { // trying deliver points for x[s]
    if(s == 0) {
        if(k < K) tryX(y[k + 1], k + 1); // if truck k isn't assigned -> move on to find routes for truck k + 1
        return;
    }

    for(int v = 0; v <= n; v++) { // v == 0 ending a route
        if(checkX(v, k)) {
            x[s] = v;
            visited[v] = true;
            f += c[s][v];
            load[k] += d[v];
            segments++;
            
            if(v > 0) {
                if(f + cmin*(n + nbR - segments) < sol) tryX(v, k); // lower bound: if the min cost to deliver the rest requests is lower 
            }                                                // than the current solution -> try next delivery point for the same truck k
            else { // v == 0 truck has reached the end point
                if(k == K) { // all truck has been assigned a route
                    if(segments == n + nbR) { // all delivery points are reached
                        if(sol > f) sol = f;
                    }
                }
                else { // k < K
                    if(f + cmin*(n + nbR - segments) < sol) tryX(y[k + 1], k + 1); // lower bound: if the min cost to deliver the rest 
                                                                                // requests is lower than the current solution ->
                }               // try finding a route for next truck, starting from it's starting delivery point found from from tryY(k)
            }

            visited[v] = false;
            f -= c[s][v];
            load[k] -= d[v];
            segments--;
        }
    }
}

bool checkY(int v, int k) {
    if(v == 0) return true; // truck k is requested for the first time

    if(load[k] + d[v] > Q) return false; // if the upcoming request overload the capacity of truck k

    if(visited[v]) return false; // if v is visited before (each client is only visited by 1 route)
    
    return true;
}

void tryY(int k) { // trying first deliver point for each truck k 
    int s = 0; // starting point
    if(y[k - 1] > 0) s = y[k - 1] + 1; // if truck (k - 1) is assigned a road (assume: y[k] >= y[k - 1])

    for(int v = s; v <= n; v++) {
        if(checkY(v, k)) {
            y[k] = v;
            if(v > 0) { // deliver to client
                segments++; // route traveled of k trucks
                visited[v] = true;
                f += c[0][v];
                load[k] += d[v];
            }
            if(k < K) {
                tryY(k + 1);
            } else { // if k == K
                nbR = segments; // number of trucks assigned = number of routes from start to the first deliver point of each truck
                tryX(y[1], 1); // trying routes for assigned trucks
            }

            if(v > 0) {
                segments--;
                visited[v] = false;
                f -= c[0][v];
                load[k] -= d[v];
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

    tryY(1);

    cout << sol;
    return 0;
}
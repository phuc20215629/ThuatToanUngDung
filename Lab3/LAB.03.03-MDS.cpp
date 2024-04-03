#include<bits/stdc++.h>
using namespace std;

// giam de tri

const int MAX = 100000;
int arr[MAX];
int n, c, res = 0;

bool check(int start, int end, int mid) { // find the c - 1 element 
    int count = 1;
    int j = start;
    for(int i = start; i <= end; i++) {
        if(arr[i] - arr[j] >= mid) {
            j = i;
            count++;
            if(count == c) {
                return true;
            }
        }
    }
    return false;
}

void trySub(int start, int end, int lo, int hi) {
    while(lo <= hi) {        
        int mid = (lo + hi) / 2;
        if(check(start, end, mid)) {
            res = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;

    while(t-- != 0) {
        cin >> n >> c;
        
        for(int i = 0; i < n; i++) cin >> arr[i];
        sort(arr, arr + n);
        trySub(0, n - 1, 0, arr[n - 1] - arr[0]);
        cout << res << "\n";
    }
}
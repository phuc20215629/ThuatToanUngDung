#include<bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int res = -1, sum = 0, left = 0;
    for(int right = 0; right < n; right++) {
        sum += arr[right];
        while(sum > q) {
            sum -= arr[left];
            left++;
        }
        res = max(res, right - left + 1);
    }
    cout << res;
    return 0;
}
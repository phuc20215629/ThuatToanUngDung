#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    int left = 0, right = n - 1;
    int res = 0;
    while(left != right) {
        if(arr[left] + arr[right] == m) {
            res++;
            left++;
            right--;
        } else if(arr[left] + arr[right] < m) left++;
        else right--;
    }
    cout << res;
    return 0;
}
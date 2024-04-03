#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> arr;
int n, minBound = INT_MAX, res = 1;

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

void tryRes(int upperBound, int k) {
    if(k > n - 1) return;
    if (arr[k].first > upperBound) {
        res++;
        // cout << arr[k].first << " " << arr[k].second << endl;
        tryRes(arr[k].second, k + 1);
    }
    else tryRes(upperBound, k + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    sort(arr.begin(), arr.end(), compare);

    tryRes(arr[0].second, 1);
    cout << res;
    return 0;
}
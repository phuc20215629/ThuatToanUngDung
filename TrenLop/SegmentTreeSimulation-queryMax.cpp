#include<bits/stdc++.h>
using namespace std;

void preprocessing(vector<int>&maxVal, const vector<int>& arr, int l, int r, int id) {
    if(l == r) {
        maxVal[id] = arr[l];
        return;
    }

    int m = (l + r) / 2;
    preprocessing(maxVal, arr, l, m, id * 2);
    preprocessing(maxVal, arr, m + 1, r, id * 2 + 1);
    maxVal[id] = max(maxVal[id * 2], maxVal[id * 2 + 1]);
}

int getMaxFromNode(const vector<int>& maxVal, int id, int l, int r, int i, int j) {
    if(i > r || j < l) return INT_MIN;
    if(i <= l && j >= r) {
        return maxVal[id];
    }

    int m = (l + r) / 2;
    int maxLeft = getMaxFromNode(maxVal, 2 * id, l, m, i, j);
    int maxRight = getMaxFromNode(maxVal, 2 * id + 1, m + 1, r, i, j);
    return max(maxLeft, maxRight);
}

void updateFromNode(vector<int>& maxVal, int id, int l, int r, int index, int value) {
    if(l > r) return;
    if(index < l || index > r) return;
    if(l == r) {
        maxVal[id] = value;
        return;
    }
    
    int m = (l + r) / 2;
    updateFromNode(maxVal, id * 2, l, m, index, value);
    updateFromNode(maxVal, id * 2 + 1, m + 1, r, index, value);
    maxVal[id] = max(maxVal[id * 2], maxVal[id * 2 + 1]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; 
    cin >> n;
    vector<int> arr(n + 1);
    vector<int> maxVal(4 * n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    preprocessing(maxVal, arr, 1, n, 1);
    int query;
    cin >> query;
    while(query-- != 0) {
        string order;
        cin >> order;
        int i, j;
        cin >> i >> j;
        if(order == "get-max") {
            cout << getMaxFromNode(maxVal, 1, 1, n, i, j) << endl;
        }
        else updateFromNode(maxVal, 1, 1, n, i, j);
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n; 
    cin >> n;
    vector<int> arr(n);
    vector<int> pref(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    pref[0] = arr[0];
    for(int i = 1; i < n; i++) {
        pref[i] = pref[i-1] + arr[i];
    }
    int num; 
    cin >> num;
    while(num-- != 0) {
        int startIdx, endIdx;
        cin >> startIdx >> endIdx;
        if(startIdx == 1) cout << pref[endIdx-1] << endl;
        else cout << pref[endIdx-1] - pref[startIdx-2] << endl;
    }
    return 0;
}
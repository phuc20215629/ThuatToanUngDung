#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
int arr[1000000], temp[1000000];

long long mergeAndCount(int left, int mid, int right) {
    int i = left;       // Pointer for left subarray
    int j = mid + 1;    // Pointer for right subarray
    int k = left;       // Pointer for merged array
    long long inversionCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
            inversionCount += mid - i + 1; // Increment inversion count
        }
        k++;
    }

    // Copy the remaining elements of the left subarray, if any
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of the right subarray, if any
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // Copy the merged elements back to the original array
    for (int x = left; x <= right; x++) {
        arr[x] = temp[x];
    }

    return inversionCount;
}

long long mergeSortAndCount(int l, int r) {
    long long inversionCount = 0;
    if(l < r) {
        int mid = (l + r) / 2;

        inversionCount = (inversionCount + mergeSortAndCount(l, mid)) % MOD;
        inversionCount = (inversionCount + mergeSortAndCount(mid + 1, r)) % MOD;
        inversionCount = (inversionCount + mergeAndCount(l, mid, r)) % MOD;
    } 

    return inversionCount;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << mergeSortAndCount(0, n - 1) << endl;

    return 0;
}
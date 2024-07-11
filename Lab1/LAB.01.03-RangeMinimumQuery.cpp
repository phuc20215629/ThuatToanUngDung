#include <bits/stdc++.h>
using namespace std;

/*
Given a sequence of n integers a,...,an-1.
We denote rmq(i,j) the minimum element of the sequence i, ai+1,...,aj. Given m pairs (i1,j1),. . .,(im,jm),
compute the sum Q = rmq(i1,j1) + ... + rmq(im,jm)
*/

const int MAXN = 10000000;
int arr[MAXN], segmentTree[MAXN];

// https://www.youtube.com/watch?v=DpSYj7t1sbQ
// Building Segment Tree
void buildSegmentTree(int low, int high, int pos)
{
    if (low == high)
    {
        segmentTree[pos] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    buildSegmentTree(low, mid, 2 * pos + 1);      // 2 * pos + 1 is left child
    buildSegmentTree(mid + 1, high, 2 * pos + 2); // 2 * pos + 2 is right child

    // return with the minimum value of the 2 leaves
    segmentTree[pos] = min(segmentTree[2 * pos + 1], segmentTree[2 * pos + 2]);
}

void updateTree(int pos, int low, int high, int index, int value)
{
    if (low > high)
        return;
    if (index < low || index > high)
        return;
    if (low == high)
    {
        segmentTree[pos] = value;
        return;
    }
    int mid = (low + high) / 2;
    updateTree(2 * pos + 1, low, mid, index, value);
    updateTree(2 * pos + 2, mid + 1, high, index, value);
    segmentTree[pos] = min(segmentTree[2 * pos + 1], segmentTree[2 * pos + 2]);
}

// Find rmq in range [qlow, qhigh]
int RMQ(int low, int high, int qlow, int qhigh, int pos)
{
    // No overlap -> no further search
    if (qlow > high || qhigh < low)
        return INT_MAX;

    // Total overlap -> return right away since it is already the minimum value in range [low, high]
    if (qlow <= low && qhigh >= high)
        return segmentTree[pos];

    // Partial overlap -> divide into smaller segments to continue searching
    int mid = (low + high) / 2;
    int left = RMQ(low, mid, qlow, qhigh, 2 * pos + 1);
    int right = RMQ(mid + 1, high, qlow, qhigh, 2 * pos + 2);

    // compare 2 side of the segment tree (left, right) to find the answer
    return min(left, right);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Building Segment Tree with size of 2 * n - 1 but start from 0
    buildSegmentTree(0, n - 1, 0);

    // Update segment tree
    // int index, value;
    // cin >> index >> value;

    // n = n + 1;
    // vector<int> segmentTree(2 * n - 1);
    // buildSegmentTree(0, n - 2, 0);
    // updateTree(arr, segmentTree, 0, 0, n - 1, index, value);

    int m;
    cin >> m;

    int totalRmq = 0;
    while (m-- != 0)
    {
        int start, end;
        cin >> start >> end;

        int rmq = RMQ(0, n - 1, start, end, 0);
        totalRmq += rmq;
    }

    cout << totalRmq << endl;

    return 0;
}

/*
 #include <bits/stdc++.h>
 using namespace std;

//Idea sparse table
 int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
     int n;
     cin >> n;
     vector<int> a(n);
     for (int i = 0; i < n; i++) {
         cin >> a[i];
     }

     int logn = log2(n) + 1;
     vector<vector<int>> sparseTable(n, vector<int>(logn));

     for (int i = 0; i < n; i++) {
         sparseTable[i][0] = a[i];
     }

     for (int j = 1; j < logn; j++) {
         for (int i = 0; i + (1 << j) <= n; i++) {
             sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
         }
     }

     int q;
     cin >> q;
     int res = 0;
     while (q--) {
         int l, r;
         cin >> l >> r;
         int k = log2(r - l + 1);   //highest power of 2 that is smaller or equal to the count of numbers in the range
         int minimum = min(sparseTable[l][k], sparseTable[r - (1 << k) + 1][k]);
         res += minimum;
     }
     cout << res;

     return 0;
 }
 */

/*
#include<bits/stdc++.h>
using namespace std;

//RMQ in slide file:///C:/Users/hanoi/OneDrive%20-%20Hanoi%20University%20of%20Science%20and%20Technology/Hust/2023.2/Thu%E1%BA%ADt%20to%C3%A1n%20%E1%BB%A9ng%20d%E1%BB%A5ng/Slide/week3-chap2-advanced-data-structures.pdf
void preprocessing(const vector<int>& arr, vector<vector<int>>& M, int n) {
    for(int j = 0; j < n; j++) M[0][j] = j;

    for(int j = 1; (1 << j) < n; j++) {
        for(int i = 0; i + (1 << j) - 1 < n; i++) {
            if(arr[M[j - 1][i]] < arr[M[j - 1][i + (1 << (j - 1))]]) {
                M[j][i] = M[j - 1][i];
            } else M[j][i] = M[j - 1][i + (1 << (j - 1))];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<vector<int>> M(ceil(log2(n + 1)), vector<int>(n));
    preprocessing(arr, M, n);

    int RMQ;
    cin >> RMQ;
    int res = 0;
    while(RMQ-- != 0) {
        int i, j;
        cin >> i >> j;
        int k = log2(j - i + 1);
        if(arr[M[k][i]] < arr[M[k][j - (1 << k) + 1]]) res += arr[M[k][i]];
        else res += arr[M[k][j - (1 << k) + 1]];
    }
    cout << res;
    return 0;
}*/
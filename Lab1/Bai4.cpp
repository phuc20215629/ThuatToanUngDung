#include <bits/stdc++.h>
using namespace std;

//Idea Largest Rectangular Area in a Histogram using Stack
int n, m;

int maxS(const vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int n = heights.size();
    int i = 0;

    while (i < n) {
        if (s.empty() || heights[i] >= heights[s.top()]) {
            s.push(i);
            i++;
        } else {
            int tp = s.top();
            s.pop();
            int area = heights[tp] * (s.empty() ? i : (i - s.top() - 1));
            maxArea = max(maxArea, area);
        }
    }

    while (!s.empty()) {
        int tmp = s.top();
        s.pop();
        int area;
        if(s.empty()) area = heights[tmp] *  i;
        else area = heights[tmp] * (i - s.top() - 1);
        maxArea = max(maxArea, area);
    }

    return maxArea;
}

int maximalRectangle(const vector<vector<int>>& matrix) {
    vector<int> heights(n, 0);
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                heights[j] = 0;
            } else {
                heights[j] += matrix[i][j];
            }
        }

        maxArea = max(maxArea, maxS(heights));
    }

    return maxArea;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;

    vector<vector<int>> rec(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> rec[i][j];
        }
    }

    cout << maximalRectangle(rec) << endl;

    return 0;
}
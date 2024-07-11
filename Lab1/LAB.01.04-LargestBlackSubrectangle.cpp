#include <bits/stdc++.h>
using namespace std;

/*
Một hình chữ nhật kích thước n x m được chia thành các ô vuông con 1 x 1 với 2 màu đen hoặc trắng.
Hình chữ nhật được biểu diễn bởi ma trận A(n x m) trong đó A(i, j) = 1 có nghĩa ô hàng i, cột j là ô đen
và A(i, j) = 0 có nghĩa ô vuông hàng i cột j là ô trắng.
Hãy xác định hình chữ nhật con của bảng đã cho bao gồm toàn ô đen và có diện tích lớn nhất.
*/

// Idea Largest Rectangular Area in a Histogram using Stack
int n, m;

int maxS(const vector<int> &heights)
{
    int n = heights.size();
    vector<int> left(n), right(n);

    stack<int> s;

    // find the smallest-nearest rectangle to the left of heights[i]
    for (int i = 0; i < n; i++)
    {
        if (s.empty())
        {
            left[i] = 0;
            s.push(i);
        }
        else
        {
            while (!s.empty() && heights[s.top()] >= heights[i])
                s.pop();
            left[i] = s.empty() ? 0 : s.top() + 1;
            s.push(i);
        }
    }

    s = stack<int>();

    // find the smallest-nearest rectangle to the right of heights[i]
    for (int i = n - 1; i >= 0; i--)
    {
        if (s.empty())
        {
            right[i] = n - 1;
            s.push(i);
        }
        else
        {
            while (!s.empty() && heights[s.top()] >= heights[i])
                s.pop();
            right[i] = s.empty() ? n - 1 : s.top() - 1;
            s.push(i);
        }
    }

    int maxArea = 0;
    for (int i = 0; i < n; i++)
    {
        maxArea = max(maxArea, (right[i] - left[i] + 1) * heights[i]);
    }
    return maxArea;
}

int maximalRectangle(const vector<vector<int>> &matrix)
{
    vector<int> heights(n, 0);
    int maxArea = 0;

    // build the histogram to find largest area for each row
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                heights[j] = 0;
            }
            else
            {
                heights[j] += matrix[i][j];
            }
        }

        maxArea = max(maxArea, maxS(heights));
    }

    return maxArea;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    vector<vector<int>> rec(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> rec[i][j];
        }
    }

    cout << maximalRectangle(rec) << endl;

    return 0;
}
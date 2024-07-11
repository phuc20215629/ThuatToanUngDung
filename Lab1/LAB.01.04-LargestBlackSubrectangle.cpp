#include <bits/stdc++.h>
using namespace std;

// Idea Largest Rectangular Area in a Histogram using Stack
int n, m;

// int maxS(const vector<int> &heights)
// {
//     stack<int> s;
//     int maxArea = 0;
//     int n = heights.size();
//     int i = 0;

//     // process from left to right
//     while (i < n)
//     {
//         if (s.empty() || heights[i] >= heights[s.top()])
//         {
//             s.push(i);
//             i++;
//         }
//         else
//         {
//             int tp = s.top();
//             s.pop();
//             int area = heights[tp] * (s.empty() ? i : (i - s.top() - 1));
//             maxArea = max(maxArea, area);
//         }
//     }

//     // process from right to left
//     while (!s.empty())
//     {
//         int tmp = s.top();
//         s.pop();
//         int area;
//         if (s.empty())
//             area = heights[tmp] * i;
//         else
//             area = heights[tmp] * (i - s.top() - 1);
//         maxArea = max(maxArea, area);
//     }

//     return maxArea;
// }

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
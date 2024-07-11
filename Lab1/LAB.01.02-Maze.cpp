#include <bits/stdc++.h>
using namespace std;

/*
Một mê cung hình chữ nhật được biểu diễn bởi 0-1 ma trận NxM trong đó
A[i,j] = 1 thể hiện ô (i,j) là tường gạch và A[i,j] = 0 thể hiện ô (i,j) là ô trống, có thể di chuyển vào.
Từ 1 ô trống, ta có thể di chuyển sang 1 trong 4 ô lân cận (lên trên, xuống dưới, sang trái, sang phải) nếu ô đó là ô trống.
Xuất phát từ 1 ô trống trong mê cung, hãy tìm đường ngắn nhất thoát ra khỏi mê cung.
*/

int r, c, startR, startC;
int maze[1000][1000];

struct Cell
{
    int row, col, distance;
    Cell(int r, int c, int distance) : row(r), col(c), distance(distance) {}
};

int countStep()
{
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    queue<Cell> q;

    // Direction:  Up, left, down, right
    int rowDir[] = {-1, 0, 1, 0};
    int colDir[] = {0, -1, 0, 1};

    q.push(Cell(startR, startC, 1));
    visited[startR][startC] = true;

    // use BFS to find the shortest path
    while (!q.empty())
    {
        Cell cur = q.front();
        q.pop();

        int curR = cur.row, curC = cur.col, dis = cur.distance;
        if (curR == 0 || curR == r - 1 || curC == 0 || curC == c - 1)
        { // get out of maze
            return dis;
        }

        // find next move
        for (int i = 0; i < 4; i++)
        {
            int nextR = curR + rowDir[i];
            int nextC = curC + colDir[i];

            if (nextR < r && nextC < c && maze[nextR][nextC] == 0 && !visited[nextR][nextC])
            {
                q.push(Cell(nextR, nextC, dis + 1));
                visited[nextR][nextC] = true;
            }
        }
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> r >> c >> startR >> startC;
    startR--;
    startC--;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> maze[i][j];
        }
    }

    cout << countStep();
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int r, c, startR, startC;
int maze[1000][1000];

struct Cell {
    int row, col, distance;
    Cell(int r, int c, int distance) : row(r), col(c), distance(distance){}
};

int countStep() {
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    queue<Cell> q;

    int rowDir[] = {-1, 0, 1, 0};   //Up, left, down, right
    int colDir[] = {0, -1, 0, 1};

    q.push(Cell(startR, startC, 0));
    visited[startR][startC] = true;

    while (!q.empty())
    {
        Cell cur = q.front();
        q.pop();

        int curR = cur.row, curC = cur.col, dis = cur.distance;
        if(curR == 0 || curR == r - 1 || curC == 0 || curC == c - 1) {
            return dis;
        }

        for(int i = 0; i < 4; i++) {
            int nextR = curR + rowDir[i];
            int nextC = curC + colDir[i];

            if(nextR < r && nextC < c && maze[nextR][nextC] == 0 && !visited[nextR][nextC]) {
                q.push(Cell(nextR, nextC, dis + 1));
                visited[nextR][nextC] = true;
            }
        }
    }
    
    return -2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> r >> c >> startR >> startC;
    startR--;
    startC--;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> maze[i][j];
        }
    }

    cout << countStep() + 1;
    return 0;
}
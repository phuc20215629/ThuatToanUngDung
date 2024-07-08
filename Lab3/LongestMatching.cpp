#include <iostream>
#include <cstring>
using namespace std;

string x = "abcb", y = "bdcab";
int mem[10][10];

int LCS(int i, int j)
{
    if (i == 0 || j == 0)
        return 0;
    if (mem[i][j] != -1)
        return mem[i][j];
    if (x[i - 1] == y[j - 1])
        return mem[i][j] = 1 + LCS(i - 1, j - 1);
    else
        return mem[i][j] = max(LCS(i, j - 1), LCS(i - 1, j));
}

int main()
{
    memset(mem, -1, sizeof(mem));
    int len = LCS(x.length(), y.length());
    cout << "Length of LCS: " << len << endl;
    return 0;
}
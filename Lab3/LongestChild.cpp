#include <bits/stdc++.h>
using namespace std;

int arr[] = {2, 0, 6, 1, 2, 9}, mem[10], sol = INT_MIN;

int Lis(int i)
{
    if (mem[i] != 0)
        return mem[i];

    for (int j = 0; j < i; j++)
    {
        if (arr[j] < arr[i])
        {
            sol = max(sol, 1 + Lis(j));
        }
    }

    if (sol != INT_MIN)
        return mem[i] = sol;
    else
        return mem[i] = 1;
}

int main()
{
    for (int i = 0; i < 6; i++)
    {
        Lis(i);
    }
    cout << "Longest Increasing Subsequence Length: " << sol << endl;
    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
int off[1001] = {0}; // off[i]: number of plans that day i is an off day
int on[1001] = {0};  // on[i]: number of plans that day i is a working day

int main()
{
    int N, K1, K2;
    cin >> N >> K1 >> K2;

    // because K1 >= 2, day start from 1 -> N
    off[0] = 1;
    off[1] = 1;
    on[K1] = 1;

    for (int i = 2; i <= N; i++)
    {
        off[i] = on[i - 1]; // put an off day between 2 working periods since on[i - 1] always satisfies the condition of working day in (K1, K2)
        if (i > K2)
        {
            for (int j = K1; j <= K2; j++)
            {
                on[i] += off[i - j];
            }
        }
        else if (i > K1)
        {
            for (int j = K1; j <= i; j++)
            {
                on[i] += off[i - j];
            }
        }
    }

    int result = (off[N] + on[N]) % MOD;
    cout << result << endl;

    return 0;
}
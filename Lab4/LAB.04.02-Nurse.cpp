#include <iostream>
#include <vector>
using namespace std;

/*
The director of a hospital want to schedule a working plan for a nurse in a given period of N consecutive days 1,..., N.
Due to the policy of the hospital, each nurse cannot work all the days 1,..., N.
Instead, there must be days off in which the nurse need to take a rest.
A working plan is a sequence of disjoint working periods.
A working period of a nurse is defined to be a sequence of consecutive days on which the nurse must work
and the length of the working period is the number of consecutive days of that working period. The hospital imposes two constraints:
Each nurse can take a rest only one day between two consecutive working periods.
It means that if the nurse takes a rest today, then she has to work tomorrow
The length of each working period must be greater or equal to K1 and less than or equal to K2
The director of the hospital want to know how many possible working plans satisfying above constraint?
*/

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
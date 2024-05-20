#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
int off[1001] = { 0 };  // so cach lap lich den ngay thu i ma i la ngay nghi
int on[1001] = { 0 };  // so cach lap lich den ngay thu i ma i la ngay lam viec

int main() {
    int N, K1, K2;
    cin >> N >> K1 >> K2;

    off[0] = 1;
    off[1] = 1;
    on[K1] = 1;

    for(int i = 2; i <= N; i++) {
        off[i] = on[i - 1];  // so cach xep ngay nghi vao ngay i
        if(i >= K2) {
            for(int j = K1; j <= K2; j++) {
                on[i] += off[i - j];  
            }
        }
        else if(i > K1) {
            for(int j = K1; j <= i; j++) {
                on[i] += off[i - j];
            }
        }
    }


    int result = (off[N] + on[N]) % MOD;
    cout << result << endl;

    return 0;
}
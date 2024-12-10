#include <iostream>
#include <cmath>

const int MOD = 1000000007;

using namespace std;

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long N, M, A, B;
    cin >> N >> M >> A >> B;

    long long waysLength = modExp(A, N, MOD);
    long long waysWidth = modExp(B, M, MOD);

    long long result = (waysLength * waysWidth) % MOD;

    cout << result << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N;
    cin >> N;
    
    vector<int> transactionsArray(N);
    for (int i = 0; i < N; ++i) {
        cin >> transactionsArray[i];
    }

    vector<int> DP(1 << N, 0);
    DP[0] = 1;

    for (int mask = 0; mask < (1 << N); ++mask) {
        long long currentBalance = 0;

        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                currentBalance += transactionsArray[i];
            }
        }

        for (int i = 0; i < N; ++i) {
            if (!(mask & (1 << i))) {
                if (currentBalance + transactionsArray[i] >= 0) {
                    int newMask = mask | (1 << i);
                    DP[newMask] = (DP[newMask] + DP[mask]) % MOD;
                }
            }
        }
    }

    cout << DP[(1 << N) - 1] << endl;
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int popcountFunction(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<vector<int>> numberArray(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> numberArray[i][j];
        }
    }

    vector<ll> DP(1 << N, 0);
    DP[0] = 1;

    for (int mask = 0; mask < (1 << N); mask++) {
        int X = popcountFunction(mask);
        for (int j = 0; j < N; ++j) {
            if (!(mask & (1 << j)) && numberArray[X][j]) {
                DP[mask | (1 << j)] = (DP[mask | (1 << j)] + DP[mask]) % MOD;
            }
        }
    }

    cout << DP[(1 << N) - 1] << endl;
    return 0;
}

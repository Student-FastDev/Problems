#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 3000;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;
    vector<int> valueArray(N);
    for (int i = 0; i < N; ++i) {
        cin >> valueArray[i];
    }

    vector<vector<int>> DP(N + 1, vector<int>(K + 1, 0));
    DP[0][0] = 1;

    for (int i = 1; i <= N; ++i) {
        vector<int> prefixSum(K + 1, 0);
        prefixSum[0] = DP[i - 1][0];
        for (int j = 1; j <= K; ++j) {
            prefixSum[j] = (prefixSum[j - 1] + DP[i - 1][j]) % MOD;
            // cout << prefixSum[j] << " ";
        }
        for (int j = 0; j <= K; ++j) {
            if (j > valueArray[i - 1]) {
                DP[i][j] = (prefixSum[j] - prefixSum[j - valueArray[i - 1] - 1] + MOD) % MOD;
            } else {
                DP[i][j] = prefixSum[j];
            }
            // cout << DP[i][j] << " ";
        }
    }

    cout << DP[N][K] << endl;
    return 0;
}

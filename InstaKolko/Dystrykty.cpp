#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    long long N, M;
    cin >> N >> M;

    vector<vector<long long>> cost(N, vector<long long>(M));
    vector<vector<long long>> DP(N, vector<long long>(M, LLONG_MAX));

    for (long long i = 0; i < N; i++) {
        for (long long j = 0; j < M; j++) {
            cin >> cost[i][j];
        }
    }

    for (long long i = 0; i < N; i++) {
        DP[i][0] = cost[i][0];
    }

    for (long long j = 1; j < M; j++) {
        for (long long i = 0; i < N; i++) {
            DP[i][j] = DP[i][j - 1] + cost[i][j];
            if (i > 0) {
                DP[i][j] = min(DP[i][j], DP[i - 1][j - 1] + cost[i][j]);
            }
            if (i < N - 1) {
                DP[i][j] = min(DP[i][j], DP[i + 1][j - 1] + cost[i][j]);
            }
        }

        for (long long i = 1; i < N; i++) {
            DP[i][j] = min(DP[i][j], DP[i - 1][j] + cost[i][j]);
        }

        for (long long i = N - 2; i >= 0; i--) {
            DP[i][j] = min(DP[i][j], DP[i + 1][j] + cost[i][j]);
        }
    }

    long long minCost = LLONG_MAX;
    for (long long i = 0; i < N; i++) {
        minCost = min(minCost, DP[i][M - 1]);
    }

    cout << minCost << endl;
    return 0;
}

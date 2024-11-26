#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long N, M;
    cin >> N >> M;

    vector<vector<long long>> flowers(N, vector<long long>(M));

    for (long long i = 0; i < N; ++i) {
        for (long long j = 0; j < M; ++j) {
            cin >> flowers[i][j];
        }
    }

    vector<vector<long long>> DP(N, vector<long long>(M, 0));

    DP[0][0] = flowers[0][0];

    for (long long j = 1; j < M; ++j) {
        DP[0][j] = DP[0][j - 1] + flowers[0][j];
    }

    for (long long i = 1; i < N; ++i) {
        DP[i][0] = DP[i - 1][0] + flowers[i][0];
    }

    for (long long i = 1; i < N; ++i) {
        for (long long j = 1; j < M; ++j) {
            DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]) + flowers[i][j];
        }
    }

    cout << DP[N - 1][M - 1] << endl;

    vector<pair<long long, long long>> path;
    long long i = N - 1, j = M - 1;

    while (i > 0 || j > 0) {
        path.push_back({i + 1, j + 1});
        if (i > 0 && DP[i][j] == DP[i - 1][j] + flowers[i][j]) {
            --i;
        } else {
            --j;
        }
    }
    path.push_back({1, 1});

    for (const auto& p : path) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}

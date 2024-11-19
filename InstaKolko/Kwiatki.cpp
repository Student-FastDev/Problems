#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long N, M;
    cin >> N >> M;

    vector<vector<long long>> flowersArray(N, vector<long long>(M));
    for (long long i = 0; i < N; ++i) {
        for (long long j = 0; j < M; ++j) {
            cin >> flowersArray[i][j];
        }
    }

    vector<vector<long long>> DP(N, vector<long long>(M, 0));

    DP[0][0] = flowersArray[0][0];

    for (long long j = 1; j < M; ++j) {
        DP[0][j] = DP[0][j - 1] + flowersArray[0][j];
    }

    for (long long i = 1; i < N; ++i) {
        DP[i][0] = DP[i - 1][0] + flowersArray[i][0];
    }

    for (long long i = 1; i < N; ++i) {
        for (long long j = 1; j < M; ++j) {
            DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]) + flowersArray[i][j];
        }
    }

    cout << DP[N - 1][M - 1] << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

pair<long long, pair<long long, bool>> maximalIntersections(long long N, long long M, vector<string>& board) {
    vector<long long> x_counts(N, 0), y_counts(M, 0);
    long long pointsSum = 0;

    for (long long i = 0; i < N; ++i) {
        for (long long j = 0; j < M; ++j) {
            if (board[i][j] == '#') {
                x_counts[i]++;
                y_counts[j]++;
                pointsSum++;
            }
        }
    }

    long long minScoreValue = LLONG_MAX;

    for (long long i = 0; i < N; ++i) {
        for (long long j = 0; j < M; ++j) {
            long long currentSum = x_counts[i] + y_counts[j];
            if (board[i][j] == '#') {
                currentSum--;
            }

            long long scoreValue = currentSum + (pointsSum - currentSum) * 2;
            if (board[i][j] == '#') {
                scoreValue--;
            }

            minScoreValue = min(minScoreValue, scoreValue);
        }
    }

    return {minScoreValue, {pointsSum, false}};
}

int main() {
    long long N, M;
    cin >> N >> M;

    vector<string> board(N);
    for (long long i = 0; i < N; ++i) {
        cin >> board[i];
    }

    pair<long long, pair<long long, bool>> maxInt = maximalIntersections(N, M, board);

    cout << maxInt.first << endl;
    return 0;
}

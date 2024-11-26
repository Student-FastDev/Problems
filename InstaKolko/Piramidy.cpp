#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> DP(N, vector<int>(M, 0));

    int maxHeight = 0;

    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'X') {
                if (i == N - 1) {
                    DP[i][j] = 1;
                } else {
                    int left = (j > 0) ? DP[i + 1][j - 1] : 0;
                    int right = (j < M - 1) ? DP[i + 1][j + 1] : 0;
                    int below = DP[i + 1][j];
                    DP[i][j] = 1 + min({left, right, below});
                }
                maxHeight = max(maxHeight, DP[i][j]);
            }
        }
    }

    cout << maxHeight << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> computeDensityMap(int N, int R, const vector<vector<int>>& F) {
    vector<vector<int>> prefixSum(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> W(N, vector<int>(N, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            prefixSum[i][j] = F[i - 1][j - 1] 
                            + prefixSum[i - 1][j] 
                            + prefixSum[i][j - 1] 
                            - prefixSum[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x1 = max(1, i - R), y1 = max(1, j - R);
            int x2 = min(N, i + R), y2 = min(N, j + R);

            W[i - 1][j - 1] = prefixSum[x2][y2]
                            - prefixSum[x1 - 1][y2]
                            - prefixSum[x2][y1 - 1]
                            + prefixSum[x1 - 1][y1 - 1];
        }
    }

    return W;
}

int main() {
    int N, R;
    cin >> N >> R;

    vector<vector<int>> F(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> F[i][j];
        }
    }

    vector<vector<int>> W = computeDensityMap(N, R, F);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << W[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

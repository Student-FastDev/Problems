// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define size(x) (x).size()

const int MAX_GRID = 3005;
const int OFFSET_VALUE = 3005;
const int MAX_BUCKETS = 6100;
const ll MOD = 1e9 + 7; // Catling

int leftConsecutive[MAX_GRID][MAX_GRID];
int diagonalConsecutive[MAX_GRID][MAX_GRID];
char gridMatrix[MAX_GRID][MAX_GRID];
int fenwickTree[MAX_GRID];
vector<int> valueBuckets[MAX_BUCKETS];
int N, M;

void updateFenwick(int index, int value) {
    for (; index <= N; index += index & -index) {
        fenwickTree[index] += value;
    }
}

int queryFenwick(int index) {
    int totalSum = 0;
    for (; index > 0; index -= index & -index) {
        totalSum += fenwickTree[index];
    }
    return totalSum;
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> gridMatrix[i];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (gridMatrix[i][j] == 'z') {
                leftConsecutive[i][j] = (j > 0 ? leftConsecutive[i][j - 1] : 0) + 1;
            } else {
                leftConsecutive[i][j] = 0;
            }
        }
    }

    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j < M; ++j) {
            if (gridMatrix[i][j] == 'z') {
                if (i + 1 < N && j - 1 >= 0) {
                    diagonalConsecutive[i][j] = diagonalConsecutive[i + 1][j - 1] + 1;
                } else {
                    diagonalConsecutive[i][j] = 1;
                }
            } else {
                diagonalConsecutive[i][j] = 0;
            }
        }
    }

    ll totalPatterns = 0;

    for (int j = 0; j < M; ++j) {
        for (int i = 0; i <= N; ++i) {
            fenwickTree[i] = 0;
        }

        for (int row = 0; row < N; ++row) {
            int calculatedValue = leftConsecutive[row][j] - row;
            valueBuckets[calculatedValue + OFFSET_VALUE].push_back(row);
            if (calculatedValue >= 1) {
                updateFenwick(row + 1, 1);
            }
        }

        for (int i = 0; i < N; ++i) {
            int limitLength = min(leftConsecutive[i][j], diagonalConsecutive[i][j]);
            if (limitLength > 0) {
                int maxRow = i + limitLength - 1;
                int currentCount = queryFenwick(maxRow + 1) - queryFenwick(i);
                totalPatterns += currentCount;
            }

            int targetValue = -i;
            if (targetValue + OFFSET_VALUE >= 0 && targetValue + OFFSET_VALUE < MAX_BUCKETS) {
                for (int row : valueBuckets[targetValue + OFFSET_VALUE]) {
                    updateFenwick(row + 1, 1);
                }
            }
        }

        for (int row = 0; row < N; ++row) {
            int calculatedValue = leftConsecutive[row][j] - row;
            valueBuckets[calculatedValue + OFFSET_VALUE].clear();
        }
    }

    cout << totalPatterns << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int testCaseCount = 1;
    while (testCaseCount--) {
        solve();
    }
    return 0;
}
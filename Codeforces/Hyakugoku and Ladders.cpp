// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INFINITY_VALUE = 9223372036854775806;
const ll MAXIMUM_N = 1e9 + 1;
const ll MOD = 1e9 + 7; // 998244353

void solveTestCase() {
    vector<vector<int>> boardArray(10, vector<int>(10));
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cin >> boardArray[i][j];
        }
    }

    auto getSquareIndex = [&](int rowIndex, int colIndex) -> int {
        int invertedRowIndex = 9 - rowIndex;
        if (invertedRowIndex % 2 == 0) {
            return invertedRowIndex * 10 + colIndex;
        } else {
            return invertedRowIndex * 10 + (9 - colIndex);
        }
    };

    auto getGridCoordinates = [&](int squareId) -> pii {
        int rowGroup = squareId / 10;
        int remainderValue = squareId % 10;
        int rowIndex = 9 - rowGroup;
        int colIndex;
        if (rowGroup % 2 == 0) {
            colIndex = remainderValue;
        } else {
            colIndex = 9 - remainderValue;
        }
        return {rowIndex, colIndex};
    };

    vector<int> ladderDestination(100);
    for (int i = 0; i < 100; ++i) {
        pii positionCoordinates = getGridCoordinates(i);
        int rowIndex = positionCoordinates.first;
        int colIndex = positionCoordinates.second;
        if (boardArray[rowIndex][colIndex] > 0) {
            int newRowIndex = rowIndex - boardArray[rowIndex][colIndex];
            int newColIndex = colIndex;
            ladderDestination[i] = getSquareIndex(newRowIndex, newColIndex);
        } else {
            ladderDestination[i] = i;
        }
    }

    vector<double> expectedMoves(100);
    expectedMoves[99] = 0;

    for (int i = 98; i >= 0; --i) {
        double currentSum = 0;
        int validMoveCount = 0;
        for (int diceRoll = 1; diceRoll <= 6; ++diceRoll) {
            if (i + diceRoll <= 99) {
                int nextPosition = i + diceRoll;
                double minimumValue = min(expectedMoves[nextPosition], expectedMoves[ladderDestination[nextPosition]]);
                currentSum += minimumValue;
                validMoveCount++;
            }
        }
        expectedMoves[i] = (6.0 + currentSum) / validMoveCount;
    }

    cout << fixed << setprecision(10) << expectedMoves[0] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
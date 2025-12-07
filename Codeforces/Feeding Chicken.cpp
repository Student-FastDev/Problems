// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int rows, cols, numberOfChickens;
    cin >> rows >> cols >> numberOfChickens;

    vector<string> farmGrid(rows);
    int totalRiceCells = 0;
    for (int r = 0; r < rows; ++r) {
        cin >> farmGrid[r];
        for (char cell : farmGrid[r]) {
            if (cell == 'R') {
                totalRiceCells++;
            }
        }
    }

    int ricePerChicken = totalRiceCells / numberOfChickens;
    int chickensWithExtraRice = totalRiceCells % numberOfChickens;

    vector<string> resultGrid(rows, string(cols, ' '));
    string chickenIdentifiers = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int currentChickenIndex = 0;
    int currentChickenRiceCount = 0;

    for (int r = 0; r < rows; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < cols; ++c) {
                resultGrid[r][c] = chickenIdentifiers[currentChickenIndex];
                if (farmGrid[r][c] == 'R') {
                    currentChickenRiceCount++;
                }

                int requiredRice = (currentChickenIndex < chickensWithExtraRice) ? (ricePerChicken + 1) : ricePerChicken;
                if (currentChickenRiceCount == requiredRice && currentChickenIndex < numberOfChickens - 1) {
                    currentChickenIndex++;
                    currentChickenRiceCount = 0;
                }
            }
        } else {
            for (int c = cols - 1; c >= 0; --c) {
                resultGrid[r][c] = chickenIdentifiers[currentChickenIndex];
                if (farmGrid[r][c] == 'R') {
                    currentChickenRiceCount++;
                }

                int requiredRice = (currentChickenIndex < chickensWithExtraRice) ? (ricePerChicken + 1) : ricePerChicken;
                if (currentChickenRiceCount == requiredRice && currentChickenIndex < numberOfChickens - 1) {
                    currentChickenIndex++;
                    currentChickenRiceCount = 0;
                }
            }
        }
    }

    for (int r = 0; r < rows; ++r) {
        cout << resultGrid[r] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
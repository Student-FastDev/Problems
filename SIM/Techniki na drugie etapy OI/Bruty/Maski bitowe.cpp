#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> relationArray(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < N; ++j) {
            relationArray[i][j] = row[j] - '0';
        }
    }

    int maxCount = 0;
    vector<int> bestSet;

    for (int mask = 0; mask < (1 << N); ++mask) {
        vector<int> currentSet;
        bool isValid = true;

        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                currentSet.push_back(i + 1);
                for (int j = 0; j < N; ++j) {
                    if ((mask & (1 << j)) && relationArray[i][j] == 1) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (!isValid) break;
        }

        if (isValid) {
            if (currentSet.size() > maxCount ||
                (currentSet.size() == maxCount && currentSet < bestSet)) {
                maxCount = currentSet.size();
                bestSet = currentSet;
            }
        }
    }

    cout << maxCount << endl;
    for (int i = 0; i < bestSet.size(); ++i) {
        if (i > 0) cout << " ";
        cout << bestSet[i];
    }
    cout << endl;

    return 0;
}

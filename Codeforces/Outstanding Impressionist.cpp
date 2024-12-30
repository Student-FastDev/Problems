#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int intervalsCount;
        cin >> intervalsCount;

        vector<int> leftBounds(intervalsCount), rightBounds(intervalsCount);
        vector<int> counts(2 * intervalsCount, 0);
        vector<int> prefixSum(2 * intervalsCount + 1, 0);

        for (int i = 0; i < intervalsCount; ++i) {
            cin >> leftBounds[i] >> rightBounds[i];
            leftBounds[i]--;

            if (leftBounds[i] + 1 == rightBounds[i]) {
                counts[leftBounds[i]]++;
            }
        }

        for (int i = 0; i < 2 * intervalsCount; ++i) {
            prefixSum[i + 1] = prefixSum[i] + (counts[i] == 0);
        }

        for (int i = 0; i < intervalsCount; ++i) {
            if (leftBounds[i] + 1 < rightBounds[i]) {
                cout << (prefixSum[leftBounds[i]] != prefixSum[rightBounds[i]]);
            } else {
                cout << (counts[leftBounds[i]] == 1);
            }
        }
        cout << "\n";
    }

    return 0;
}

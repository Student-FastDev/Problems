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
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<int> cardArray(Q);
        for(int i = 0; i < Q; i++) {
            cin >> cardArray[i];
        }

        vector<pair<int, int>> segmentsArray({{1, -Q}, {M, M}, {N + Q + 1, N}});
        
        for (int i = 0; i < Q; i++) {
            int A = cardArray[i];
            bool inserted = false;

            for (auto& [leftIndex, rightIndex] : segmentsArray) {
                if (A < leftIndex) {
                    leftIndex = max(1, leftIndex - 1);
                } else if (A > rightIndex) {
                    rightIndex = min(N, rightIndex + 1);
                } else {
                    inserted = true;
                    if (leftIndex == rightIndex) {
                        leftIndex = N + Q - i;
                        rightIndex = -Q + i;
                    }
                }
            }

            if (inserted) {
                segmentsArray[0] = {1, max(segmentsArray[0].second, 1)};
                segmentsArray[2] = {min(segmentsArray[2].first, N), N};
            }

            int leftSide = 0, rightSide = -1, result = 0;
            for (auto [leftIndex, rightIndex] : segmentsArray) {
                if (leftIndex > rightIndex) continue;
                if (leftIndex > rightSide) {
                    result += max(0, rightSide - leftSide + 1);
                    leftSide = leftIndex;
                    rightSide = rightIndex;
                }
                rightSide = max(rightSide, rightIndex);
            }
            result += max(0, rightSide - leftSide + 1);
            cout << result << ' ';
        }
        cout << endl;
    }

    return 0;
}

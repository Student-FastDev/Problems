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
        int N, K;
        cin >> N >> K;
        vector<int> A(N);

        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }

        --K;

        auto findFirstBetterIndex = [&]() {
            for (int i = 0; i < K; ++i) {
                if (A[i] > A[K]) {
                    return i;
                }
            }
            return K;
        };

        int iMax = findFirstBetterIndex();

        auto calculateScore = [&](int swapPos) -> int {
            swap(A[K], A[swapPos]);
            swap(K, swapPos);

            vector<int> prefixMax(N);
            prefixMax[0] = A[0];

            for (int i = 1; i < N; ++i) {
                prefixMax[i] = max(prefixMax[i - 1], A[i]);
            }

            int result = 0;
            if (K > 0 && prefixMax[K - 1] < A[K]) {
                ++result;
            }

            for (int i = K + 1; i < N; ++i) {
                if (A[K] == prefixMax[i]) {
                    ++result;
                } else {
                    break;
                }
            }

            swap(A[K], A[swapPos]);
            swap(K, swapPos);

            return result;
        };

        int result;
        if (iMax == K) {
            result = calculateScore(0);
        } else {
            result = max(calculateScore(0), calculateScore(iMax));
        }

        cout << result << '\n';
    }

    return 0;
}

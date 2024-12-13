#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K;
    cin >> N >> K;
    vector<int> valueArray(N);
    for (int i = 0; i < N; ++i) {
        cin >> valueArray[i];
    }

    vector<bool> DP(K + 1, false);

    for (int i = 1; i <= K; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i >= valueArray[j] && !DP[i - valueArray[j]]) {
                DP[i] = true;
                break;
            }
        }
    }

    if (DP[K]) { cout << "Tomek" << endl; }
    else { cout << "Michał" << endl; }
    return 0;
}

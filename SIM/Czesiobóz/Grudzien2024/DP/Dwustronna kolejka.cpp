#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 3000;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<int> valueArray(N);
    for(int i = 0; i < N; i++) {
        cin >> valueArray[i];
    }

    vector<vector<ll>> DP(N, vector<ll>(N, 0));

    for (int lenghtSize = 1; lenghtSize <= N; lenghtSize++) {
        for (int i = 0; i + lenghtSize - 1 < N; i++) {
            int j = i + lenghtSize - 1;
            if (i == j) {
                DP[i][j] = valueArray[i];
            } else {
                DP[i][j] = max(valueArray[i] - DP[i + 1][j], valueArray[j] - DP[i][j - 1]);
            }
        }
    }

    cout << DP[0][N - 1] << endl;

    return 0;
}

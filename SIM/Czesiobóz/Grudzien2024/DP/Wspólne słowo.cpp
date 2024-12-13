#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string S, T;
    cin >> S >> T;

    int N = S.size();
    int M = T.size();
    vector<vector<int>> DP(N + 1, vector<int>(M + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (S[i - 1] == T[j - 1]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            } else {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }
        }
    }

    string LCS;
    int i = N, j = M;
    while (i > 0 && j > 0) {
        if (S[i - 1] == T[j - 1]) {
            LCS.push_back(S[i - 1]);
            --i;
            --j;
        } else if (DP[i - 1][j] > DP[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(LCS.begin(), LCS.end());
    cout << LCS << endl;
    return 0;
}

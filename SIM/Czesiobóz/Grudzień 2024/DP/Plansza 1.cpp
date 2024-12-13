#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    vector<vector<char>> gridArray(N, vector<char>(M, '.'));
    vector<vector<int>> DP(N, vector<int>(M, 0));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> gridArray[i][j];
        }
    }

    DP[0][0] = 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(i == 0 && j == 0) {
                continue;
            }
            if(gridArray[i][j] == '#') {
                DP[i][j] = 0;
                continue;
            }

            if(j > 0 && gridArray[i][j-1] == '.') {
                DP[i][j] = (DP[i][j] + DP[i][j-1]) % MOD;
            }

            if(i > 0 && gridArray[i-1][j] == '.') {
                DP[i][j] = (DP[i][j] + DP[i-1][j]) % MOD;
            }
        }
    }

    cout << DP[N-1][M-1] << endl;
    return 0;
}

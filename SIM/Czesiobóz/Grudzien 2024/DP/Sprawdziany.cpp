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

    vector<long double> P(N);
    for(int i = 0; i < N; i++) {
        cin >> P[i];
    }

    int maxFails = (N - 1) / 2;
    vector<vector<long double>> DP(N + 1, vector<long double>(maxFails + 1, 0.0));
    DP[0][0] = 1.0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= maxFails; ++j) {
            DP[i][j] = DP[i-1][j] * P[i-1];
            if (j > 0) {
                DP[i][j] += DP[i-1][j-1] * (1 - P[i-1]);
            }
        }
    }

    long double result = 0.0;
    for (int j = 0; j <= maxFails; ++j) {
        result += DP[N][j];
    }

    cout << fixed << setprecision(10) << result << endl;

    return 0;
}

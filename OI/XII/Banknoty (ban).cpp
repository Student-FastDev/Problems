#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;

    vector<int> denominations(N);
    vector<int> counts(N);

    for (int i = 0; i < N; ++i) {
        cin >> denominations[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> counts[i];
    }

    int K;
    cin >> K;

    vector<int> DP(K + 1, INT_MAX);
    vector<vector<int>> used(N, vector<int>(K + 1, 0));

    DP[0] = 0;

    for (int i = 0; i < N; ++i) {
        for (int amount = K; amount >= 0; --amount) {
            if (DP[amount] != INT_MAX) {
                for (int num = 1; num <= counts[i] && amount + num * denominations[i] <= K; ++num) {
                    int newAmount = amount + num * denominations[i];
                    if (DP[newAmount] > DP[amount] + num) {
                        DP[newAmount] = DP[amount] + num;
                        used[i][newAmount] = num;
                    }
                }
            }
        }
    }

    cout << DP[K] << endl;

    vector<int> result(N, 0);
    int remaining = K;
    for (int i = N - 1; i >= 0; --i) {
        result[i] = used[i][remaining];
        remaining -= result[i] * denominations[i];
    }

    for (int i = 0; i < N; ++i) {
        cout << result[i] << (i < N - 1 ? " " : "\n");
    }
    return 0;
}

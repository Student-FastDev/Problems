#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MOD = 1e9+7;
const int MAX = 200005;

ll fact[MAX], invFact[MAX];

ll power(ll tempValue, ll yValue) {
    ll resultValue = 1;
    tempValue = tempValue % MOD;
    while (yValue > 0) {
        if (yValue & 1)
            resultValue = (resultValue * tempValue) % MOD;
        yValue = yValue >> 1;
        tempValue = (tempValue * tempValue) % MOD;
    }
    return resultValue;
}

void precomputeFactorials() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i < MAX; i++)
        fact[i] = fact[i-1] * i % MOD;
    invFact[MAX-1] = power(fact[MAX-1], MOD-2);
    for (int i = MAX-2; i >= 0; i--)
        invFact[i] = invFact[i+1] * (i+1) % MOD;
}

ll combinatorial(int N, int rValue) {
    if (rValue > N || rValue < 0) return 0;
    return fact[N] * invFact[rValue] % MOD * invFact[N-rValue] % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<pair<int, int>> blocked(K);
    for (int i = 0; i < K; ++i) {
        cin >> blocked[i].first >> blocked[i].second;
    }

    precomputeFactorials();
    sort(blocked.begin(), blocked.end());

    vector<ll> DP(K, 0);

    for (int i = 0; i < K; ++i) {
        int X = blocked[i].first, Y = blocked[i].second;
        DP[i] = combinatorial(X + Y - 2, X - 1);
        for (int j = 0; j < i; ++j) {
            int prevX = blocked[j].first, prevY = blocked[j].second;
            if (prevX <= X && prevY <= Y) {
                DP[i] = (DP[i] - DP[j] * combinatorial(X - prevX + Y - prevY, X - prevX) % MOD + MOD) % MOD;
            }
        }
    }

    ll totalPaths = combinatorial(N + M - 2, N - 1);
    for (int i = 0; i < K; ++i) {
        int X = blocked[i].first, Y = blocked[i].second;
        totalPaths = (totalPaths - DP[i] * combinatorial(N - X + M - Y, N - X) % MOD + MOD) % MOD;
    }

    cout << totalPaths << endl;
    return 0;
}

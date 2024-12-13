#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 3000;
const int MOD = 1e9+7;

vector<vector<vector<int>>> DP;

int solveFunction(string &K, int D, int positionValue, int sumValue, int tight) {
    if (positionValue == K.size()) {
        return sumValue % D == 0;
    }
    if (DP[positionValue][sumValue][tight] != -1) {
        return DP[positionValue][sumValue][tight];
    }
    int limit = tight ? K[positionValue] - '0' : 9;
    int resultValue = 0;
    for (int digit = 0; digit <= limit; digit++) {
        resultValue = (resultValue + solveFunction(K, D, positionValue + 1, (sumValue + digit) % D, tight && (digit == limit))) % MOD;
    }
    return DP[positionValue][sumValue][tight] = resultValue;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string K;
    int D;
    cin >> K >> D;

    DP = vector<vector<vector<int>>>(K.size(), vector<vector<int>>(D, vector<int>(2, -1)));
    cout << (solveFunction(K, D, 0, 0, 1) - 1 + MOD) % MOD << endl;
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

long long fastPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void precompute(int maxN, vector<long long>& results) {
    vector<long long> factorialArray(maxN + 1);
    factorialArray[0] = 1;
    for (int i = 1; i <= maxN; ++i) {
        factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
    }
    
    for (int n = 1; n <= maxN; ++n) {
        long long total = fastPow(n, n, MOD);
        long long invalid = factorialArray[n];
        results[n] = (total - invalid + MOD) % MOD;
    }
}

int main() {
    int T;
    cin >> T;
    vector<int> testCases(T);
    int maxN = 0;
    for (int i = 0; i < T; ++i) {
        cin >> testCases[i];
        maxN = max(maxN, testCases[i]);
    }
    vector<long long> results(maxN + 1);
    precompute(maxN, results);
    
    for (int i = 0; i < T; ++i) {
        cout << results[testCases[i]] << "\n";
    }
    return 0;
}

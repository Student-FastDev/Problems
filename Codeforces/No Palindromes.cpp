#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 696969;
const int PRIME = 31;

struct hashManager {
    vector<long long> prefixHash;
    vector<long long> sufixHash;
    vector<long long> powPrimeInv;
    int N;

    hashManager(const string &S) {
        N = S.size();
        prefixHash.resize(N);
        sufixHash.resize(N);
        powPrimeInv.resize(N);

        auto mul = [&](long long a, long long b) {
            return a * b % MOD;
        };
        auto add = [&](long long a, long long b) {
            return (a + b) % MOD;
        };
        auto sub = [&](long long a, long long b) {
            return (a + MOD - b) % MOD;
        };
        auto gPow = [&](long long a, long long exp) {
            for (long long res = 1;; exp >>= 1) {
                if (exp == 0) {
                    return res;
                }
                if (1 & exp)
                    res = mul(res, a);
                a = mul(a, a);
            }
        };

        int powerPrime = PRIME;
        prefixHash[0] = S[0] - 'a';
        for (int i = 1; i < N; i++) {
            prefixHash[i] = add(mul(powerPrime, S[i] - 'a'), prefixHash[i - 1]);
            powerPrime = mul(PRIME, powerPrime);
        }

        string reversedS = S;
        reverse(reversedS.begin(), reversedS.end());
        powerPrime = PRIME;
        sufixHash[0] = reversedS[0] - 'a';
        for (int i = 1; i < N; i++) {
            sufixHash[i] = add(mul(powerPrime, reversedS[i] - 'a'), sufixHash[i - 1]);
            powerPrime = mul(PRIME, powerPrime);
        }
        reverse(sufixHash.begin(), sufixHash.end());

        long long revPot = gPow(PRIME, MOD - 2);
        powPrimeInv[0] = 1;
        for (int i = 1; i < N; i++) {
            powPrimeInv[i] = mul(powPrimeInv[i - 1], revPot);
        }
    }

    long long getHashPrefix(int a, int b) {
        auto mul = [&](long long a, long long b) {
            return a * b % MOD;
        };
        auto sub = [&](long long a, long long b) {
            return (a + MOD - b) % MOD;
        };
        long long res = prefixHash[b];
        if (a > 0) {
            res = sub(res, prefixHash[a - 1]);
        }
        res = mul(res, powPrimeInv[a]);
        return res;
    }

    long long getHashSuf(int a, int b) {
        auto mul = [&](long long a, long long b) {
            return a * b % MOD;
        };
        auto sub = [&](long long a, long long b) {
            return (a + MOD - b) % MOD;
        };
        long long res = sufixHash[a];
        if (b < N - 1) {
            res = sub(res, sufixHash[b + 1]);
        }
        res = mul(res, powPrimeInv[N - 1 - b]);
        return res;
    }

    bool check(int begin, int end) {
        return getHashPrefix(begin, end) == getHashSuf(begin, end);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        string S;
        cin >> S;
        int N = S.size();

        hashManager hashManager(S);

        if (!hashManager.check(0, N - 1)) {
            cout << "YES\n1\n" << S << "\n";
            continue;
        }

        bool found = false;
        for (int i = 2; i < N - 1; i++) {
            if (!hashManager.check(0, i - 1) && !hashManager.check(i, N - 1)) {
                cout << "YES\n2\n";
                for (int j = 0; j < i; j++) {
                    cout << S[j];
                }
                cout << " ";
                for (int j = i; j < N; j++) {
                    cout << S[j];
                }
                cout << "\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "NO\n";
        }
    }

    return 0;
}

// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

long long getPower(long long baseValue, long long exponentValue) {
    long long finalResult = 1;
    baseValue %= MOD;
    while (exponentValue > 0) {
        if (exponentValue % 2 == 1) finalResult = (finalResult * baseValue) % MOD;
        baseValue = (baseValue * baseValue) % MOD;
        exponentValue /= 2;
    }
    return finalResult;
}

long long modInverse(long long N) {
    return getPower(N, MOD - 2);
}

void solveTestCase() {
    int N;
    cin >> N;

    if (N == 1) {
        cout << 1 << endl;
        return;
    }

    vector<long long> DP(1, 1);
    long long twoInverse = modInverse(2);

    for (int i = 2; i <= N; ++i) {
        vector<long long> newDP(i);
        
        long long sumTerm = 0;
        long long probabilityTwo = 2;

        for (int k = 1; k < i; ++k) {
            long long thisTerm = (probabilityTwo * DP[k - 1]) % MOD;
            sumTerm = (sumTerm + thisTerm) % MOD;
            probabilityTwo = (probabilityTwo * 2) % MOD;
        }

        long long denominatorValue = (getPower(2, i) - 1 + MOD) % MOD;
        long long denominatorInverse = modInverse(denominatorValue);
        
        newDP[i - 1] = (sumTerm * denominatorInverse) % MOD;
        newDP[0] = (newDP[i - 1] * twoInverse) % MOD;

        for (int j = 2; j < i; ++j) {
            long long firstTerm = (DP[j - 2] * twoInverse) % MOD;
            long long secondTerm = (newDP[j - 2] * twoInverse) % MOD;
            newDP[j - 1] = (firstTerm + secondTerm) % MOD;
        }

        DP = newDP; 
    }

    for (int k = 0; k < N; ++k) {
        cout << DP[k] << (k == N - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

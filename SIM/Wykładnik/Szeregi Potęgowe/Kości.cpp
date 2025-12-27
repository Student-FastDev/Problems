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
const ll MAX_N = 1e6+1;
const ll MOD = 998244353; // 998244353

ll fastPower(ll base, ll exponent) {
    ll finalResult = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent % 2 == 1) finalResult = (finalResult * base) % MOD;
        base = (base * base) % MOD;
        exponent /= 2;
    }
    return finalResult;
}

ll modInverse(ll n) {
    return fastPower(n, MOD - 2);
}

vector<ll> factorialArray;
vector<ll> inverseFactorialArray;

void precomputefactorialArrayorials(int n) {
    factorialArray.resize(n + 1);
    inverseFactorialArray.resize(n + 1);
    factorialArray[0] = 1;
    inverseFactorialArray[0] = 1;
    
    for (int i = 1; i <= n; i++) factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
    
    inverseFactorialArray[n] = modInverse(factorialArray[n]);
    for (int i = n - 1; i >= 1; i--) inverseFactorialArray[i] = (inverseFactorialArray[i + 1] * (i + 1)) % MOD;
}

ll newtonBinomial(int n, int r) {
    if (r < 0 || r > n) return 0;
    return factorialArray[n] * inverseFactorialArray[r] % MOD * inverseFactorialArray[n - r] % MOD;
}

void solveTestCase() {
    int N, M, K;
    cin >> N >> M >> K;

    if (K < N) {
        cout << 0 << endl;
        return;
    }

    precomputefactorialArrayorials(K);
    ll finalAnswer = 0;

    for (int j = 0; j <= N; j++) {
        int upperValue = K - M * j;
        if (upperValue < N) break;

        ll temporaryVariable = newtonBinomial(N, j) * newtonBinomial(upperValue, N) % MOD;
        if (j % 2 == 1) finalAnswer = (finalAnswer - temporaryVariable + MOD) % MOD;
        else finalAnswer = (finalAnswer + temporaryVariable) % MOD;
    }

    cout << finalAnswer << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

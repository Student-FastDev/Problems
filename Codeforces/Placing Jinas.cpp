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

const int MAX_VAL = 400005;
ll factorialArray[MAX_VAL];
ll inverseFactorialArray[MAX_VAL];

ll power(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

ll modInverse(ll N) {
    return power(N, MOD - 2);
}

void precomputeFactorials() {
    factorialArray[0] = 1;
    inverseFactorialArray[0] = 1;
    for (int i = 1; i < MAX_VAL; i++) {
        factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
        inverseFactorialArray[i] = modInverse(factorialArray[i]);
    }
}

ll nCr(int N, int R) {
    if (R < 0 || R > N) return 0;
    return factorialArray[N] * inverseFactorialArray[R] % MOD * inverseFactorialArray[N - R] % MOD;
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> A(N + 1);
    for (int i = 0; i <= N; ++i) {
        cin >> A[i];
    }

    ll totalOperations = 0;
    for (int x = 1; x <= N + 1; ++x) {
        int val = A[x - 1];
        ll term = nCr(val + x - 1, x);
        totalOperations = (totalOperations + term) % MOD;
    }

    cout << totalOperations << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    precomputeFactorials();

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
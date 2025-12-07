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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 998244353;

ll power(ll baseValue, ll exponent) {
    ll result = 1;
    baseValue %= MOD;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * baseValue) % MOD;
        baseValue = (baseValue * baseValue) % MOD;
        exponent /= 2;
    }
    return result;
}

ll modInverse(ll number) {
    return power(number, MOD - 2);
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> A(N);
    int zeroCount = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        if (A[i] == 0) zeroCount++;
    }

    int onesInPrefixCount = 0;
    for (int i = 0; i < zeroCount; ++i) {
        if (A[i] == 1) onesInPrefixCount++;
    }

    if (onesInPrefixCount == 0) {
        cout << 0 << endl;
        return;
    }

    ll totalPairs = (1LL * N * (N - 1) / 2) % MOD;
    ll sumInverseSquares = 0;

    for (int i = 1; i <= onesInPrefixCount; ++i) {
        ll squareVal = (1LL * i * i) % MOD;
        ll invSquare = modInverse(squareVal);
        sumInverseSquares = (sumInverseSquares + invSquare) % MOD;
    }

    ll expectedValue = (totalPairs * sumInverseSquares) % MOD;
    cout << expectedValue << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
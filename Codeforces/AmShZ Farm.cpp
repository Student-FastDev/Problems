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
const ll MOD = 998244353; // 998244353

ll power(ll base, ll exponent) {
    ll result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent /= 2;
    }
    return result;
}

ll modInverse(ll n) {
    return power(n, MOD - 2);
}

void ntt(vector<ll>& coefficients, bool isInvert) {
    int n = size(coefficients);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(coefficients[i], coefficients[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = power(3, (MOD - 1) / len);
        if (isInvert) wlen = modInverse(wlen);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = coefficients[i + j];
                ll v = (coefficients[i + j + len / 2] * w) % MOD;
                coefficients[i + j] = (u + v) % MOD;
                coefficients[i + j + len / 2] = (u - v + MOD) % MOD;
                w = (w * wlen) % MOD;
            }
        }
    }
    if (isInvert) {
        ll nInverse = modInverse(n);
        for (ll& x : coefficients) x = (x * nInverse) % MOD;
    }
}

vector<ll> multiply(vector<ll> const& polynomialA, vector<ll> const& polynomialB) {
    vector<ll> fftA(all(polynomialA));
    vector<ll> fftB(all(polynomialB));
    int n = 1;
    while (n < size(polynomialA) + size(polynomialB)) n <<= 1;
    fftA.resize(n);
    fftB.resize(n);
    ntt(fftA, false);
    ntt(fftB, false);
    for (int i = 0; i < n; i++) fftA[i] = (fftA[i] * fftB[i]) % MOD;
    ntt(fftA, true);
    return fftA;
}

void solveTestCase() {
    ll N;
    int K;
    cin >> N >> K;

    vector<ll> factorialArray(K + 1), inverseFactorialArray(K + 1);
    factorialArray[0] = 1;
    for (int i = 1; i <= K; i++) factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
    inverseFactorialArray[K] = modInverse(factorialArray[K]);
    for (int i = K - 1; i >= 0; i--) inverseFactorialArray[i] = (inverseFactorialArray[i + 1] * (i + 1)) % MOD;

    vector<ll> polynomialA(K + 1), polynomialB(K + 1);
    for (int i = 0; i <= K; i++) {
        polynomialA[i] = inverseFactorialArray[i];
        if (i % 2 == 1) polynomialA[i] = (MOD - polynomialA[i]) % MOD;
        polynomialB[i] = (power(i, K) * inverseFactorialArray[i]) % MOD;
    }

    vector<ll> stirlingNumbers = multiply(polynomialA, polynomialB);

    if ((N + 1) % MOD == 0) {
        if (N <= K) {
            int nVal = (int)N;
            ll currentAnswer = (factorialArray[nVal] * stirlingNumbers[nVal]) % MOD;
            cout << currentAnswer << endl;
        } else {
            cout << 0 << endl;
        }
        return;
    }

    ll totalAnswer = 0;
    ll basePower = power((N + 1) % MOD, N);
    ll inverseBase = modInverse((N + 1) % MOD);

    int loopLimit = K;
    if (N < K) loopLimit = (int)N;

    ll currentInversePower = inverseBase;
    ll fallingFactorial = N % MOD;

    for (int m = 1; m <= loopLimit; ++m) {
        ll stirlingValue = stirlingNumbers[m];
        ll currentTerm = (fallingFactorial * stirlingValue) % MOD;
        currentTerm = (currentTerm * currentInversePower) % MOD;

        totalAnswer = (totalAnswer + currentTerm) % MOD;

        if (m < loopLimit) {
            fallingFactorial = (fallingFactorial * ((N - m) % MOD)) % MOD;
            currentInversePower = (currentInversePower * inverseBase) % MOD;
        }
    }

    totalAnswer = (totalAnswer * basePower) % MOD;
    cout << totalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
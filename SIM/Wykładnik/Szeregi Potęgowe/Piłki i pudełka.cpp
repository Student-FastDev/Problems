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
#define size(x) (int)(x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e6+1;
const ll MOD = 998244353; // 998244353
const int G = 3;

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

void precomputeFactorials(int n) {
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

void NTT(vector<ll>& A, bool invert) {
    int n = size(A);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(A[i], A[j]);
    }
    for (int length = 2; length <= n; length <<= 1) {
        ll secondLength = fastPower(G, (MOD - 1) / length);
        if (invert) secondLength = modInverse(secondLength);
        for (int i = 0; i < n; i += length) {
            ll w = 1;
            for (int j = 0; j < length / 2; j++) {
                ll u = A[i + j];
                ll v = (A[i + j + length / 2] * w) % MOD;
                ll firstValue = u + v;
                if (firstValue >= MOD) firstValue -= MOD;
                A[i + j] = firstValue;
                ll secondValue = u - v;
                if (secondValue < 0) secondValue += MOD;
                A[i + j + length / 2] = secondValue;
                w = (w * secondLength) % MOD;
            }
        }
    }
    if (invert) {
        ll inverseN = modInverse(n);
        for (ll& x : A) x = (x * inverseN) % MOD;
    }
}

vector<ll> multiplyPolynomials(const vector<ll>& constantA, const vector<ll>& constantB) {
    vector<ll> A = constantA;
    vector<ll> B = constantB;
    int n = 1;
    while (n < size(A) + size(B)) n <<= 1;
    A.resize(n);
    B.resize(n);
    NTT(A, false);
    NTT(B, false);
    for (int i = 0; i < n; i++) A[i] = (A[i] * B[i]) % MOD;
    NTT(A, true);
    return A;
}

void solveTestCase() {
    int A, B, C, N;
    cin >> A >> B >> C >> N;

    int currentSize = 1;
    while (currentSize <= 3 * N) currentSize <<= 1;

    vector<ll> firstPolynomial(currentSize, 0), secondPolynomial(currentSize, 0), thirdPolynomial(currentSize, 0);
    
    for (int i = 0; i <= N; i += A) firstPolynomial[i] = 1;
    for (int i = 0; i <= N; i += B) secondPolynomial[i] = 1;
    for (int i = 0; i <= N; i += C) thirdPolynomial[i] = 1;

    NTT(firstPolynomial, false);
    NTT(secondPolynomial, false);
    NTT(thirdPolynomial, false);

    for (int i = 0; i < currentSize; i++) {
        ll currentProduct = (firstPolynomial[i] * secondPolynomial[i]) % MOD;
        firstPolynomial[i] = (currentProduct * thirdPolynomial[i]) % MOD;
    }

    NTT(firstPolynomial, true);
    cout << firstPolynomial[N] << endl;

    precomputeFactorials(N);
    fill(all(firstPolynomial), 0);
    fill(all(secondPolynomial), 0);
    fill(all(thirdPolynomial), 0);

    for (int i = 0; i <= N; i += A) firstPolynomial[i] = inverseFactorialArray[i];
    for (int i = 0; i <= N; i += B) secondPolynomial[i] = inverseFactorialArray[i];
    for (int i = 0; i <= N; i += C) thirdPolynomial[i] = inverseFactorialArray[i];

    NTT(firstPolynomial, false);
    NTT(secondPolynomial, false);
    NTT(thirdPolynomial, false);

    for (int i = 0; i < currentSize; i++) {
        ll currentProduct = (firstPolynomial[i] * secondPolynomial[i]) % MOD;
        firstPolynomial[i] = (currentProduct * thirdPolynomial[i]) % MOD;
    }

    NTT(firstPolynomial, true);
    
    ll secondAnswer = (firstPolynomial[N] * factorialArray[N]) % MOD;
    cout << secondAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

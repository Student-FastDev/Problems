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
    for (; exponent; exponent >>= 1, base = base * base % MOD) 
        if (exponent & 1) result = result * base % MOD;
    return result;
}

ll modInverse(ll n) { return power(n, MOD - 2); }

void ntt(vector<ll>& polynomial, bool invert) {
    int n = size(polynomial);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(polynomial[i], polynomial[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wLen = power(3, (MOD - 1) / len);
        if (invert) wLen = modInverse(wLen);
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = polynomial[i + j], v = (polynomial[i + j + len / 2] * w) % MOD;
                polynomial[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                polynomial[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                w = (w * wLen) % MOD;
            }
        }
    }
    if (invert) {
        ll nInverse = modInverse(n);
        for (ll& x : polynomial) x = x * nInverse % MOD;
    }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<ll> transformedA(a.begin(), a.end()), transformedB(b.begin(), b.end());
    int n = 1;
    while (n < (int)(size(a) + size(b))) n <<= 1;
    transformedA.resize(n); transformedB.resize(n);
    ntt(transformedA, false); ntt(transformedB, false);
    for (int i = 0; i < n; i++) transformedA[i] = transformedA[i] * transformedB[i] % MOD;
    ntt(transformedA, true);
    return transformedA;
}

const int MAX_FACT = 300005;
ll factorialArray[MAX_FACT], inverseFactorialArray[MAX_FACT];

void precomputeFactorials() {
    factorialArray[0] = 1;
    for (int i = 1; i < MAX_FACT; i++) factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
    inverseFactorialArray[MAX_FACT - 1] = modInverse(factorialArray[MAX_FACT - 1]);
    for (int i = MAX_FACT - 2; i >= 0; i--) inverseFactorialArray[i] = (inverseFactorialArray[i + 1] * (i + 1)) % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return factorialArray[n] * inverseFactorialArray[r] % MOD * inverseFactorialArray[n - r] % MOD;
}

void solveTestCase() {
    int N, K;
    cin >> N >> K;
    vector<int> whiteBoardLengths(N);
    vector<int> lengthFrequency(300005, 0);
    for (int i = 0; i < N; ++i) {
        cin >> whiteBoardLengths[i];
        lengthFrequency[whiteBoardLengths[i]]++;
    }
    vector<int> redBoardLengths(K);
    for (int i = 0; i < K; ++i) cin >> redBoardLengths[i];

    int Q;
    cin >> Q;
    vector<int> queryPerimeters(Q);
    for (int i = 0; i < Q; ++i) cin >> queryPerimeters[i];

    vector<int> singleCountPrefixSum(300005, 0);
    vector<int> multiCountPrefixSum(300005, 0);
    for (int i = 1; i <= 300000; ++i) {
        singleCountPrefixSum[i] = singleCountPrefixSum[i - 1] + (lengthFrequency[i] == 1);
        multiCountPrefixSum[i] = multiCountPrefixSum[i - 1] + (lengthFrequency[i] >= 2);
    }

    precomputeFactorials();
    vector<ll> finalAnswer(Q, 0);

    for (int redLength : redBoardLengths) {
        int singleCount = 0, multiCount = 0;
        if (redLength > 1) {
            singleCount = singleCountPrefixSum[redLength - 1];
            multiCount = multiCountPrefixSum[redLength - 1];
        }

        vector<ll> polynomialA(singleCount + 1);
        ll powerOfTwo = 1;
        for (int j = 0; j <= singleCount; ++j) {
            polynomialA[j] = nCr(singleCount, j) * powerOfTwo % MOD;
            powerOfTwo = powerOfTwo * 2 % MOD;
        }

        int exponentB = 2 * multiCount;
        vector<ll> polynomialB(exponentB + 1);
        for (int j = 0; j <= exponentB; ++j) {
            polynomialB[j] = nCr(exponentB, j);
        }

        vector<ll> convolutionResult = multiply(polynomialA, polynomialB);

        for (int i = 0; i < Q; ++i) {
            ll perimeter = queryPerimeters[i];
            ll neededLength = perimeter / 2 - redLength;
            if (neededLength < 1) continue;
            ll k = neededLength - 1;
            if (k >= 0 && k < (int)size(convolutionResult)) {
                finalAnswer[i] = (finalAnswer[i] + convolutionResult[k]) % MOD;
            }
        }
    }

    for (int i = 0; i < Q; ++i) cout << finalAnswer[i] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}
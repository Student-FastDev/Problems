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

ll modularPower(ll powerBase, ll exponentValue, ll moduloValue = MOD) {
    powerBase %= moduloValue;
    ll powerResult = 1;
    while (exponentValue > 0) {
        if (exponentValue & 1) powerResult = (powerResult * powerBase) % moduloValue;
        powerBase = (powerBase * powerBase) % moduloValue;
        exponentValue >>= 1;
    }
    return powerResult;
}

vector<ll> BerlekampMassey(const vector<ll> &S) {
    int N = size(S);
    vector<ll> C(N, 0), B(N, 0);
    C[0] = 1; B[0] = 1;
    int L = 0, M = 1;
    ll K = 1;
    for (int i = 0; i < N; i++) {
        ll O = S[i];
        for (int j = 1; j <= L; j++) O = (O + C[j] * S[i - j]) % MOD;
        if (O == 0) { M++;
        } else {
            ll coefficientValue = O * modularPower(K, MOD-2, MOD) % MOD;
            vector<ll> T = C;
            for (int j = M; j < N; j++) C[j] = (C[j] - coefficientValue * B[j - M]) % MOD;
            if (2 * L <= i) {
                L = i + 1 - L; B = T; K = O; M = 1;
            } else {
                M++;
            }
        }
    }
    C.resize(L + 1);
    return C;
}

vector<ll> multiplyPolynomial(const vector<ll> &A, const vector<ll> &K, const vector<ll> &recurrencePolynomial) {
    int DA = size(A), DB = size(K), O = size(recurrencePolynomial);
    vector<ll> powerResult(DA + DB - 1, 0);
    for (int i = 0; i < DA; i++) {
        for (int j = 0; j < DB; j++) powerResult[i + j] = (powerResult[i + j] + A[i] * K[j]) % MOD;
    }
    while (size(powerResult) > O) {
        ll coefficientValue = powerResult.back();
        int degreeCount = size(powerResult) - 1;
        powerResult.pop_back();
        for (int i = 0; i < O; i++) {
            if (degreeCount - 1 - i < 0) break;
            powerResult[degreeCount - 1 - i] = (powerResult[degreeCount - 1 - i] + coefficientValue * recurrencePolynomial[i]) % MOD;
        }
    }
    for (ll &x : powerResult) 
        if (x < 0) x += MOD;
    return powerResult;
}

ll solveLinearRecurrence(vector<ll> S, ll K) {
    int N = size(S);
    if (K < N) return S[K];
    vector<ll> C = BerlekampMassey(S);
    int O = size(C) - 1;
    if (O == 0) return 0;

    vector<ll> initialVector(S.begin(), S.begin() + O);
    if (K < O) return initialVector[K];
    
    vector<ll> T = vector<ll>(O, 0);
    for (int i = 1; i <= O; i++) T[i - 1] = (MOD - C[i]) % MOD;
    
    vector<ll> U = {1}, P = {0, 1};
    ll exponentValue = K;
    
    while (exponentValue) {
        if (exponentValue & 1) U = multiplyPolynomial(U, P, T);
        P = multiplyPolynomial(P, P, T);
        exponentValue >>= 1;
    }
    
    ll powerResult = 0;
    for (int i = 0; i < size(U) && i < size(initialVector); i++) 
        powerResult = (powerResult + U[i] * initialVector[i]) % MOD;
    return (powerResult + MOD) % MOD;
}

void solveTestCase() {
    int N; ll K;
    cin >> N >> K;

    vector<int> A(N);
    int zeroCount = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] == 0) zeroCount++;
    }

    int oneCount = N - zeroCount;
    int misplacedCount = 0;
    for (int i = 0; i < zeroCount; i++) 
        if (A[i] == 1) 
            misplacedCount++;

    int M = min(zeroCount, oneCount);
    if (M == 0) {
        cout << (misplacedCount == 0 ? 1 : 0) << endl;
        return;
    }

    ll totalPairs = (ll)N * (N - 1) / 2 % MOD;
    ll totalInversion = modularPower(totalPairs, MOD-2, MOD);

    vector<ll> pValue(M + 1, 0), rValue(M + 1, 0), qValue(M+1, 0);
    for (int x = 0; x <= M; x++) {
        if (x > 0) {
            pValue[x] = (ll)x * x % MOD;
            pValue[x] = pValue[x] * totalInversion % MOD;
        }
        if (x < M) {
            rValue[x] = (ll)(zeroCount - x) * (oneCount - x) % MOD;
            rValue[x] = rValue[x] * totalInversion % MOD;
        }
        ll selfValue = (totalPairs - (ll)x*x - (ll)(zeroCount - x) * (oneCount - x)) % MOD;
        if (selfValue < 0) selfValue += MOD;
        qValue[x] = selfValue * totalInversion % MOD;
    }

    vector<ll> currentState(M+1, 0);
    currentState[misplacedCount] = 1;
    vector<ll> sequenceArray;
    sequenceArray.push_back(currentState[0]);

    for (int step = 1; step <= 2 * (M+1); step++) {
        vector<ll> newState(M+1, 0);
        for (int y = 0; y <= M; y++) {
            if (y > 0) 
                newState[y] = (newState[y] + currentState[y - 1] * rValue[y - 1]) % MOD;
            newState[y] = (newState[y] + currentState[y] * qValue[y]) % MOD;
            if (y < M) 
                newState[y] = (newState[y] + currentState[y + 1] * pValue[y + 1]) % MOD;
            if (newState[y] < 0) newState[y] += MOD;
        }
        currentState = newState;
        sequenceArray.push_back(currentState[0]);
    }

    ll finalResult;
    if (K < size(sequenceArray)) finalResult = sequenceArray[K];
    else finalResult = solveLinearRecurrence(sequenceArray, K);
    cout << finalResult << endl;

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

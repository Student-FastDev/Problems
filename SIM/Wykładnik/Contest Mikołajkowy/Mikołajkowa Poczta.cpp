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
#define size(x)  (int)(x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;

struct Matrix {
    ll matrixArray[2][2];
    Matrix() {
        matrixArray[0][0] = matrixArray[0][1] = matrixArray[1][0] = matrixArray[1][1] = 0;
    }
};

Matrix multiplyMatrices(Matrix A, Matrix B) {
    Matrix C;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                C.matrixArray[i][j] = (C.matrixArray[i][j] + A.matrixArray[i][k] * B.matrixArray[k][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix powerMatrix(Matrix A, ll p) {
    Matrix finalResult;
    finalResult.matrixArray[0][0] = 1; finalResult.matrixArray[1][1] = 1;
    A.matrixArray[0][0] %= MOD; A.matrixArray[0][1] %= MOD; A.matrixArray[1][0] %= MOD; A.matrixArray[1][1] %= MOD;
    while(p > 0) {
        if(p & 1) finalResult = multiplyMatrices(finalResult, A);
        A = multiplyMatrices(A, A);
        p >>= 1;
    }
    return finalResult;
}

void solveTestCase() {
    int N;
    ll M;
    cin >> N >> M;

    vector<ll> shortTrails(N);
    vector<ll> longTrails(N);
    vector<ll> totalTrails(N);

    for(int i = 0; i < N; ++i) cin >> shortTrails[i];
    for(int i = 0; i < N; ++i) cin >> longTrails[i];
    for(int i = 0; i < N; ++i) totalTrails[i] = shortTrails[i] + longTrails[i];

    ll sumTotalTotal = 0;
    ll sumTotalLong = 0;
    ll sumLongLong = 0;
    ll sumAllTotal = 0;
    ll sumAllLong = 0;

    for(int i = 0; i < N; ++i) {
        sumTotalTotal = (sumTotalTotal + totalTrails[i] * totalTrails[i]) % MOD;
        sumTotalLong = (sumTotalLong + totalTrails[i] * longTrails[i]) % MOD;
        sumLongLong = (sumLongLong + longTrails[i] * longTrails[i]) % MOD;
        
        sumAllTotal = (sumAllTotal + totalTrails[i]) % MOD;
        sumAllLong = (sumAllLong + longTrails[i]) % MOD;
    }

    Matrix transitionMatrix;
    transitionMatrix.matrixArray[0][0] = sumTotalTotal;
    transitionMatrix.matrixArray[0][1] = sumTotalLong;
    transitionMatrix.matrixArray[1][0] = (MOD - sumTotalLong) % MOD;
    transitionMatrix.matrixArray[1][1] = (MOD - sumLongLong) % MOD;

    Matrix poweredMatrix = powerMatrix(transitionMatrix, M - 1);

    ll A = totalTrails[0] % MOD;
    ll B = (MOD - longTrails[0] % MOD) % MOD;

    ll C = (poweredMatrix.matrixArray[0][0] * A + poweredMatrix.matrixArray[0][1] * B) % MOD;
    ll D = (poweredMatrix.matrixArray[1][0] * A + poweredMatrix.matrixArray[1][1] * B) % MOD;

    ll finalAnswer = (C * sumAllTotal + D * sumAllLong) % MOD;
    
    cout << finalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
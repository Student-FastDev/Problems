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
const ll MOD = 1e9+7; 

const int MAX_ARRAY_SIZE = 1000005;
const int LOG_N_VAL = 21;
ll sparseTable[MAX_ARRAY_SIZE][LOG_N_VAL];
int logValues[MAX_ARRAY_SIZE];

void buildSparseTable(const vector<ll>& V) {
    int N = size(V);
    logValues[1] = 0;
    for (int i = 2; i <= N; i++)
        logValues[i] = logValues[i/2] + 1;
    
    for (int i = 0; i < N; i++)
        sparseTable[i][0] = V[i];
    
    for (int j = 1; j < LOG_N_VAL; j++) {
        for (int i = 0; i + (1 << j) <= N; i++) {
            sparseTable[i][j] = max(sparseTable[i][j-1], sparseTable[i + (1 << (j-1))][j-1]);
        }
    }
}

ll querySparseTable(int L, int R) {
    if (L > R) return -2e18; 
    int j = logValues[R - L + 1];
    return max(sparseTable[L][j], sparseTable[R - (1 << j) + 1][j]);
}

ll solveOneDirection(int N, const vector<ll>& A, const vector<ll>& B) {
    vector<ll> S(N);
    ll currentS = 0;
    for(int i = 0; i < N; ++i) {
        currentS += (A[i] - B[i]);
        S[i] = currentS;
    }

    vector<ll> C(N);
    ll currentC = 0;
    for(int i = 0; i < N; ++i) {
        currentC += A[i];
        C[i] = currentC;
    }

    vector<ll> V(N);
    for(int i = 0; i < N; ++i) {
        V[i] = C[i] - (i + 1);
    }

    buildSparseTable(V);
    ll maxTime = 0;
    
    for(int i = 0; i < N - 1; ++i) {
        if (S[i] > 0) {
            ll neededFlow = S[i];
            ll startPersonIndex = C[i] - neededFlow + 1;
            
            auto iterator = lower_bound(all(C), startPersonIndex);
            int P = distance(C.begin(), iterator);
            ll maxValue = querySparseTable(P, i);
            
            ll calculatedTime = neededFlow + (i + 1) - C[i] + maxValue;
            if (calculatedTime > maxTime) {
                maxTime = calculatedTime;
            }
        }
    }
    return maxTime;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<ll> A(N), B(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    for(int i = 0; i < N; ++i) cin >> B[i];

    ll firstTime = solveOneDirection(N, A, B);

    reverse(all(A));
    reverse(all(B));
    ll secondTime = solveOneDirection(N, A, B);

    cout << max(firstTime, secondTime) << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

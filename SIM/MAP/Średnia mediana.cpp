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
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353
const ld INF = numeric_limits<ld>::infinity();

int N;
vector<ll> A;

bool canAchieveAverage(ld X) {
    vector<ld> firstDP(N+1, -INF);
    vector<ld> secondDP(N+1, -INF);
    
    firstDP[1] = 0;
    secondDP[1] = (ld)A[0] - X;

    for (int i = 2; i <= N; i++) {
        ld val = (ld)A[i-1] - X;
        secondDP[i] = max(firstDP[i-1], secondDP[i-1]) + val;
        firstDP[i] = secondDP[i-1];
    }
    
    ld bestScore = max(firstDP[N], secondDP[N]);
    return bestScore >= 0;
}

bool canAchieveMedian(ll M) {
    vector<ll> firstDP(N+1, -1000000000);
    vector<ll> secondDP(N+1, -1000000000);
    
    firstDP[1] = 0; 
    secondDP[1] = (A[0] >= M ? 1 : -1);

    for (int i = 2; i <= N; i++) {
        ll B = (A[i-1] >= M ? 1 : -1);
        secondDP[i] = max(firstDP[i-1], secondDP[i-1]) + B;
        firstDP[i] = secondDP[i-1];
    }
    
    ll bestScore = max(firstDP[N], secondDP[N]);
    return bestScore >= 1;
}


void solveTestCase() {
    cin >> N;
    A.resize(N);
    ll lowA = 1, highA = 0;
    for (int i = 0; i < N; i++){
        cin >> A[i];
        highA = max(highA, A[i]);
    }
    
    ld L = 0.0, R = highA;
    for (int i = 0; i < 60; i++){
        ld M = (L + R) / 2.0;
        if (canAchieveAverage(M))
            L = M;
        else
            R = M;
    }
    ld bestAverage = L;
    
    L = 1, R = highA;
    ll bestMedian = 1;
    while (L <= R) {
        ll M = (L + R) / 2;
        if (canAchieveMedian(M)) {
            bestMedian = M;
            L = M + 1;
        }
        else {
            R = M - 1;
        }
    }
    
    cout << fixed << setprecision(15) << bestAverage << endl;
    cout << bestMedian << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

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

const ll INF = numeric_limits<ll>::max();
const ll MAX_N = 8000;
const ll MOD = 1e9+7; // 998244353

ll modAdd(ll a, ll b, ll mod) {
    return (a + b) % mod;
}

ll modMul(ll a, ll b, ll mod) {
    return (a * b) % mod;
}

ll modSub(ll a, ll b, ll mod) {
    return ((a - b) + mod) % mod;
}

void solveTestCase() {
    ll N, A, B, M; 
    cin >> N >> A >> B >> M;

    ll previousDP[MAX_N], currentDP[MAX_N];

    previousDP[1] = 1;

    for(int i = 2; i <= N; i++) {
        for(int j = 1; j <= i; j++) {    
            if(i == A || i == B) {
                currentDP[j] = modAdd(previousDP[j], previousDP[j-1], M);
            } else {
                currentDP[j] = modAdd(modMul(previousDP[j+1], j, M), 
                                 modMul(previousDP[j-1], (j - (i > A) - (i > B)), M), M);
            }
        }

        for(int j = 1; j <= i; j++) {
            previousDP[j] = currentDP[j];
        }
    }

    cout << previousDP[1] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

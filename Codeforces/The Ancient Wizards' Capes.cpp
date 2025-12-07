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
const ll MOD = 676767677;

ll floorHalf(ll x) {
    if (x >= 0) return x / 2;
    return (x - 1) / 2;
}

ll ceilHalf(ll x) {
    if (x >= 0) return (x + 1) / 2;
    return x / 2;
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<ll> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    vector<ll> C(N);
    for(int i = 0; i < N; ++i) {
        C[i] = A[i] - 1 - N + (i + 1);
    }

    ll baseK = C[N-1];
    vector<ll> candidates = {baseK, baseK + 1};

    int validCount = 0;

    for (ll K : candidates) {
        ll T1 = C[0] + K;
        if (T1 < 0 || T1 > 1) continue;

        bool ok = true;
        for(int i = 0; i < N - 1; ++i) {
            ll leftVal = floorHalf(C[i+1] + K);
            ll rightVal = ceilHalf(C[i] + K);
            if (leftVal != rightVal) {
                ok = false;
                break;
            }
        }
        
        if (ok) {
            validCount++;
        }
    }
    
    cout << validCount << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
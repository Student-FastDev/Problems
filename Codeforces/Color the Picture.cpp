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

bool checkPossibility(ll gridHeight, ll gridWidth, const vector<ll>& pigmentAmounts) {
    ll maxCoverable = 0;
    bool canAdjustParity = false;
    for (ll pigmentAmount : pigmentAmounts) {
        ll contribution = pigmentAmount / gridHeight;
        if (contribution >= 2) {
            maxCoverable += contribution;
            if (contribution > 2) canAdjustParity = true;
        }
    }
    if (maxCoverable < gridWidth) return false;
    if (gridWidth % 2 != 0 && !canAdjustParity) return false;
    return true;
}

void solveTestCase() {
    ll N, M;
    int K;
    cin >> N >> M >> K;
    vector<ll> pigmentValues(K);
    for (int i = 0; i < K; ++i) {
        cin >> pigmentValues[i];
    }

    if (checkPossibility(N, M, pigmentValues) || checkPossibility(M, N, pigmentValues)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
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
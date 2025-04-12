// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';ll i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll, ll> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

bool isPossible(const vector<ll>& deskPositions, ll N, ll minDistance) {
    ll lastDesk = deskPositions[0];
    ll counterValue = 1;

    for (ll i = 1; i < size(deskPositions); i++) {
        if (deskPositions[i] - lastDesk >= minDistance) {
            counterValue++;
            lastDesk = deskPositions[i];
            if (counterValue >= N) return true;
        }
    }
    return false;
}

void solveTestCase() {
    ll N, K;
    cin >> N >> K;

    vector<ll> distancesValues(K - 1);
    for (ll i = 0; i < K - 1; ++i) {
        cin >> distancesValues[i];
    }

    vector<ll> deskPositions(K);
    deskPositions[0] = 0;
    for (ll i = 1; i < K; ++i) {
        deskPositions[i] = deskPositions[i - 1] + distancesValues[i - 1];
    }

    ll L = 0;
    ll R = deskPositions.back();
    ll scoreValue = 0;

    while (L <= R) {
        ll M = (L + R) / 2;
        if (isPossible(deskPositions, N, M)) {
            scoreValue = M;
            L = M + 1;
        } else {
            R = M - 1;
        }
    }

    cout << scoreValue << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

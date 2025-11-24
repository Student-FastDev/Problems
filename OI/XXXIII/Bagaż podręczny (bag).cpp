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

void solveTestCase() {
    ll N;
    cin >> N;

    ll firstD = INF;
    ll secondD = INF;
    ll thirdD = INF;
    ll D[3];

    for (ll i = 0; i < N; ++i) {
        cin >> D[0] >> D[1] >> D[2];

        if (D[0] > D[1]) swap(D[0], D[1]);
        if (D[1] > D[2]) swap(D[1], D[2]);
        if (D[0] > D[1]) swap(D[0], D[1]);
        if (D[0] < firstD) firstD = D[0];
        if (D[1] < secondD) secondD = D[1];
        if (D[2] < thirdD) thirdD = D[2];
    }

    ll currentVolume = (ll)firstD * secondD * thirdD;
    cout << currentVolume << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
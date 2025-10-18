// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    ll N, Q;
    cin >> N >> Q;

    vector<ll> M(N);
    for (int i = 0; i < N; ++i) {
        cin >> M[i];
    }

    vector<ll> moduloValues;
    ll globalMininimum = INF;
    for (int i = 0; i < N; ++i) {
        if (M[i] < globalMininimum) {
            moduloValues.push_back(M[i]);
            globalMininimum = M[i];
        }
    }

    for (int i = 0; i < Q; ++i) {
        ll X;
        cin >> X;

        auto it = moduloValues.begin();
        while (it != moduloValues.end() && X > 0) {
            it = lower_bound(it, moduloValues.end(), X, greater<ll>());
            if (it == moduloValues.end()) break;
            X %= *it; it++;
        }
        cout << X << endl;
    }
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

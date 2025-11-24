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

const ll INF = 9223372036854775806 / 2;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N;
    ll A, B, C;
    cin >> N >> A >> B >> C;
    vector<ll> DP(N + 1, INF);

    DP[1] = A;
    for (int k = 2; k <= N; ++k) {
        for (int i = 1; i <= k / 2; ++i) {
            ll currentCost = DP[i] + DP[k - i] + B;
            if (currentCost < DP[k]) {
                DP[k] = currentCost;
            }
        }

        for (int i = 2; i * i <= k; ++i) {
            if (k % i == 0) {
                ll currentCost = DP[i] + DP[k / i] + C;
                if (currentCost < DP[k]) {
                    DP[k] = currentCost;
                }
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        cout << DP[i] << (i == N ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
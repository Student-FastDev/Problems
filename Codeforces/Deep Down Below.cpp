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

void solveTestCase() {
    int N;
    cin >> N;

    vector<pll> caveList;
    caveList.reserve(N);
    for (int i = 0; i < N; ++i) {
        int K;
        cin >> K;
        ll maximumRequirement = 0;
        for (int j = 0; j < K; ++j) {
            ll A;
            cin >> A;
            maximumRequirement = max(maximumRequirement, A - j + 1);
        }
        caveList.push_back({maximumRequirement, (ll)K});
    }

    sort(all(caveList));

    ll minimumInitialPower = 0;
    ll currentPowerGain = 0;
    for (auto& currentCave : caveList) {
        minimumInitialPower = max(minimumInitialPower, currentCave.first - currentPowerGain);
        currentPowerGain += currentCave.second;
    }

    cout << minimumInitialPower << endl;
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
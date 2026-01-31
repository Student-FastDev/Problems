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
    vector<pll> costGroups;
    ll totalFigures = 0;
    for (int i = 0; i < N; ++i) {
        ll K, C;
        cin >> K >> C;
        costGroups.push_back({C, K});
        totalFigures += K;
    }
    sort(all(costGroups));

    int T;
    cin >> T;
    vector<ll> P(T);
    for (int i = 0; i < T; ++i) cin >> P[i];

    vector<pll> multiplierGroups;
    ll currentCovered = 0;
    for (int i = 0; i < T; ++i) {
        ll currentLimit = P[i];
        if (currentLimit > totalFigures) currentLimit = totalFigures;
        ll countToAdd = currentLimit - currentCovered;
        if (countToAdd > 0) {
            multiplierGroups.push_back({i + 1, countToAdd});
            currentCovered += countToAdd;
        }
        if (currentCovered == totalFigures) break;
    }

    if (currentCovered < totalFigures) {
        multiplierGroups.push_back({T + 1, totalFigures - currentCovered});
    }

    ll maxPoints = 0;
    int costIndex = 0;
    int multiplierIndex = 0;

    while (costIndex < size(costGroups) && multiplierIndex < size(multiplierGroups)) {
        ll takeAmount = min(costGroups[costIndex].second, multiplierGroups[multiplierIndex].second);
        maxPoints += takeAmount * costGroups[costIndex].first * multiplierGroups[multiplierIndex].first;
        
        costGroups[costIndex].second -= takeAmount;
        multiplierGroups[multiplierIndex].second -= takeAmount;
        
        if (costGroups[costIndex].second == 0) costIndex++;
        if (multiplierGroups[multiplierIndex].second == 0) multiplierIndex++;
    }

    cout << maxPoints << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
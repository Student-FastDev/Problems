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
    int N, M;
    cin >> N >> M;
    vector<ll> paintLimitArray(M);
    for (int i = 0; i < M; ++i) {
        cin >> paintLimitArray[i];
    }
    sort(all(paintLimitArray));

    ll weightedSum = 0;
    ll totalPairs = 0;

    for (int i = 0; i < M; ++i) {
        ll currentValue = paintLimitArray[i];
        ll targetValue = N - currentValue;
        auto boundIterator = lower_bound(all(paintLimitArray), targetValue);
        ll validCount = paintLimitArray.end() - boundIterator;

        if (2 * currentValue >= N) {
            validCount--;
        }

        ll effectiveValue = (currentValue == N ? N - 1 : currentValue);
        weightedSum += validCount * effectiveValue;
        totalPairs += validCount;
    }

    cout << 2 * weightedSum - totalPairs * (N - 1) << endl;
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
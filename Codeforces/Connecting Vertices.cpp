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
const ll MAX_N = 505;
const ll MOD = 1e9+7; // 998244353

int N;
int adjacencyMatrix[MAX_N][MAX_N];
ll treesMemo[MAX_N][MAX_N];
ll treesWithEdgeMemo[MAX_N][MAX_N];

ll countTrees(int i, int j);

ll countTreesWithEdge(int i, int j) {
    if (i >= j) return 0;
    if (treesWithEdgeMemo[i][j] != -1) return treesWithEdgeMemo[i][j];

    if (adjacencyMatrix[i][j] == 0) {
        return treesWithEdgeMemo[i][j] = 0;
    }

    ll totalWays = 0;
    for (int k = i; k < j; ++k) {
        ll leftWays = countTrees(i, k);
        ll rightWays = countTrees(k + 1, j);
        totalWays = (totalWays + leftWays * rightWays) % MOD;
    }
    return treesWithEdgeMemo[i][j] = totalWays;
}

ll countTrees(int i, int j) {
    if (i == j) return 1;
    if (i > j) return 0;
    if (treesMemo[i][j] != -1) return treesMemo[i][j];

    ll totalWays = 0;
    for (int k = i + 1; k <= j; ++k) {
        ll waysWithEdge = countTreesWithEdge(i, k);
        if (waysWithEdge == 0) continue;
        ll restWays = countTrees(k, j);
        totalWays = (totalWays + waysWithEdge * restWays) % MOD;
    }
    return treesMemo[i][j] = totalWays;
}

void solveTestCase() {
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> adjacencyMatrix[i][j];
        }
    }

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            treesMemo[i][j] = -1;
            treesWithEdgeMemo[i][j] = -1;
        }
    }

    cout << countTrees(1, N) << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
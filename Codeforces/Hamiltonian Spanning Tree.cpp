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

ll N, X, Y;
vector<vector<int>> neighbourList;

array<ll, 3> dfs(int u, int p) {
    ll baseSum = 0;
    vector<ll> gainList;
    
    for (int v : neighbourList[u]) {
        if (v == p) continue;
        array<ll, 3> childResult = dfs(v, u);
        ll bestChildOption = max({childResult[0], childResult[1], childResult[2]});
        baseSum += bestChildOption;
        
        ll connectionValue = 1 + max(childResult[0], childResult[1]);
        gainList.push_back(connectionValue - bestChildOption);
    }
    
    sort(all(gainList), greater<ll>());
    
    array<ll, 3> currentResult;
    currentResult[0] = baseSum;
    currentResult[1] = -1e15;
    currentResult[2] = -1e15;
    
    if (size(gainList) >= 1) currentResult[1] = baseSum + gainList[0];
    if (size(gainList) >= 2) currentResult[2] = baseSum + gainList[0] + gainList[1];
    
    return currentResult;
}

void solveTestCase() {
    cin >> N >> X >> Y;
    neighbourList.assign(N + 1, vector<int>());
    vector<int> degreeArray(N + 1, 0);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
        degreeArray[u]++;
        degreeArray[v]++;
    }
    
    if (X >= Y) {
        bool isStarGraph = false;
        for (int i = 1; i <= N; ++i) {
            if (degreeArray[i] == N - 1) isStarGraph = true;
        }
        
        if (isStarGraph) cout << X + (ll)(N - 2) * Y << endl;
        else cout << (ll)(N - 1) * Y << endl;
    } else {
        array<ll, 3> dfsResult = dfs(1, 0);
        ll maximumTreeEdges = max({dfsResult[0], dfsResult[1], dfsResult[2]});
        ll finalAnswer = maximumTreeEdges * X + (ll)(N - 1 - maximumTreeEdges) * Y;
        cout << finalAnswer << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
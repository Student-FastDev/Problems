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
const int MAX_NODES = 1000005;

vector<pair<char, int>> adj[MAX_NODES];
int parentOf[MAX_NODES];
bool inS[MAX_NODES];
int globalRank[MAX_NODES];
int minRank[MAX_NODES];
ll minTime[MAX_NODES];
int currentRankGlobal = 0;

void dfsRank(int node) {
    int startRank = currentRankGlobal + 1;
    if (inS[node]) {
        currentRankGlobal++;
        globalRank[node] = currentRankGlobal;
    }
    
    for (auto& edge : adj[node]) {
        dfsRank(edge.second);
    }
    
    if (currentRankGlobal >= startRank) {
        minRank[node] = startRank;
    } else {
        minRank[node] = -1; 
    }
}

void dfsSolve(int node, ll minAncestorVal) {
    if (node == 0) {
        minTime[node] = 0;
    } else {
        ll option1 = minTime[parentOf[node]] + 1;
        minTime[node] = option1;
        
        if (inS[node]) {
            ll option2 = minAncestorVal + globalRank[node] + 1;
            if (option2 < minTime[node]) {
                minTime[node] = option2;
            }
        }
    }
    
    ll nextMinVal = minAncestorVal;
    if (minRank[node] != -1) {
        ll val = minTime[node] - minRank[node];
        if (val < nextMinVal) {
            nextMinVal = val;
        }
    }
    
    for (auto& edge : adj[node]) {
        dfsSolve(edge.second, nextMinVal);
    }
}

void solveTestCase() {
    int N;
    cin >> N;
    
    for (int i = 1; i <= N; ++i) {
        int parentIndex;
        char charToAppend;
        cin >> parentIndex >> charToAppend;
        adj[parentIndex].push_back({charToAppend, i});
        parentOf[i] = parentIndex;
    }
    
    for (int i = 0; i <= N; ++i) {
        if (!adj[i].empty()) {
            sort(all(adj[i]));
        }
    }
    
    int K;
    cin >> K;
    vector<int> targets(K);
    for (int i = 0; i < K; ++i) {
        cin >> targets[i];
        inS[targets[i]] = true;
    }
    
    currentRankGlobal = 0;
    dfsRank(0);
    
    dfsSolve(0, 2e18); 
    
    for (int i = 0; i < K; ++i) {
        cout << minTime[targets[i]] << (i == K - 1 ? "" : " ");
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
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

struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int N) : parent(N + 1), rank(N + 1, 0) {
        for(int i = 0; i <= N; ++i) parent[i] = i;
    }

    int findSet(int x) {
        if(parent[x] != x)
            parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void unionSet(int x, int y) {
        int xRoot = findSet(x);
        int yRoot = findSet(y);
        if(xRoot == yRoot) return;
        if(rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        }
        else {
            parent[yRoot] = xRoot;
            if(rank[xRoot] == rank[yRoot]) rank[xRoot]++;
        }
    }
};

typedef struct DSU DSU;

void solveTestCase() {
    int N, M, R;
    cin >> N >> M >> R;

    vector<pair<int, int>> fEdges(M);
    for(auto &edge : fEdges) {
        cin >> edge.first >> edge.second;
    }

    vector<pair<int, int>> gEdges(R);
    for(auto &edge : gEdges) {
        cin >> edge.first >> edge.second;
    }

    DSU dsuG(N);
    for(auto &[u, v] : gEdges) {
        dsuG.unionSet(u, v);
    }

    vector<int> compG(N + 1);
    for(int v = 1; v <= N; ++v) {
        compG[v] = dsuG.findSet(v);
    }

    int eCross = 0;
    vector<pair<int, int>> fInternalEdges;
    for(auto &[u, v] : fEdges) {
        if(compG[u] != compG[v]) {
            eCross++;
        }
        else {
            fInternalEdges.emplace_back(u, v);
        }
    }

    DSU dsuF(N);
    for(auto &[u, v] : fInternalEdges) {
        dsuF.unionSet(u, v);
    }

    vector<pair<int, int>> gFPairs(N);
    for(int v = 1; v <= N; ++v) {
        gFPairs[v - 1] = {compG[v], dsuF.findSet(v)};
    }

    sort(gFPairs.begin(), gFPairs.end());

    int sumAdditional = 0;
    int currentGComp = -1;
    unordered_set<int> uniqueFComps;
    for(auto &[gComp, fComp] : gFPairs) {
        if(gComp != currentGComp) {
            if(currentGComp != -1) {
                sumAdditional += max(0, (int)size(uniqueFComps) - 1);
            }
            currentGComp = gComp;
            uniqueFComps.clear();
        }
        uniqueFComps.insert(fComp);
    }
    if(currentGComp != -1) {
        sumAdditional += max(0, (int)size(uniqueFComps) - 1);
    }

    int totalOperations = eCross + sumAdditional;
    cout << totalOperations << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }

    return 0;
}

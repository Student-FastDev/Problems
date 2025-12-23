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
    vector<int> dsuParent;
    DSU(int n) {
        dsuParent.resize(n + 1);
        iota(all(dsuParent), 0);
    }
    int findSet(int i) {
        if (dsuParent[i] == i)
            return i;
        return dsuParent[i] = findSet(dsuParent[i]);
    }
    void uniteSets(int i, int j) {
        int rootI = findSet(i);
        int rootJ = findSet(j);
        if (rootI != rootJ) {
            dsuParent[rootI] = rootJ;
        }
    }
};

int N, M;
vector<vector<pii>> neighbourList;
vector<pair<int, int>> edgeList;
vector<int> depthArray;
vector<vector<int>> ancestorTable;
vector<int> timeIn, timeOut;
vector<int> parentEdgeIndex;
int currentTime;
vector<int> differenceArray;

void performDFS(int u, int p, int d) {
    depthArray[u] = d;
    ancestorTable[u][0] = p;
    timeIn[u] = ++currentTime;
    for (int i = 1; i <= 19; ++i) {
        ancestorTable[u][i] = ancestorTable[ancestorTable[u][i - 1]][i - 1];
    }
    for (auto& edge : neighbourList[u]) {
        int v = edge.first;
        int index = edge.second;
        if (v != p) {
            parentEdgeIndex[v] = index;
            performDFS(v, u, d + 1);
        }
    }
    timeOut[u] = currentTime;
}

bool checkAncestor(int u, int v) {
    return timeIn[u] <= timeIn[v] && timeOut[u] >= timeOut[v];
}

int findLCA(int u, int v) {
    if (checkAncestor(u, v)) return u;
    if (checkAncestor(v, u)) return v;
    for (int i = 19; i >= 0; --i) {
        if (!checkAncestor(ancestorTable[u][i], v)) {
            u = ancestorTable[u][i];
        }
    }
    return ancestorTable[u][0];
}

int findKthAncestor(int u, int k) {
    for (int i = 0; i <= 19; ++i) {
        if ((k >> i) & 1) {
            u = ancestorTable[u][i];
        }
    }
    return u;
}

void updateRange(int l, int r, int val) {
    if (l > r) return;
    differenceArray[l] += val;
    differenceArray[r + 1] -= val;
}

void updateSubtree(int u, int val) {
    updateRange(timeIn[u], timeOut[u], val);
}

void updateExceptSubtree(int u, int val) {
    updateRange(1, timeIn[u] - 1, val);
    updateRange(timeOut[u] + 1, N, val);
}

void solveTestCase() {
    cin >> N >> M;
    edgeList.clear();
    edgeList.resize(M + 1);
    neighbourList.assign(N + 1, vector<pii>());
    
    DSU dsuStructure(N);
    vector<bool> isMSTEdge(M + 1, false);
    
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        edgeList[i] = {u, v};
        if (dsuStructure.findSet(u) != dsuStructure.findSet(v)) {
            dsuStructure.uniteSets(u, v);
            isMSTEdge[i] = true;
            neighbourList[u].push_back({v, i});
            neighbourList[v].push_back({u, i});
        }
    }
    
    depthArray.assign(N + 1, 0);
    ancestorTable.assign(N + 1, vector<int>(20));
    timeIn.assign(N + 1, 0);
    timeOut.assign(N + 1, 0);
    parentEdgeIndex.assign(N + 1, 0);
    currentTime = 0;
    
    performDFS(1, 1, 0);
    
    differenceArray.assign(N + 2, 0);
    
    for (int i = 1; i <= M; ++i) {
        if (isMSTEdge[i]) continue;
        
        int u = edgeList[i].first;
        int v = edgeList[i].second;
        int currentEdgeIndex = i;
        
        int lcaNode = findLCA(u, v);
        
        if (lcaNode == u || lcaNode == v) {
            int ancestorNode = (lcaNode == u) ? u : v;
            int descendantNode = (lcaNode == u) ? v : u;
            
            int childNode = findKthAncestor(descendantNode, depthArray[descendantNode] - depthArray[ancestorNode] - 1);
            
            updateSubtree(childNode, 1);
            updateSubtree(descendantNode, -1);
            
            int weightChild = parentEdgeIndex[childNode];
            if (currentEdgeIndex < weightChild) {
                updateExceptSubtree(childNode, 1);
            }
            
            int weightDescendant = parentEdgeIndex[descendantNode];
            if (currentEdgeIndex < weightDescendant) {
                updateSubtree(descendantNode, 1);
            }
            
        } else {
            updateRange(1, N, 1);
            updateSubtree(u, -1);
            updateSubtree(v, -1);
            
            int weightU = parentEdgeIndex[u];
            if (currentEdgeIndex < weightU) {
                updateSubtree(u, 1);
            }
            
            int weightV = parentEdgeIndex[v];
            if (currentEdgeIndex < weightV) {
                updateSubtree(v, 1);
            }
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        differenceArray[i] += differenceArray[i - 1];
    }
    
    for (int i = 1; i <= N; ++i) {
        cout << (differenceArray[timeIn[i]] == 0 ? '1' : '0');
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
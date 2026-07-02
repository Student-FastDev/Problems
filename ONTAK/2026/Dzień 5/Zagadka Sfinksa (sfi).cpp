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
#define size_of(x)  (x).size()

const ll INF = 1e9+67;
const ll MAX_N = 2e3+67;
const ll MOD = 1e9+7; // 998244353

struct Edge {
    int to;
    int weight;
};

int N, M;
vector<Edge> neighbourList[MAX_N];
vector<Edge> upEdges[MAX_N];
vector<int> treeChildren[MAX_N];

bool isVisited[MAX_N];
int depthArray[MAX_N];
int parentArray[MAX_N];
int DP[MAX_N][2048];

bool foundCycle = false;
vector<int> cyclePath;

void buildDFS(int node, int parent, int depth) {
    depthArray[node] = depth;
    isVisited[node] = true;
    parentArray[node] = parent;
    for(auto& edge : neighbourList[node]) {
        int v = edge.to;
        if(!isVisited[v]) {
            treeChildren[node].push_back(v);
            upEdges[v].push_back({node, edge.weight});
            buildDFS(v, node, depth + 1);
            if(foundCycle) return;
        }
        else {
            if(depthArray[v] < depthArray[node] && v != parent) {
                upEdges[node].push_back({v, edge.weight});
                if(depthArray[node] - depthArray[v] >= 12) {
                    foundCycle = true;
                    int currentNode = node;
                    while(currentNode != v) {
                        cyclePath.push_back(currentNode);
                        currentNode = parentArray[currentNode];
                    }
                    cyclePath.push_back(v);
                    return;
                }
            }
        }
    }
}

int calculateDP(int node, int mask) {
    if(DP[node][mask] != -1) return DP[node][mask];

    int bestValue = INF;
    for(int c = 0; c <= 1; c++) {
        int currentCost = 0;
        for(auto& edge : upEdges[node]) {
            int v = edge.to;
            int currentDistance = depthArray[node] - depthArray[v];
            int neighbourColor = (mask >> (currentDistance - 1)) & 1;
            if(neighbourColor == c) currentCost += edge.weight;
        }
        int newMask = ((mask << 1) | c) & 2047;
        for(int child : treeChildren[node]) currentCost += calculateDP(child, newMask);
        bestValue = min(bestValue, currentCost);
    }
    return DP[node][mask] = bestValue;
}

void solveTestCase() {
    cin >> N >> M;

    ll baseCost = 0;
    for(int i = 0; i < M; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        if(u == v) {
            baseCost += weight;
        } else {
            neighbourList[u].push_back({v, weight});
            neighbourList[v].push_back({u, weight});
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < 2048; j++) {
            DP[i][j] = -1;
        }
    }

    ll finalCost = 0;
    for(int i = 1; i <= N; i++) {
        if(!isVisited[i]) {
            buildDFS(i, 0, 0);
            if(foundCycle) break;
            finalCost += calculateDP(i, 0);
        }
    }

    if(foundCycle) {
        cout << "CYKL" << endl;
        cout << size_of(cyclePath) << endl;
        for(int i = 0; i < size_of(cyclePath); i++) cout << cyclePath[i] << " ";
        cout << endl;
    } else {
        cout << "PODZIAL" << endl;
        cout << finalCost + baseCost << endl;
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
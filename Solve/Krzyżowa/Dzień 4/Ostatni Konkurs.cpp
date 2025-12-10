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
const ll MAX_N = 5 * 1e5 + 1;
const ll MOD = 1e9+7; // 998244353

int neighbourList[MAX_N][2]; 
int nodeDegree[MAX_N];
int nodeParent[MAX_N];
bool visitedComponents[MAX_N];

int findSet(int v) {
    if (v == nodeParent[v]) return v;
    return nodeParent[v] = findSet(nodeParent[v]);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) nodeParent[b] = a;
}

int excludeNeighbours(int u, int v) {
    if (neighbourList[u][0] != 0 && neighbourList[u][0] != v) return neighbourList[u][0];
    if (neighbourList[u][1] != 0 && neighbourList[u][1] != v) return neighbourList[u][1];
    return 0;
}

void replaceNeighbours(int node, int oldValue, int newValue) {
    if (neighbourList[node][0] == oldValue) neighbourList[node][0] = newValue;
    else if (neighbourList[node][1] == oldValue) neighbourList[node][1] = newValue;
}

bool areNeighbours(int u, int v) {
    return (neighbourList[u][0] == v || neighbourList[u][1] == v);
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        nodeParent[i] = i;
        nodeDegree[i] = 0;
        neighbourList[i][0] = 0;
        neighbourList[i][1] = 0;
    }

    for (int k = 0; k < M; ++k) {
        int u, v;
        cin >> u >> v;

        int rootU = findSet(u);
        int rootV = findSet(v);        
        int X = 0, Y = 0;

        if (rootU != rootV) {
            if (nodeDegree[u] > 1 || nodeDegree[v] > 1) {
                cout << "Nie" << endl;
                return;
            }
            X = (neighbourList[u][0] != 0) ? neighbourList[u][0] : neighbourList[u][1];
            Y = (neighbourList[v][0] != 0) ? neighbourList[v][0] : neighbourList[v][1];
            
            unionSet(rootU, rootV);
        } else {
            if (!areNeighbours(u, v)) {
                cout << "Nie" << endl;
                return;
            }
            X = excludeNeighbours(u, v);
            Y = excludeNeighbours(v, u);
        }

        if (X != 0) replaceNeighbours(X, u, v);
        if (Y != 0) replaceNeighbours(Y, v, u);

        neighbourList[u][0] = v; 
        neighbourList[u][1] = Y;
        nodeDegree[u] = 1 + (Y != 0);

        neighbourList[v][0] = u; 
        neighbourList[v][1] = X;
        nodeDegree[v] = 1 + (X != 0);
    }

    cout << "Tak" << endl;

    priority_queue<int, vector<int>, greater<int>> priorityArray;

    for (int i = 1; i <= N; ++i) {
        if (nodeDegree[i] < 2) {
            priorityArray.push(i);
        }
    }

    while (!priorityArray.empty()) {
        int startNode = priorityArray.top();
        priorityArray.pop();

        int componentRoot = findSet(startNode);

        if (visitedComponents[componentRoot]) continue;
        visitedComponents[componentRoot] = true;

        int currentNode = startNode;
        int previousNode = 0;

        while (currentNode != 0) {
            cout << currentNode << endl;
            
            int nextNode = 0;
            if (neighbourList[currentNode][0] != 0 && neighbourList[currentNode][0] != previousNode) nextNode = neighbourList[currentNode][0];
            else if (neighbourList[currentNode][1] != 0 && neighbourList[currentNode][1] != previousNode) nextNode = neighbourList[currentNode][1];
            
            previousNode = currentNode;
            currentNode = nextNode;
        }
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

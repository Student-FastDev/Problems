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

struct Edge {
    int from, to;
};

int N, M, Q;

vector<int> vertexValue;
vector<Edge> edgesArray;
vector<vector<pii>> neighbourList;
vector<int> depthArray;
vector<int> lowFunction;
vector<int> edgeStack;
vector<vector<int>> componentsArray;

vector<int> isVisited;
int visitedToken = 0;

void addVertex(vector<int>& currentComponent, int currentNode) {
    if (isVisited[currentNode] != visitedToken) {
        isVisited[currentNode] = visitedToken;
        currentComponent.push_back(currentNode);
    }
}

void createComponent(int stopEdge) {
    visitedToken++;
    vector<int> currentComponent;

    while (true) {
        int id = edgeStack.back();
        edgeStack.pop_back();

        int u = edgesArray[id].from;
        int currentNode = edgesArray[id].to;

        addVertex(currentComponent, u);
        addVertex(currentComponent, currentNode);
        if (id == stopEdge) break;
    }

    componentsArray.push_back(currentComponent);
}

void tarjanDFS(int currentNode, int parentEdge, int currentDepth) {
    depthArray[currentNode] = currentDepth;
    lowFunction[currentNode] = currentDepth;

    for (auto [to, edgeId] : neighbourList[currentNode]) {
        if (edgeId == parentEdge) continue;

        if (depthArray[to] == -1) {
            edgeStack.push_back(edgeId);
            tarjanDFS(to, edgeId, currentDepth + 1);
            lowFunction[currentNode] = min(lowFunction[currentNode], lowFunction[to]);
            if (lowFunction[to] >= depthArray[currentNode]) createComponent(edgeId);
        } else if (depthArray[to] < depthArray[currentNode]) {
            edgeStack.push_back(edgeId);
            lowFunction[currentNode] = min(lowFunction[currentNode], depthArray[to]);
        }
    }
}

void solveTestCase() {
    cin >> N >> M >> Q;

    vertexValue.assign(N + 1, 0);
    for (int i = 1; i <= N; i++) cin >> vertexValue[i];
    edgesArray.resize(M);
    neighbourList.assign(N + 1, {});

    for (int i = 0; i < M; i++) {
        int u, currentNode;
        cin >> u >> currentNode;
        edgesArray[i] = {u, currentNode};

        neighbourList[u].push_back({currentNode, i});
        neighbourList[currentNode].push_back({u, i});
    }

    depthArray.assign(N + 1, -1);
    lowFunction.assign(N + 1, -1);
    isVisited.assign(N + 1, 0);

    for (int currentNode = 1; currentNode <= N; currentNode++) {
        if (depthArray[currentNode] == -1) tarjanDFS(currentNode, -1, 0);
    }

    int blockCount = (int)size(componentsArray);
    vector<int> componentCount(N + 1, 0);
    int maxTreeNodes = blockCount + N + 67;
    vector<int> nodeWeight(maxTreeNodes, 0);

    for (int i = 0; i < blockCount; i++) {
        int blockNode = i + 1;

        for (int currentNode : componentsArray[i]) {
            componentCount[currentNode]++;
            nodeWeight[blockNode] = max(nodeWeight[blockNode], vertexValue[currentNode]);
        }
    }

    int totalNodes = blockCount;
    vector<int> articulationNode(N + 1, 0);
    vector<int> representationArray(N + 1, 0);

    for (int currentNode = 1; currentNode <= N; currentNode++) {
        if (componentCount[currentNode] > 1) {
            articulationNode[currentNode] = ++totalNodes;
            nodeWeight[articulationNode[currentNode]] = vertexValue[currentNode];
            representationArray[currentNode] = articulationNode[currentNode];
        }
    }

    vector<vector<int>> treeArray(totalNodes + 1);
    for (int i = 0; i < blockCount; i++) {
        int blockNode = i + 1;

        for (int currentNode : componentsArray[i]) {
            if (componentCount[currentNode] > 1) {
                int currentArticulation = articulationNode[currentNode];
                treeArray[blockNode].push_back(currentArticulation);
                treeArray[currentArticulation].push_back(blockNode);
            } else {
                representationArray[currentNode] = blockNode;
            }
        }
    }

    int LOG = 1;
    while ((1 << LOG) <= totalNodes) LOG++;

    vector<int> treeDepth(totalNodes + 1, 0);
    vector<vector<int>> upArray(LOG, vector<int>(totalNodes + 1, 1));
    vector<vector<int>> maxArray(LOG, vector<int>(totalNodes + 1, 0));

    int rootNode = 1;
    vector<int> seenArray(totalNodes + 1, 0);
    vector<int> stackTree;

    stackTree.push_back(rootNode);
    seenArray[rootNode] = 1; 
    upArray[0][rootNode] = rootNode;
    maxArray[0][rootNode] = nodeWeight[rootNode];

    while (!stackTree.empty()) {
        int currentNode = stackTree.back();
        stackTree.pop_back();

        for (int to : treeArray[currentNode]) {
            if (seenArray[to]) continue;
            seenArray[to] = 1;
            treeDepth[to] = treeDepth[currentNode] + 1;
            upArray[0][to] = currentNode;
            maxArray[0][to] = max(nodeWeight[currentNode], nodeWeight[to]);
            stackTree.push_back(to);
        }
    }

    for (int k = 1; k < LOG; k++) {
        for (int currentNode = 1; currentNode <= totalNodes; currentNode++) {
            upArray[k][currentNode] = upArray[k - 1][upArray[k - 1][currentNode]];
            maxArray[k][currentNode] = max(maxArray[k - 1][currentNode], maxArray[k - 1][upArray[k - 1][currentNode]]);
        }
    }

    auto pathMax = [&](int a, int b) {
        int currentAnswer = max(nodeWeight[a], nodeWeight[b]);
        if (treeDepth[a] < treeDepth[b]) swap(a, b);
        int currentDifference = treeDepth[a] - treeDepth[b];

        for (int k = LOG - 1; k >= 0; k--) {
            if ((currentDifference >> k) & 1) {
                currentAnswer = max(currentAnswer, maxArray[k][a]);
                a = upArray[k][a];
            }
        }

        if (a == b) {
            currentAnswer = max(currentAnswer, nodeWeight[a]);
            return currentAnswer;
        }

        for (int k = LOG - 1; k >= 0; k--) {
            if (upArray[k][a] != upArray[k][b]) {
                currentAnswer = max(currentAnswer, maxArray[k][a]);
                currentAnswer = max(currentAnswer, maxArray[k][b]);
                a = upArray[k][a];
                b = upArray[k][b];
            }
        }

        currentAnswer = max(currentAnswer, maxArray[0][a]);
        currentAnswer = max(currentAnswer, maxArray[0][b]);
        return currentAnswer;
    };

    while (Q--) {
        int a, b;
        cin >> a >> b;
        int x = representationArray[a];
        int y = representationArray[b];

        cout << pathMax(x, y) << endl;
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
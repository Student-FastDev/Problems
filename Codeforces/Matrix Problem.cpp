// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o, auto p) -> decltype(p.first, o) { return o << '(' << p.first << ", " << p.second << ')'; }
auto operator<<(auto&o, auto x) -> decltype(x.end(), o) { o << '{'; int i = 2; for (auto e : x)o << (", ") + i << e, i = 0; return o << '}'; }
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;

struct Edge {
    int to;
    int capacity;
    int flow;
    int cost;
    int reverseEdgeIndex;
};

vector<vector<Edge>> neighbourList;
vector<ll> distances;
vector<int> parentNode;
vector<int> parentEdgeIndex;
vector<bool> inQueue;

void addEdge(int U, int V, int capacity, int cost) {
    Edge forwardEdge = {V, capacity, 0, cost, (int)size(neighbourList[V])};
    Edge backwardEdge = {U, 0, 0, -cost, (int)size(neighbourList[U])};
    neighbourList[U].push_back(forwardEdge);
    neighbourList[V].push_back(backwardEdge);
}

bool spfa(int S, int T, int& flow, ll& cost, int numberOfNodes) {
    distances.assign(numberOfNodes, INF);
    parentNode.assign(numberOfNodes, -1);
    parentEdgeIndex.assign(numberOfNodes, -1);
    inQueue.assign(numberOfNodes, false);
    queue<int> Q;

    distances[S] = 0;
    Q.push(S);
    inQueue[S] = true;

    while (!Q.empty()) {
        int U = Q.front();
        Q.pop();
        inQueue[U] = false;

        for (int i = 0; i < (int)size(neighbourList[U]); ++i) {
            Edge& currentEdge = neighbourList[U][i];
            if (currentEdge.capacity - currentEdge.flow > 0 && distances[currentEdge.to] > distances[U] + currentEdge.cost) {
                distances[currentEdge.to] = distances[U] + currentEdge.cost;
                parentNode[currentEdge.to] = U;
                parentEdgeIndex[currentEdge.to] = i;
                if (!inQueue[currentEdge.to]) {
                    Q.push(currentEdge.to);
                    inQueue[currentEdge.to] = true;
                }
            }
        }
    }

    if (distances[T] == INF) return false;

    int flowPushed = 1e9;
    int currentNode = T;
    while (currentNode != S) {
        int previousNode = parentNode[currentNode];
        int edgeIndex = parentEdgeIndex[currentNode];
        flowPushed = min(flowPushed, neighbourList[previousNode][edgeIndex].capacity - neighbourList[previousNode][edgeIndex].flow);
        currentNode = previousNode;
    }

    flow += flowPushed;
    cost += (ll)flowPushed * distances[T];
    currentNode = T;
    while (currentNode != S) {
        int previousNode = parentNode[currentNode];
        int edgeIndex = parentEdgeIndex[currentNode];
        neighbourList[previousNode][edgeIndex].flow += flowPushed;
        int reverseEdgeIndex = neighbourList[previousNode][edgeIndex].reverseEdgeIndex;
        neighbourList[currentNode][reverseEdgeIndex].flow -= flowPushed;
        currentNode = previousNode;
    }

    return true;
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> matrixGrid(N, vector<int>(M));
    ll initialOnes = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrixGrid[i][j];
            if (matrixGrid[i][j] == 1) initialOnes++;
        }
    }

    vector<int> targetRowSums(N);
    ll sumA = 0;
    for (int i = 0; i < N; ++i) {
        cin >> targetRowSums[i];
        sumA += targetRowSums[i];
    }

    vector<int> targetColSums(M);
    ll sumB = 0;
    for (int i = 0; i < M; ++i) {
        cin >> targetColSums[i];
        sumB += targetColSums[i];
    }

    if (sumA != sumB) {
        cout << -1 << endl;
        return;
    }

    int sourceNode = 0;
    int sinkNode = N + M + 1;
    int numberOfNodes = N + M + 2;

    neighbourList.assign(numberOfNodes, vector<Edge>());

    for (int i = 0; i < N; ++i) {
        addEdge(sourceNode, i + 1, targetRowSums[i], 0);
    }

    for (int j = 0; j < M; ++j) {
        addEdge(N + 1 + j, sinkNode, targetColSums[j], 0);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int edgeCost = (matrixGrid[i][j] == 1 ? -1 : 1);
            addEdge(i + 1, N + 1 + j, 1, edgeCost);
        }
    }

    int maxFlow = 0;
    ll minCost = 0;
    while (spfa(sourceNode, sinkNode, maxFlow, minCost, numberOfNodes));

    if (maxFlow != sumA) {
        cout << -1 << endl;
    } else {
        cout << initialOnes + minCost << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    solveTestCase();

    return 0;
}
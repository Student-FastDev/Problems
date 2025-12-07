// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

struct DSU {
    vector<int> parentArray;
    vector<int> componentSize;
    int componentCount;
    vector<pair<int, int>> rollbackHistory;

    DSU(int N) {
        parentArray.resize(N + 1);
        iota(all(parentArray), 0);
        componentSize.assign(N + 1, 1);
        componentCount = N;
    }

    int find(int nodeIndex) {
        while (nodeIndex != parentArray[nodeIndex]) nodeIndex = parentArray[nodeIndex];
        return nodeIndex;
    }

    bool unite(int nodeU, int nodeV) {
        int rootU = find(nodeU);
        int rootV = find(nodeV);
        if (rootU != rootV) {
            if (componentSize[rootU] < componentSize[rootV]) swap(rootU, rootV);
            parentArray[rootV] = rootU;
            componentSize[rootU] += componentSize[rootV];
            componentCount--;
            rollbackHistory.push_back({rootV, rootU});
            return true;
        }
        rollbackHistory.push_back({0, 0});
        return false;
    }

    void rollback(int snapshotIndex) {
        while ((int)size(rollbackHistory) > snapshotIndex) {
            auto [childNode, parentNode] = rollbackHistory.back();
            rollbackHistory.pop_back();
            if (childNode != 0) {
                parentArray[childNode] = childNode;
                componentSize[parentNode] -= componentSize[childNode];
                componentCount++;
            }
        }
    }
};

struct Update {
    int U, V;
    int updateType;
};

const int MAX_Q = 400005;
vector<Update> segmentTree[4 * MAX_Q];

void addUpdate(int currentNode, int rangeStart, int rangeEnd, int queryLeft, int queryRight, Update updateOperation) {
    if (queryLeft > rangeEnd || queryRight < rangeStart) return;
    if (queryLeft <= rangeStart && rangeEnd <= queryRight) {
        segmentTree[currentNode].push_back(updateOperation);
        return;
    }
    int midPoint = (rangeStart + rangeEnd) / 2;
    addUpdate(currentNode * 2, rangeStart, midPoint, queryLeft, queryRight, updateOperation);
    addUpdate(currentNode * 2 + 1, midPoint + 1, rangeEnd, queryLeft, queryRight, updateOperation);
}

DSU* dsuA;
DSU* dsuUnion;
vector<int> answersArray;

void solve(int currentNode, int rangeStart, int rangeEnd) {
    int snapshotA = size(dsuA->rollbackHistory);
    int snapshotUnion = size(dsuUnion->rollbackHistory);

    for (const auto& updateOperation : segmentTree[currentNode]) {
        if (updateOperation.updateType == 0) {
            dsuA->unite(updateOperation.U, updateOperation.V);
            dsuUnion->unite(updateOperation.U, updateOperation.V);
        } else {
            dsuUnion->unite(updateOperation.U, updateOperation.V);
        }
    }

    if (rangeStart == rangeEnd) {
        answersArray[rangeStart] = dsuA->componentCount - dsuUnion->componentCount;
    } else {
        int midPoint = (rangeStart + rangeEnd) / 2;
        solve(currentNode * 2, rangeStart, midPoint);
        solve(currentNode * 2 + 1, midPoint + 1, rangeEnd);
    }

    dsuA->rollback(snapshotA);
    dsuUnion->rollback(snapshotUnion);
}

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;

    map<pair<int, int>, int> activeA;
    map<pair<int, int>, int> activeB;

    for (int i = 1; i <= Q; ++i) {
        char operationType;
        int U, V;
        cin >> operationType >> U >> V;
        if (U > V) swap(U, V);
        pair<int, int> edgePair = {U, V};

        if (operationType == 'A') {
            if (activeA.count(edgePair)) {
                int startTime = activeA[edgePair];
                addUpdate(1, 1, Q, startTime, i - 1, {U, V, 0});
                activeA.erase(edgePair);
            } else {
                activeA[edgePair] = i;
            }
        } else {
            if (activeB.count(edgePair)) {
                int startTime = activeB[edgePair];
                addUpdate(1, 1, Q, startTime, i - 1, {U, V, 1});
                activeB.erase(edgePair);
            } else {
                activeB[edgePair] = i;
            }
        }
    }

    for (auto const& [edgePair, startTime] : activeA) {
        addUpdate(1, 1, Q, startTime, Q, {edgePair.first, edgePair.second, 0});
    }
    for (auto const& [edgePair, startTime] : activeB) {
        addUpdate(1, 1, Q, startTime, Q, {edgePair.first, edgePair.second, 1});
    }

    dsuA = new DSU(N);
    dsuUnion = new DSU(N);
    answersArray.resize(Q + 1);

    solve(1, 1, Q);

    for (int i = 1; i <= Q; ++i) {
        cout << answersArray[i] << endl;
    }

    delete dsuA;
    delete dsuUnion;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
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

const int MAX_ARRAY_SIZE = 100005;

struct Edge {
    int U, V, W, id;
};

struct DSU {
    vector<int> parentArray;
    vector<ll> sizeArray;
    DSU(int N) {
        parentArray.resize(N + 1);
        iota(all(parentArray), 0);
        sizeArray.assign(N + 1, 1);
    }
    int find(int I) {
        if (parentArray[I] == I)
            return I;
        return parentArray[I] = find(parentArray[I]);
    }
    void unite(int I, int J) {
        int rootI = find(I);
        int rootJ = find(J);
        if (rootI != rootJ) {
            if (sizeArray[rootI] < sizeArray[rootJ])
                swap(rootI, rootJ);
            parentArray[rootJ] = rootI;
            sizeArray[rootI] += sizeArray[rootJ];
        }
    }
    ll getSize(int I) {
        return sizeArray[find(I)];
    }
};

vector<pii> neighbourList[MAX_ARRAY_SIZE];
ll answerArray[MAX_ARRAY_SIZE];
bool visitedArray[MAX_ARRAY_SIZE];

ll dfsCompute(int U, int P, ll totalSize, DSU& dsuSet) {
    ll currentSz = dsuSet.getSize(U);
    for (auto& edge : neighbourList[U]) {
        int V = edge.first;
        int id = edge.second;
        if (V != P) {
            ll childSz = dfsCompute(V, U, totalSize, dsuSet);
            answerArray[id] = 2 * childSz * (totalSize - childSz);
            currentSz += childSz;
        }
    }
    return currentSz;
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<Edge> edgeList(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        cin >> edgeList[i].U >> edgeList[i].V >> edgeList[i].W;
        edgeList[i].id = i + 1;
    }

    sort(all(edgeList), [](const Edge& A, const Edge& B) {
        return A.W < B.W;
    });

    DSU dsuSet(N);

    int edgeIndex = 0;
    while (edgeIndex < N - 1) {
        int j = edgeIndex;
        while (j < N - 1 && edgeList[j].W == edgeList[edgeIndex].W) {
            j++;
        }

        vector<int> currentNodes;
        for (int k = edgeIndex; k < j; ++k) {
            int U = dsuSet.find(edgeList[k].U);
            int V = dsuSet.find(edgeList[k].V);
            neighbourList[U].push_back({V, edgeList[k].id});
            neighbourList[V].push_back({U, edgeList[k].id});
            currentNodes.push_back(U);
            currentNodes.push_back(V);
        }

        sort(all(currentNodes));
        currentNodes.erase(unique(all(currentNodes)), currentNodes.end());

        for (int node : currentNodes) visitedArray[node] = false;

        for (int node : currentNodes) {
            if (!visitedArray[node]) {
                visitedArray[node] = true;
                vector<int> componentNodes;
                componentNodes.push_back(node);
                ll totalSize = 0;

                int head = 0;
                while (head < size(componentNodes)) {
                    int curr = componentNodes[head++];
                    totalSize += dsuSet.getSize(curr);
                    for (auto& edge : neighbourList[curr]) {
                        int neighbor = edge.first;
                        if (!visitedArray[neighbor]) {
                            visitedArray[neighbor] = true;
                            componentNodes.push_back(neighbor);
                        }
                    }
                }

                dfsCompute(node, -1, totalSize, dsuSet);
            }
        }

        for (int node : currentNodes) {
            neighbourList[node].clear();
        }

        for (int k = edgeIndex; k < j; ++k) {
            dsuSet.unite(edgeList[k].U, edgeList[k].V);
        }

        edgeIndex = j;
    }

    ll maxTrees = 0;
    for (int i = 1; i < N; ++i) maxTrees = max(maxTrees, answerArray[i]);

    vector<int> bestRoads;
    for (int i = 1; i < N; ++i) {
        if (answerArray[i] == maxTrees) {
            bestRoads.push_back(i);
        }
    }

    cout << maxTrees << " " << size(bestRoads) << endl;
    for (int i = 0; i < size(bestRoads); ++i) {
        cout << bestRoads[i] << (i == size(bestRoads) - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
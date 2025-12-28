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

int N, M, Q;
vector<vector<int>> grid;

struct Node {
    int componentCount;
    vector<int> leftIds;
    vector<int> rightIds;
};

vector<Node> tree;

Node makeLeaf(int col) {
    Node node;
    node.leftIds.resize(N);
    node.rightIds.resize(N);
    int nextComponentId = 0;
    for (int i = 0; i < N; ++i) {
        if (i > 0 && grid[i][col] == grid[i - 1][col]) {
            node.leftIds[i] = node.leftIds[i - 1];
        } else {
            node.leftIds[i] = ++nextComponentId;
        }
        node.rightIds[i] = node.leftIds[i];
    }
    node.componentCount = nextComponentId;
    return node;
}

Node mergeNodes(const Node& leftNode, const Node& rightNode, int midCol) {
    Node resultNode;
    resultNode.componentCount = leftNode.componentCount + rightNode.componentCount;

    int maxLeftId = 0;
    for (int x : leftNode.leftIds) maxLeftId = max(maxLeftId, x);
    for (int x : leftNode.rightIds) maxLeftId = max(maxLeftId, x);

    static int parentArray[100];
    int limit = maxLeftId + 2 * N + 5;
    if (limit > 95) limit = 95;

    for (int i = 0; i <= limit; ++i) parentArray[i] = i;

    auto findSetRepresentative = [&](int i) {
        int root = i;
        while (root != parentArray[root]) root = parentArray[root];
        int curr = i;
        while (curr != root) {
            int next = parentArray[curr];
            parentArray[curr] = root;
            curr = next;
        }
        return root;
    };

    auto uniteSets = [&](int i, int j) {
        i = findSetRepresentative(i);
        j = findSetRepresentative(j);
        if (i != j) {
            parentArray[i] = j;
            return true;
        }
        return false;
    };

    for (int i = 0; i < N; ++i) {
        if (grid[i][midCol] == grid[i][midCol + 1]) {
            int u = leftNode.rightIds[i];
            int v = rightNode.leftIds[i] + maxLeftId;
            if (uniteSets(u, v)) {
                resultNode.componentCount--;
            }
        }
    }

    vector<int> rootLeftIds(N), rootRightIds(N);
    for (int i = 0; i < N; ++i) rootLeftIds[i] = findSetRepresentative(leftNode.leftIds[i]);
    for (int i = 0; i < N; ++i) rootRightIds[i] = findSetRepresentative(rightNode.rightIds[i] + maxLeftId);

    static int idMapping[100];
    for (int i = 0; i <= limit; ++i) idMapping[i] = 0;

    int nextComponentId = 0;
    resultNode.leftIds.resize(N);
    resultNode.rightIds.resize(N);

    for (int i = 0; i < N; ++i) {
        if (idMapping[rootLeftIds[i]] == 0) idMapping[rootLeftIds[i]] = ++nextComponentId;
        resultNode.leftIds[i] = idMapping[rootLeftIds[i]];
    }
    for (int i = 0; i < N; ++i) {
        if (idMapping[rootRightIds[i]] == 0) idMapping[rootRightIds[i]] = ++nextComponentId;
        resultNode.rightIds[i] = idMapping[rootRightIds[i]];
    }

    return resultNode;
}

void buildTree(int nodeIndex, int startRange, int endRange) {
    if (startRange == endRange) {
        tree[nodeIndex] = makeLeaf(startRange);
    } else {
        int mid = (startRange + endRange) / 2;
        buildTree(2 * nodeIndex, startRange, mid);
        buildTree(2 * nodeIndex + 1, mid + 1, endRange);
        tree[nodeIndex] = mergeNodes(tree[2 * nodeIndex], tree[2 * nodeIndex + 1], mid);
    }
}

Node queryTree(int nodeIndex, int startRange, int endRange, int queryL, int queryR) {
    if (queryR < startRange || endRange < queryL) return {0, {}, {}};
    if (queryL <= startRange && endRange <= queryR) return tree[nodeIndex];

    int mid = (startRange + endRange) / 2;
    if (queryR <= mid) return queryTree(2 * nodeIndex, startRange, mid, queryL, queryR);
    if (queryL > mid) return queryTree(2 * nodeIndex + 1, mid + 1, endRange, queryL, queryR);

    Node leftChildNode = queryTree(2 * nodeIndex, startRange, mid, queryL, queryR);
    Node rightChildNode = queryTree(2 * nodeIndex + 1, mid + 1, endRange, queryL, queryR);
    return mergeNodes(leftChildNode, rightChildNode, mid);
}

void solveTestCase() {
    cin >> N >> M >> Q;
    grid.assign(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    tree.resize(4 * M);
    buildTree(1, 0, M - 1);

    for (int i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << queryTree(1, 0, M - 1, l, r).componentCount << endl;
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
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
mt19937 randomNumberGenerator((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 1e18;

struct Node {
    ll maxPrefix;
    ll maxValue;
    ll minConstant;
    ll maxConstant;
    ll lazyConstant;
};

vector<Node> segmentTree;
vector<ll> prefixArray;
int treeSize;

void push(int nodeIndex, int leftRange, int rightRange) {
    if (segmentTree[nodeIndex].lazyConstant == -INF) return;
    ll value = segmentTree[nodeIndex].lazyConstant;

    segmentTree[2 * nodeIndex + 1].lazyConstant = value;
    segmentTree[2 * nodeIndex + 1].minConstant = value;
    segmentTree[2 * nodeIndex + 1].maxConstant = value;
    segmentTree[2 * nodeIndex + 1].maxValue = value + segmentTree[2 * nodeIndex + 1].maxPrefix;

    segmentTree[2 * nodeIndex + 2].lazyConstant = value;
    segmentTree[2 * nodeIndex + 2].minConstant = value;
    segmentTree[2 * nodeIndex + 2].maxConstant = value;
    segmentTree[2 * nodeIndex + 2].maxValue = value + segmentTree[2 * nodeIndex + 2].maxPrefix;

    segmentTree[nodeIndex].lazyConstant = -INF;
}

void pull(int nodeIndex) {
    segmentTree[nodeIndex].maxPrefix = max(segmentTree[2 * nodeIndex + 1].maxPrefix, segmentTree[2 * nodeIndex + 2].maxPrefix);
    segmentTree[nodeIndex].maxValue = max(segmentTree[2 * nodeIndex + 1].maxValue, segmentTree[2 * nodeIndex + 2].maxValue);
    segmentTree[nodeIndex].minConstant = segmentTree[2 * nodeIndex + 1].minConstant;
    segmentTree[nodeIndex].maxConstant = segmentTree[2 * nodeIndex + 2].maxConstant;
}

void build(int nodeIndex, int leftRange, int rightRange) {
    segmentTree[nodeIndex].lazyConstant = -INF;
    if (rightRange - leftRange == 1) {
        if (leftRange < size(prefixArray)) {
            segmentTree[nodeIndex].maxPrefix = prefixArray[leftRange];
        } else {
            segmentTree[nodeIndex].maxPrefix = -INF;
        }
        segmentTree[nodeIndex].minConstant = -INF;
        segmentTree[nodeIndex].maxConstant = -INF;
        segmentTree[nodeIndex].maxValue = -INF;
        return;
    }
    int midIndex = (leftRange + rightRange) / 2;
    build(2 * nodeIndex + 1, leftRange, midIndex);
    build(2 * nodeIndex + 2, midIndex, rightRange);
    pull(nodeIndex);
}

void update(int nodeIndex, int leftRange, int rightRange, int queryLeft, int queryRight, ll value) {
    if (leftRange >= queryRight || rightRange <= queryLeft) return;
    if (leftRange >= queryLeft && rightRange <= queryRight) {
        if (segmentTree[nodeIndex].minConstant >= value) return;
        if (segmentTree[nodeIndex].maxConstant < value) {
            segmentTree[nodeIndex].lazyConstant = value;
            segmentTree[nodeIndex].minConstant = value;
            segmentTree[nodeIndex].maxConstant = value;
            segmentTree[nodeIndex].maxValue = value + segmentTree[nodeIndex].maxPrefix;
            return;
        }
    }
    push(nodeIndex, leftRange, rightRange);
    int midIndex = (leftRange + rightRange) / 2;
    update(2 * nodeIndex + 1, leftRange, midIndex, queryLeft, queryRight, value);
    update(2 * nodeIndex + 2, midIndex, rightRange, queryLeft, queryRight, value);
    pull(nodeIndex);
}

ll query(int nodeIndex, int leftRange, int rightRange, int queryLeft, int queryRight) {
    if (leftRange >= queryRight || rightRange <= queryLeft) return -INF;
    if (leftRange >= queryLeft && rightRange <= queryRight) return segmentTree[nodeIndex].maxValue;
    push(nodeIndex, leftRange, rightRange);
    int midIndex = (leftRange + rightRange) / 2;
    return max(query(2 * nodeIndex + 1, leftRange, midIndex, queryLeft, queryRight), query(2 * nodeIndex + 2, midIndex, rightRange, queryLeft, queryRight));
}

vector<ll> computeNext(int M, const vector<ll>& arrayA, const vector<ll>& previousS, const vector<ll>& previousE) {
    prefixArray.assign(M + 1, 0);
    for (int i = 0; i < M; ++i) prefixArray[i + 1] = prefixArray[i] + arrayA[i];

    treeSize = 1;
    while (treeSize <= M) treeSize *= 2;
    segmentTree.resize(2 * treeSize);

    vector<ll> tempPrefix(treeSize, -INF);
    for (int i = 0; i < M; ++i) tempPrefix[i] = prefixArray[i + 1];

    auto oldPrefixArray = prefixArray;
    prefixArray.clear();
    for (auto element : tempPrefix) prefixArray.push_back(element);

    build(0, 0, treeSize);

    vector<ll> currentS(M + 1, -INF);

    for (int L = M; L >= 1; --L) {
        ll updateValue = -INF;
        if (L + 1 <= M) updateValue = max(updateValue, previousS[L + 1]);
        if (L <= M) updateValue = max(updateValue, previousE[L]);

        if (updateValue > -INF) {
            if (L < M) {
                update(0, 0, treeSize, L, M, updateValue);
            }
        }

        ll result = query(0, 0, treeSize, L - 1, M);
        if (result > -INF) {
            currentS[L] = result - oldPrefixArray[L - 1];
        }
    }
    return currentS;
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    vector<vector<ll>> matrixA(N, vector<ll>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrixA[i][j];
        }
    }

    vector<ll> stateS(M + 1, -INF), stateE(M + 1, -INF);
    {
        vector<ll> prefix(M + 1, 0);
        for (int i = 0; i < M; ++i) prefix[i + 1] = prefix[i] + matrixA[0][i];

        vector<ll> suffixMax(M + 2, -INF);
        for (int i = M; i >= 1; --i) suffixMax[i] = max(suffixMax[i + 1], prefix[i]);
        for (int i = 1; i <= M; ++i) stateS[i] = suffixMax[i] - prefix[i - 1];

        ll minPrefix = 0;
        for (int i = 1; i <= M; ++i) {
            stateE[i] = prefix[i] - minPrefix;
            minPrefix = min(minPrefix, prefix[i]);
        }
    }

    for (int i = 1; i < N; ++i) {
        vector<ll> nextS = computeNext(M, matrixA[i], stateS, stateE);

        vector<ll> reversedA = matrixA[i];
        reverse(all(reversedA));
        vector<ll> reversedS = stateS;
        vector<ll> reversedE = stateE;
        reverse(reversedS.begin() + 1, reversedS.end());
        reverse(reversedE.begin() + 1, reversedE.end());
        swap(reversedS, reversedE);

        vector<ll> nextE_rev = computeNext(M, reversedA, reversedS, reversedE);

        vector<ll> nextE = nextE_rev;
        reverse(nextE.begin() + 1, nextE.end());

        stateS = nextS;
        stateE = nextE;
    }

    ll answer = -INF;
    for (int i = 1; i <= M; ++i) answer = max(answer, stateS[i]);
    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solveTestCase();
    }
    return 0;
}
// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second<<')';}
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

struct Node {
    ll maxG, maxF, bestScore;
    ll lazyG, lazyF;
    Node() : maxG(LLONG_MIN), maxF(LLONG_MIN), bestScore(LLONG_MIN), lazyG(0), lazyF(0) {}
};

struct SegmentTree {
    int N;
    vector<Node> segmentArray;
    SegmentTree(int n) : N(n) {
        segmentArray.resize(4 * (N + 1));
    }

    Node mergeNodes(const Node& leftNode, const Node& rightNode) {
        Node resultNode;
        resultNode.maxG      = max(leftNode.maxG, rightNode.maxG);
        resultNode.maxF      = max(leftNode.maxF, rightNode.maxF);
        resultNode.bestScore = max({leftNode.bestScore, rightNode.bestScore, leftNode.maxG + rightNode.maxF});
        return resultNode;
    }

    void applyValues(int nodeIndex, ll valueG, ll valueF) {
        Node& nodeReference = segmentArray[nodeIndex];
        nodeReference.maxG      += valueG;
        nodeReference.maxF      += valueF;
        nodeReference.bestScore += valueG + valueF;
        nodeReference.lazyG     += valueG;
        nodeReference.lazyF     += valueF;
    }

    void pushValues(int nodeIndex) {
        ll lazyG = segmentArray[nodeIndex].lazyG;
        ll lazyF = segmentArray[nodeIndex].lazyF;
        if(lazyG != 0 || lazyF != 0) {
            applyValues(nodeIndex << 1,   lazyG, lazyF);
            applyValues(nodeIndex << 1 | 1, lazyG, lazyF);
            segmentArray[nodeIndex].lazyG = 0;
            segmentArray[nodeIndex].lazyF = 0;
        }
    }

    void buildTree(int nodeIndex, int leftRange, int rightRange, const vector<ll>& D, const vector<ll>& E) {
        if(leftRange == rightRange) {
            segmentArray[nodeIndex].maxG      = D[leftRange - 1];
            segmentArray[nodeIndex].maxF      = E[leftRange];
            segmentArray[nodeIndex].bestScore = D[leftRange - 1] + E[leftRange];
        }
        else {
            int middleValue = (leftRange + rightRange) / 2;
            buildTree(nodeIndex << 1,   leftRange, middleValue, D, E);
            buildTree(nodeIndex << 1 | 1, middleValue + 1, rightRange, D, E);
            segmentArray[nodeIndex] = mergeNodes(segmentArray[nodeIndex << 1], segmentArray[nodeIndex << 1 | 1]);
        }
    }

    void updateTree(int nodeIndex, int leftRange, int rightRange,
                    int expectedLeft, int expectedRight,
                    ll valueG, ll valueF) {
        if(expectedRight < leftRange || expectedLeft > rightRange) return;
        if(leftRange >= expectedLeft && rightRange <= expectedRight) {
            applyValues(nodeIndex, valueG, valueF);
            return;
        }
        pushValues(nodeIndex);
        int middleValue = (leftRange + rightRange) / 2;
        updateTree(nodeIndex << 1,   leftRange, middleValue, expectedLeft, expectedRight, valueG, valueF);
        updateTree(nodeIndex << 1 | 1, middleValue + 1, rightRange, expectedLeft, expectedRight, valueG, valueF);
        segmentArray[nodeIndex] = mergeNodes(segmentArray[nodeIndex << 1], segmentArray[nodeIndex << 1 | 1]);
    }

    ll queryTree() {
        return segmentArray[1].bestScore;
    }
};

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N+1), B(N+1), C(N+2);
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) cin >> B[i];
    for(int i = 1; i <= N; i++) cin >> C[i];

    vector<ll> prefixA(N+1), prefixB(N+1), suffixC(N+2);
    prefixA[0] = prefixB[0] = 0;
    for(int i = 1; i <= N; i++){
        prefixA[i] = prefixA[i-1] + A[i];
        prefixB[i] = prefixB[i-1] + B[i];
    }
    suffixC[N+1] = 0;
    for(int i = N; i >= 1; i--){
        suffixC[i] = suffixC[i+1] + C[i];
    }

    vector<ll> D(N+1), E(N+1);
    D[0] = 0;
    for(int k = 1; k <= N; k++){
        D[k] = prefixA[k] - prefixB[k];
        E[k] = prefixB[k] + suffixC[k+1];
    }

    SegmentTree answerTree(N);
    answerTree.buildTree(1, 1, N, D, E);

    while(Q--){
        int T, changePosition;
        ll changeValue;
        cin >> T >> changePosition >> changeValue;
        if(T == 1){
            ll deltaValue = changeValue - A[changePosition];
            A[changePosition] = changeValue;
            if(changePosition < N) {
                answerTree.updateTree(1, 1, N, changePosition + 1, N, deltaValue, 0);
            }
        } else if(T == 2){
            ll deltaValue = changeValue - B[changePosition];
            B[changePosition] = changeValue;
            if(changePosition < N) {
                answerTree.updateTree(1, 1, N, changePosition + 1, N, -deltaValue, 0);
            }
            answerTree.updateTree(1, 1, N, changePosition, N, 0, deltaValue);
        } else {
            ll deltaValue = changeValue - C[changePosition];
            C[changePosition] = changeValue;
            if(changePosition > 1) {
                answerTree.updateTree(1, 1, N, 1, changePosition - 1, 0, deltaValue);
            }
        }
        cout << answerTree.queryTree() << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}

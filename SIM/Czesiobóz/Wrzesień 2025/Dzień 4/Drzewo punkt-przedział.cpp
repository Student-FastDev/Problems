// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto updateValue)->decltype(updateValue.end(),o){o<<'{';int i=2;for(auto e:updateValue)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(updateValue...)cerr<<"["#updateValue"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(updateValue);
#else
#define LOG(updateValue...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(updateValue)  (updateValue).begin(),(updateValue).end()
#define endl    '\n'
#define size(updateValue)  updateValue.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct SegmentTree {
    int N;
    vector<int> treeArray;

    SegmentTree(int _n) {
        N = _n;
        treeArray.assign(4 * N, 0);
    }

    void buildTree(vector<int> &A, int V, int leftRange, int rightRange) {
        if (leftRange == rightRange) {
            treeArray[V] = A[leftRange];
        } else {
            int middleIndex = (leftRange + rightRange) / 2;
            buildTree(A, V*2, leftRange, middleIndex);
            buildTree(A, V*2+1, middleIndex+1, rightRange);
            treeArray[V] = gcd(treeArray[V*2], treeArray[V*2+1]);
        }
    }

    void buildTree(vector<int> &A) {
        buildTree(A, 1, 0, N-1);
    }

    void updateTree(int V, int leftRange, int rightRange, int positionIndex, int newValue) {
        if (leftRange == rightRange) {
            treeArray[V] = newValue;
        } else {
            int middleIndex = (leftRange + rightRange) / 2;
            if (positionIndex <= middleIndex)
                updateTree(V*2, leftRange, middleIndex, positionIndex, newValue);
            else
                updateTree(V*2+1, middleIndex+1, rightRange, positionIndex, newValue);
            treeArray[V] = gcd(treeArray[V*2], treeArray[V*2+1]);
        }
    }

    void updateTree(int positionIndex, int newValue) {
        updateTree(1, 0, N-1, positionIndex, newValue);
    }

    int queryTree(int V, int leftRange, int rightRange, int L, int R) {
        if (L > R) return 0;
        if (L == leftRange && R == rightRange) return treeArray[V];
        int middleIndex = (leftRange + rightRange) / 2;
        int left = queryTree(V*2, leftRange, middleIndex, L, min(R, middleIndex));
        int right = queryTree(V*2+1, middleIndex+1, rightRange, max(L, middleIndex + 1), R);
        return gcd(left, right);
    }

    int queryTree(int L, int R) {
        return queryTree(1, 0, N-1, L, R);
    }
};


void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    SegmentTree segmentTree(N);
    segmentTree.buildTree(A);

    for (int i = 0; i < Q; i++) {
        char queryType; cin >> queryType;
        if (queryType == 'U') {
            int indexValue, updateValue; cin >> indexValue >> updateValue;
            --indexValue;
            segmentTree.updateTree(indexValue, updateValue);
        } else {
            int l, r; cin >> l >> r;
            --l; --r;
            cout << segmentTree.queryTree(l, r) << endl;
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

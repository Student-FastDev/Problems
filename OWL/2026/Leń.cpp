// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define size(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define endl '\n'

const ll MOD = 1e9 + 7;
const int MAX_N = 1e5;
const ll INF = 1e18 + 67;

struct FenwickTree {
    int N;
    vector<int> treeArray;
    FenwickTree(int N) : N(N), treeArray(N + 1, 0) {}
    
    void addTree(int i, int value) {
        for (; i <= N; i += i & -i) treeArray[i] += value;
    }
    
    int queryTree(int i) {
        int finalResult = 0;
        for (; i > 0; i -= i & -i) finalResult += treeArray[i];
        return finalResult;
    }
};

struct SegmentTree {
    int N;
    vector<ll> treeArray;
    vector<ll> lazyArray;

    SegmentTree(int N) : N(N) {
        treeArray.assign(4 * N + 1, INF);
        lazyArray.assign(4 * N + 1, 0);
    }

    void pushTree(int node) {
        if (lazyArray[node] != 0) {
            
            if (treeArray[2 * node] != INF) {
                treeArray[2 * node] += lazyArray[node];
                lazyArray[2 * node] += lazyArray[node];
            }
            if (treeArray[2 * node + 1] != INF) {
                treeArray[2 * node + 1] += lazyArray[node];
                lazyArray[2 * node + 1] += lazyArray[node];
            }
            lazyArray[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int left, int right, int value) {
        if (left > end || right < start) return;
        if (treeArray[node] == INF) return;

        if (left <= start && end <= right) {
            treeArray[node] += value;
            lazyArray[node] += value;
            return;
        }
        pushTree(node);
        int middleValue = (start + end) / 2;
        updateRange(2 * node, start, middleValue, left, right, value);
        updateRange(2 * node + 1, middleValue + 1, end, left, right, value);
        treeArray[node] = min(treeArray[2 * node], treeArray[2 * node + 1]);
    }

    void setPoints(int node, int start, int end, int idx, ll value) {
        if (start == end) {
            treeArray[node] = value;
            lazyArray[node] = 0;
            return;
        }
        pushTree(node);
        int middleValue = (start + end) / 2;
        if (idx <= middleValue) setPoints(2 * node, start, middleValue, idx, value);
        else setPoints(2 * node + 1, middleValue + 1, end, idx, value);
        treeArray[node] = min(treeArray[2 * node], treeArray[2 * node + 1]);
    }

    ll queryMinimum() {
        return treeArray[1];
    }
};

void solveTestCase() {
    int N;
    cin >> N;

    vector<int> P(N);
    vector<int> positionArray(N + 1);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
        positionArray[P[i]] = i + 1; 
    }

    ll inverseCount = 0;
    FenwickTree firstFenwick(N);
    for (int i = N - 1; i >= 0; --i) {
        inverseCount += firstFenwick.queryTree(P[i] - 1);
        firstFenwick.addTree(P[i], 1);
    }

    SegmentTree firstSegment(N);

    firstSegment.setPoints(1, 1, N, positionArray[1], 0);

    for (int w = 2; w <= N; ++w) {
        ll firstPosition = firstSegment.queryMinimum();

        int secondPosition = positionArray[w];
        if (secondPosition > 1) firstSegment.updateRange(1, 1, N, 1, secondPosition - 1, 1);
        if (secondPosition < N) firstSegment.updateRange(1, 1, N, secondPosition + 1, N, -1);

        firstSegment.setPoints(1, 1, N, secondPosition, firstPosition);
    }

    ll minDelta = firstSegment.queryMinimum();
    cout << inverseCount + minDelta << endl;
    return;
} 

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
}

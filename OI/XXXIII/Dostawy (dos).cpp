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
typedef pair<int,int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MINUS_INF = (ll)-9e18;
const int D_RANGE = 1000000;

struct Fenwick {
    int N;
    vector<int> bitsArray;
    Fenwick(int _N = 0) { initializeFenwick(_N); }
    void initializeFenwick(int _N) { N = _N; bitsArray.assign(N + 1, 0); }
    void updateFenwick(int updateIndex, int updateDelta) {
        updateIndex++;
        for (; updateIndex <= N; updateIndex += updateIndex & -updateIndex) bitsArray[updateIndex] += updateDelta;
    }
    int queryFenwick(int updateIndex) const {
        if (updateIndex < 0) return 0;
        int result = 0;
        updateIndex++;
        for (; updateIndex > 0; updateIndex -= updateIndex & -updateIndex) result += bitsArray[updateIndex];
        return result;
    }
    int rangeQuery(int l, int R) const { if (R < l) return 0; return queryFenwick(R) - queryFenwick(l - 1); }
};

struct SegmentTree {
    struct Node { ll maxVal; ll lazyValue; };
    int N;
    vector<Node> treeArray;
    SegmentTree() { initializeTree(0); }
    void initializeTree(int _N) {
        N = _N;
        treeArray.assign(4 * max(1, N), {MINUS_INF, 0});
    }
    void buildTree(int currentNode, int thisLeft, int thisRight, const vector<ll>& initialValues) {
        treeArray[currentNode].lazyValue = 0;
        if (thisLeft == thisRight) {
            treeArray[currentNode].maxVal = initialValues[thisLeft];
        } else {
            int middleValue = (thisLeft + thisRight) >> 1;
            buildTree(currentNode << 1, thisLeft, middleValue, initialValues);
            buildTree(currentNode << 1 | 1, middleValue + 1, thisRight, initialValues);
            pullNode(currentNode);
        }
    }
    void pushNode(int currentNode) {
        ll L = treeArray[currentNode].lazyValue;
        if (L != 0) {
            for (int u : {currentNode << 1, currentNode << 1 | 1}) {
                treeArray[u].maxVal += L;
                treeArray[u].lazyValue += L;
            }
            treeArray[currentNode].lazyValue = 0;
        }
    }
    void pullNode(int currentNode) {
        treeArray[currentNode].maxVal = max(treeArray[currentNode << 1].maxVal, treeArray[currentNode << 1 | 1].maxVal);
    }
    void rangeUpdate(int currentNode, int thisLeft, int thisRight, int l, int R, ll addValue) {
        if (l > R) return;
        if (l == thisLeft && R == thisRight) {
            treeArray[currentNode].maxVal += addValue;
            treeArray[currentNode].lazyValue += addValue;
            return;
        }
        pushNode(currentNode);
        int middleValue = (thisLeft + thisRight) >> 1;
        rangeUpdate(currentNode << 1, thisLeft, middleValue, l, min(R, middleValue), addValue);
        rangeUpdate(currentNode << 1 | 1, middleValue + 1, thisRight, max(l, middleValue + 1), R, addValue);
        pullNode(currentNode);
    }
    void pointSet(int currentNode, int thisLeft, int thisRight, int setPosition, ll setValue) {
        if (thisLeft == thisRight) {
            treeArray[currentNode].maxVal = setValue;
            treeArray[currentNode].lazyValue = 0;
            return;
        }
        pushNode(currentNode);
        int middleValue = (thisLeft + thisRight) >> 1;
        if (setPosition <= middleValue) pointSet(currentNode << 1, thisLeft, middleValue, setPosition, setValue);
        else pointSet(currentNode << 1 | 1, middleValue + 1, thisRight, setPosition, setValue);
        pullNode(currentNode);
    }
    ll queryMax(int currentNode, int thisLeft, int thisRight, int l, int R) {
        if (l > R) return MINUS_INF;
        if (l <= thisLeft && thisRight <= R) return treeArray[currentNode].maxVal;
        pushNode(currentNode);
        int middleValue = (thisLeft + thisRight) >> 1;
        ll leftMax = queryMax(currentNode << 1, thisLeft, middleValue, l, min(R, middleValue));
        ll rightMax = queryMax(currentNode << 1 | 1, middleValue + 1, thisRight, max(l, middleValue + 1), R);
        return max(leftMax, rightMax);
    }
};

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<string> gridArray(N);
    for (int i = 0; i < N; i++) {
        string row;
        for (int j = 0; j < N; j++) {
            char C; cin >> C; row.push_back(C);
        }
        gridArray[i] = move(row);
    }

    vector<vector<int>> distanceArray(N, vector<int>(N, -1));
    queue<pair<int, int>> bfsQueue;
    if (gridArray[0][0] != '#') {
        distanceArray[0][0] = 0;
        bfsQueue.push({0,0});
    }
    int firstDirections[4] = {-1, 1, 0, 0}, secondDirections[4] = {0, 0, -1, 1};
    while (!bfsQueue.empty()) {
        auto currentElement = bfsQueue.front(); bfsQueue.pop();
        int R = currentElement.first, C = currentElement.second;
        for (int t = 0; t < 4; t++) {
            int nR = R + firstDirections[t], nC = C + secondDirections[t];
            if (nR >= 0 && nR < N && nC >= 0 && nC < N && gridArray[nR][nC] != '#' && distanceArray[nR][nC] == -1) {
                distanceArray[nR][nC] = distanceArray[R][C] + 1;
                bfsQueue.push({nR, nC});
            }
        }
    }

    vector<vector<char>> isFort(N, vector<char>(N, 0));
    int K = 0;
    vector<int> initialCounts(D_RANGE, 0);
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        if (gridArray[i][j] == 'F') {
            isFort[i][j] = 1;
            ++K;
            if (distanceArray[i][j] != -1 && distanceArray[i][j] < D_RANGE) initialCounts[distanceArray[i][j]]++;
        }
    }

    Fenwick fenwickTree(D_RANGE);
    for (int D = 0; D < D_RANGE; D++) {
        if (initialCounts[D] > 0) fenwickTree.updateFenwick(D, initialCounts[D]);
    }

    vector<ll> initialValues(D_RANGE, MINUS_INF);
    for (int D = 1; D < D_RANGE; D++) {
        if (initialCounts[D] > 0) initialValues[D] = (ll)D - fenwickTree.queryFenwick(D - 1);
    }

    SegmentTree treeTool;
    treeTool.initializeTree(D_RANGE);
    treeTool.buildTree(1, 0, D_RANGE - 1, initialValues);

    vector<pii> queries(Q);
    for (int i = 0; i < Q; i++) {
        int R, C; cin >> R >> C; --R; --C;
        queries[i] = {R, C};
    }

    for (int day = 0; day <= Q; day++) {
        if (K == 0) {
            cout << 0 << endl;
        } else {
            ll maxV = treeTool.queryMax(1, 0, D_RANGE - 1, 0, D_RANGE - 1);
            cout << (ll)K - 1 + maxV << endl;
        }

        if (day == Q) break;

        int R = queries[day].first, C = queries[day].second;
        int D = (R >= 0 && R < N && C >= 0 && C < N) ? distanceArray[R][C] : -1;

        if (isFort[R][C]) {
            isFort[R][C] = 0;
            K--;
            if (D >= 0 && D < D_RANGE) {
                treeTool.rangeUpdate(1, 0, D_RANGE - 1, D + 1, D_RANGE - 1, 1);
                fenwickTree.updateFenwick(D, -1);
                int newCount = fenwickTree.rangeQuery(D, D);
                if (newCount == 0) treeTool.pointSet(1, 0, D_RANGE - 1, D, MINUS_INF);
            }
        } else {
            isFort[R][C] = 1;
            K++;
            if (D >= 0 && D < D_RANGE) {
                int oldS = fenwickTree.queryFenwick(D - 1);
                int oldCount = fenwickTree.rangeQuery(D, D);
                treeTool.rangeUpdate(1, 0, D_RANGE - 1, D + 1, D_RANGE - 1, -1);
                fenwickTree.updateFenwick(D, 1);
                if (oldCount == 0) treeTool.pointSet(1, 0, D_RANGE - 1, D, (ll)D - oldS);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while (T--) {
        solveTestCase();
    }
    return 0;
}
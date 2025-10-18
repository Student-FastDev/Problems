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
typedef pair<ll,int> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct SegmentTree {
    int N;
    vector<pair<ll,int>> treeArray;
    SegmentTree(int _N = 0) { inititalizeTree(_N); }
    void inititalizeTree(int _N) {
        N = 1;
        while (N < _N) N <<= 1;
        treeArray.assign(2 * N, {INF, -1});
    }
    void buildTree(const vector<ll>& A) {
        int M = (int)size(A) - 1;
        inititalizeTree(M);
        for (int i = 1; i <= M; ++i) treeArray[N + i - 1] = {A[i], i};
        for (int i = N - 1; i >= 1; --i) treeArray[i] = min(treeArray[2*i], treeArray[2*i+1]);
    }
    void pointUpdate(int updatePosition, ll valueArray) {
        int updatePoint = N + updatePosition - 1;
        treeArray[updatePoint] = { valueArray, updatePosition };
        updatePoint >>= 1;
        while (updatePoint) {
            treeArray[updatePoint] = min(treeArray[2*updatePoint], treeArray[2*updatePoint+1]);
            updatePoint >>= 1;
        }
    }
    pll queryTree(int l, int r) {
        if (l > r) return {INF, -1};
        l = l + N - 1;
        r = r + N - 1;
        pll finalResult = {INF, -1};
        while (l <= r) {
            if (l & 1) finalResult = min(finalResult, treeArray[l++]);
            if (!(r & 1)) finalResult = min(finalResult, treeArray[r--]);
            l >>= 1; r >>= 1;
        }
        return finalResult;
    }
};

int N;
vector<vector<int>> childrenArray;
vector<int> parentArray;
vector<int> IN, OUT, ORDER, SIZE;
vector<ll> valueArray;
SegmentTree segmentTree;
vector<int> resultArray;

void procedureFunction(int A) {
    while (true) {
        auto queryAll = segmentTree.queryTree(IN[A], IN[A] + SIZE[A] - 1);
        if (queryAll.first == INF) return;

        int updatePosition = queryAll.second;
        int v = ORDER[updatePosition];

        int l = IN[v] + 1;
        int r = IN[v] + SIZE[v] - 1;
        if (l > r) {
            segmentTree.pointUpdate(IN[v], INF);
            resultArray.push_back(v);
            continue;
        }
        auto queryChildren = segmentTree.queryTree(l, r);
        if (queryChildren.first == INF) {
            segmentTree.pointUpdate(IN[v], INF);
            resultArray.push_back(v);
            continue;
        } else {
            int childPosition = queryChildren.second;
            int child = ORDER[childPosition];
            procedureFunction(child);
            continue;
        }
    }
}

void solveTestCase() {
    cin >> N;
    parentArray.assign(N+1, 0);
    childrenArray.assign(N+1, {});
    for (int i = 2; i <= N; ++i) {
        int updatePoint; cin >> updatePoint;
        parentArray[i] = updatePoint;
        childrenArray[updatePoint].push_back(i);
    }
    valueArray.assign(N+1, 0);
    for (int i = 1; i <= N; ++i) cin >> valueArray[i];

    IN.assign(N+1, 0);
    OUT.assign(N+1, 0);
    ORDER.assign(N+1, 0);
    SIZE.assign(N+1, 0);
    int timerNumber = 0;
    vector<pll> treeArray;
    treeArray.emplace_back(1, 0);
    while (!treeArray.empty()) {
        auto [u, state] = treeArray.back(); treeArray.pop_back();
        if (state == 0) {
            ++timerNumber;
            IN[u] = timerNumber;
            ORDER[timerNumber] = u;
            treeArray.emplace_back(u, 1);
            for (int i = (int)size(childrenArray[u]) - 1; i >= 0; --i)
                treeArray.emplace_back(childrenArray[u][i], 0);
        } else {
            OUT[u] = timerNumber;
        }
    }
    for (int u = 1; u <= N; ++u) SIZE[u] = OUT[u] - IN[u] + 1;

    vector<ll> numberArray(N+1, INF);
    for (int t = 1; t <= N; ++t) numberArray[t] = valueArray[ORDER[t]];
    segmentTree.buildTree(numberArray);

    resultArray.reserve(N);
    procedureFunction(1);

    for (int i = 0; i < (int)size(resultArray); ++i) {
        if (i) cout << ' ';
        cout << resultArray[i];
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

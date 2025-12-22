// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&phasesValue,auto P)->decltype(P.first,phasesValue){return phasesValue<<'('<<P.first<<", "<<P.second <<')';}
auto operator<<(auto&phasesValue,auto x)->decltype(x.end(),phasesValue){phasesValue<<'{';int i=2;for(auto e:x)phasesValue<<(", ")+i<<e,i=0;return phasesValue<<'}';}
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

const ll INF = 9e18;;
const ll MAX_N = 2002;
const ll MOD = 1e9+7; // 998244353

struct DSU {
    vector<int> P, R;
    DSU(int n = 0) { initialize(n); }
    void initialize(int n) {
        P.resize(n + 1);
        R.assign(n + 1, 0);
        for (int i = 0; i <= n; ++i) P[i] = i;
    }
    int find(int x) { return P[x] == x ? x : (P[x] = find(P[x])); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (R[a] < R[b]) swap(a, b);
        P[b] = a;
        if (R[a] == R[b]) ++R[a];
        return true;
    }
};

struct Edge {
    int U, V;
    int W; 
    int edgeType;
};

int globalN, globalM;
vector<Edge> edgesArray;
vector<ll> modifiedW;
vector<int> indexOrder;

bool compareIndex(int a, int b) {
    return modifiedW[a] < modifiedW[b];
}

pll lambdaMST(ll lambda) {
    int n = globalN;
    int m = globalM;
    modifiedW.assign(m, 0);
    indexOrder.resize(m);

    for (int i = 0; i < m; ++i) {
        modifiedW[i] = (ll)edgesArray[i].W + lambda * (ll)edgesArray[i].edgeType;
        indexOrder[i] = i;
    }
    sort(indexOrder.begin(), indexOrder.end(), compareIndex);

    DSU findUnion(n);
    ll total = 0;
    int firstTypeUsed = 0;
    int usedEdges = 0;

    for (int i = 0; i < size(indexOrder); ++i) {
        int index = indexOrder[i];
        Edge &e = edgesArray[index];
        if (findUnion.unite(e.U, e.V)) {
            total += modifiedW[index];
            firstTypeUsed += e.edgeType;
            ++usedEdges;
            if (usedEdges == n - 1) break;
        }
    }
    if (usedEdges < n - 1) return make_pair(INF, -1);
    return make_pair(total, firstTypeUsed);
}

void solveTestCase() {
    int n, m, k;
    int neededW;
    cin >> n >> m >> k >> neededW;

    globalN = n;
    globalM = m;

    vector<int> specialArray(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int s; cin >> s;
        specialArray[s] = 1;
    }

    edgesArray.resize(m);
    ll sumW = 0;
    for (int i = 0; i < m; ++i) {
        int U, V, W;
        cin >> U >> V >> W;
        edgesArray[i].U = U;
        edgesArray[i].V = V;
        edgesArray[i].W = W;
        bool A = specialArray[U] != 0;
        bool B = specialArray[V] != 0;
        edgesArray[i].edgeType = (A ^ B) ? 1 : 0;
        sumW += W;
    }

    DSU findUnion(n);
    for (int i = 0; i < m; ++i) findUnion.unite(edgesArray[i].U, edgesArray[i].V);
    int componentsCount = 0;
    for (int i = 1; i <= n; ++i) if (findUnion.find(i) == i) ++componentsCount;
    if (componentsCount > 1) {
        cout << -1 << endl;
        return;
    }

    ll B = sumW + 5;
    ll lambdaLow = -B;
    ll lambdaHigh = B;

    pll resultLow = lambdaMST(lambdaLow);
    pll resultHigh = lambdaMST(lambdaHigh);
    int lowC = resultLow.second;
    int highC = resultHigh.second;
    int minC = min(lowC, highC);
    int maxC = max(lowC, highC);

    if (neededW < minC || neededW > maxC) {
        cout << -1 << endl;
        return;
    }

    ll leftRange = lambdaLow;
    ll rightRange = lambdaHigh;
    ll bestLambda = lambdaLow;

    while (leftRange <= rightRange) {
        ll middleValue = leftRange + (rightRange - leftRange) / 2;
        pll R = lambdaMST(middleValue);
        int count = R.second;
        if (count >= neededW) {
            bestLambda = middleValue;
            leftRange = middleValue + 1;
        } else {
            rightRange = middleValue - 1;
        }
    }

    ll zeroLambda = bestLambda;
    pll zeroR = lambdaMST(zeroLambda);
    ll zeroF = zeroR.first - zeroLambda * (ll)neededW;
    ll bestF = zeroF;

    if (zeroLambda + 1 <= lambdaHigh) {
        ll firstLambda = zeroLambda + 1;
        pll firstR = lambdaMST(firstLambda);
        ll firstF = firstR.first - firstLambda * (ll)neededW;
        if (firstF > bestF) bestF = firstF;
    }

    cout << bestF << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

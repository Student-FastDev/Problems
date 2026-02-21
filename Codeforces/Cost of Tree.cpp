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
const ll MAX_N = 2e5 + 67;
const ll MOD = 1e9+7; // 998244353

int A[MAX_N];
vector<int> neighbourList[MAX_N];
int parentNode[MAX_N];
int depthArray[MAX_N];
ll S[MAX_N];
int maxDepth[MAX_N];
int H[MAX_N];
int maxSide[MAX_N];
ll baseArray[MAX_N];
ll answerArray[MAX_N];

void sizeDFS(int u, int p, int d) {
    parentNode[u] = p;
    depthArray[u] = d;
    S[u] = A[u];
    maxDepth[u] = d;
    baseArray[u] = 0;
    
    for(int v : neighbourList[u]) {
        if(v != p) {
            sizeDFS(v, u, d + 1);
            S[u] += S[v];
            maxDepth[u] = max(maxDepth[u], maxDepth[v]);
            baseArray[u] += baseArray[v] + S[v];
        }
    }
    
    H[u] = 0;
    for(int v : neighbourList[u]) {
        if(v != p) {
            if(H[u] == 0 || maxDepth[v] > maxDepth[H[u]]) H[u] = v;
        }
    }
    
    maxSide[u] = d;
    for(int v : neighbourList[u]) {
        if(v != p && v != H[u]) maxSide[u] = max(maxSide[u], maxDepth[v]);
    }
}

ll lightDFS(int u, int p_node, ll max_dep_p) {
    ll finalResult = S[u] * (max_dep_p - depthArray[u] + 1);
    for(int v : neighbourList[u]) {
        if(v != p_node) {
            finalResult = max(finalResult, lightDFS(v, u, max_dep_p));
        }
    }
    return finalResult;
}

using int128 = __int128;

struct Line {
    ll m, c;
};

bool isBad(const Line& l1, const Line& l2, const Line& l3) {
    int128 firstNumerator = (int128)(l1.c - l3.c);
    int128 firstDenumerator = (int128)(l3.m - l1.m);
    int128 secondNumerator = (int128)(l1.c - l2.c);
    int128 secondDenumerator = (int128)(l2.m - l1.m);
    return firstNumerator * secondDenumerator <= secondNumerator * firstDenumerator;
}

ll lineEvaluate(const Line& l, ll x) {
    return l.m * x + l.c;
}

ll queryHull(const vector<Line>& hull, ll x) {
    if(hull.empty()) return -4e18;
    int l = 0, r = (int)size(hull) - 1;
    int bestValue = 0;
    while(l <= r) {
        int middleValue = l + (r - l) / 2;
        ll firstY = lineEvaluate(hull[middleValue], x);
        ll secondY = (middleValue + 1 < size(hull)) ? lineEvaluate(hull[middleValue+1], x) : -4e18;
        if(firstY <= secondY) {
            bestValue = middleValue + 1;
            l = middleValue + 1;
        } else {
            bestValue = middleValue;
            r = middleValue - 1;
        }
    }
    return lineEvaluate(hull[bestValue], x);
}

struct SegmentTree {
    int N;
    vector<vector<Line>> treeArray;

    SegmentTree(int N) : N(N), treeArray(4 * N + 1) {}

    void buildTree(int node, int l, int r, const vector<Line>& lineArray) {
        if (l == r) {
            treeArray[node].push_back(lineArray[l]);
            return;
        }
        int middleValue = l + (r - l) / 2;
        buildTree(2 * node, l, middleValue, lineArray);
        buildTree(2 * node + 1, middleValue + 1, r, lineArray);
        
        treeArray[node].reserve(size(treeArray[2 * node]) + size(treeArray[2 * node + 1]));
        
        int i = 0, j = 0;
        vector<Line> sortedArray;
        sortedArray.reserve(size(treeArray[2 * node]) + size(treeArray[2 * node + 1]));
        while(i < size(treeArray[2 * node]) && j < size(treeArray[2 * node + 1])) {
            if(treeArray[2 * node][i].m < treeArray[2 * node + 1][j].m) {
                sortedArray.push_back(treeArray[2 * node][i++]);
            } else if(treeArray[2 * node][i].m > treeArray[2 * node + 1][j].m) {
                sortedArray.push_back(treeArray[2 * node + 1][j++]);
            } else {
                if(treeArray[2 * node][i].c >= treeArray[2 * node + 1][j].c) {
                    sortedArray.push_back(treeArray[2 * node][i++]);
                    j++;
                } else {
                    sortedArray.push_back(treeArray[2 * node + 1][j++]);
                    i++;
                }
            }
        }
        while(i < size(treeArray[2 * node])) sortedArray.push_back(treeArray[2*node][i++]);
        while(j < size(treeArray[2 * node + 1])) sortedArray.push_back(treeArray[2 * node + 1][j++]);
        
        vector<Line> uniqueLines;
        uniqueLines.reserve(size(sortedArray));
        for(const auto& line : sortedArray) {
            if(!uniqueLines.empty() && uniqueLines.back().m == line.m) {
                uniqueLines.back().c = max(uniqueLines.back().c, line.c);
            } else {
                uniqueLines.push_back(line);
            }
        }
        
        for(const auto& line : uniqueLines) {
            while(size(treeArray[node]) >= 2 && isBad(treeArray[node][size(treeArray[node]) - 2], treeArray[node].back(), line)) {
                treeArray[node].pop_back();
            }
            treeArray[node].push_back(line);
        }
    }

    ll queryTree(int node, int l, int r, int left, int right, ll x) {
        if(left > r || right < l) return -4e18;
        if(left <= l && r <= right) {
            return queryHull(treeArray[node], x);
        }
        int middleValue = l + (r - l) / 2;
        return max(queryTree(2 * node, l, middleValue, left, right, x), queryTree(2 * node + 1, middleValue + 1, r, left, right, x));
    }
};

struct Interval {
    int L, R;
    ll V, M, maxStackM;
};

void processPath(const vector<int>& P) {
    int K = size(P);
    vector<ll> maxL(K + 1, 0);
    for(int i = 0; i < K; ++i) {
        int u = P[i];
        ll maxValue = 0;
        for(int v : neighbourList[u]) {
            if(v != parentNode[u] && v != H[u]) {
                maxValue = max(maxValue, lightDFS(v, u, maxDepth[u]));
            }
        }
        maxL[i + 1] = maxValue;
    }
    
    vector<ll> suffixMaxL(K + 2, 0);
    for(int i = K; i >= 1; --i) {
        suffixMaxL[i] = max(maxL[i], suffixMaxL[i + 1]);
    }
    
    vector<Line> lineArray(K + 1);
    for(int i = 1; i <= K; ++i) {
        lineArray[i] = {S[P[i - 1]], -S[P[i - 1]] * (depthArray[P[i - 1]] - 1)};
    }
    
    SegmentTree treeTool(K);
    if(K > 0) treeTool.buildTree(1, 1, K, lineArray);
    
    vector<Interval> stackArray;
    vector<ll> secondAnswer(K + 1, 0);
    
    for(int A = K; A >= 1; --A) {
        int u = P[A - 1];
        ll V = maxSide[u];
        Interval I = {A + 1, A + 1, V, 0, 0};
        if(A == K) {
            I = {K + 1, K, V, 0, 0};
        }
        
        while(!stackArray.empty() && stackArray.back().V <= V) {
            I.R = stackArray.back().R;
            stackArray.pop_back();
        }
        
        if(I.L <= I.R) {
            I.M = treeTool.queryTree(1, 1, K, I.L, I.R, V);
        } else {
            I.M = -4e18;
        }
        
        ll belowMax = stackArray.empty() ? 0 : stackArray.back().maxStackM;
        I.maxStackM = max({0LL, I.M, belowMax});
        stackArray.push_back(I);
        
        secondAnswer[A] = stackArray.back().maxStackM;
        answerArray[u] = max({0LL, suffixMaxL[A], secondAnswer[A]});
    }
}

void solveTestCase() {
    int N;
    cin >> N;
    for(int i = 1; i <= N; ++i) cin >> A[i];
    for(int i = 1; i <= N; ++i) {
        neighbourList[i].clear();
        H[i] = 0;
    }
    for(int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }
    
    sizeDFS(1, 0, 0);
    
    for(int i = 1; i <= N; ++i) answerArray[i] = 0;
    
    for(int i = 1; i <= N; ++i) {
        if(i == 1 || H[parentNode[i]] != i) {
            vector<int> path;
            int currentElement = i;
            while(currentElement != 0) {
                path.push_back(currentElement);
                currentElement = H[currentElement];
            }
            processPath(path);
        }
    }
    
    for(int i = 1; i <= N; ++i) {
        cout << baseArray[i] + answerArray[i] << (i == N ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

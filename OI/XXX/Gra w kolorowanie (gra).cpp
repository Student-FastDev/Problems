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
const ll MAX_N = 5 * 1e5+1;
const ll MOD = 1e9+7;

int N;
vector<int> neighbourList[MAX_N];
int sizeArray[MAX_N];
int distanceArray[MAX_N];
bool firstV[MAX_N];
int firstC = -1, secondC = -1;

struct fenwickTree {
    int treeArray[MAX_N];
    int totalCount;

    void init() {
        fill(treeArray, treeArray + N + 2, 0);
        totalCount = 0;
    }

    void treeAdd(int index, int value) {
        index++;
        totalCount += value;
        for (; index <= N + 1; index += index & -index) treeArray[index] += value;
    }

    int treeQuery(int index) {
        index++;
        if (index <= 0) return 0;
        if (index > N + 1) index = N + 1;
        int sum = 0;
        for (; index > 0; index -= index & -index) sum += treeArray[index];
        return sum;
    }
    
    int countSmaller(int D) {
        return treeQuery(D);
    }
    
    int countBigger(int D) {
        return totalCount - treeQuery(D - 1);
    }
} bitA, bitB;

void sizeDFS(int u, int p) {
    sizeArray[u] = 1;
    bool isCentroid = true;
    for (int v : neighbourList[u]) {
        if (v != p) {
            sizeDFS(v, u);
            sizeArray[u] += sizeArray[v];
            if (sizeArray[v] > N / 2) isCentroid = false;
        }
    }
    if (N - sizeArray[u] > N / 2) isCentroid = false;
    
    if (isCentroid) {
        if (firstC == -1) firstC = u;
        else secondC = u;
    }
}

void distanceBFS(int start) {
    for(int i = 1; i <= N; ++i) distanceArray[i] = -1;
    vector<int> queueArray;
    queueArray.push_back(start);
    distanceArray[start] = 0;
    
    int head = 0;
    while(head < size(queueArray)){
        int u = queueArray[head++];
        for(int v : neighbourList[u]){
            if(distanceArray[v] == -1){
                distanceArray[v] = distanceArray[u] + 1;
                queueArray.push_back(v);
            }
        }
    }
}

void markDFS(int u, int p, int badNeighbor) {
    firstV[u] = true;
    for(int v : neighbourList[u]){
        if(v != p && v != badNeighbor){
            markDFS(v, u, badNeighbor);
        }
    }
}

ll globalPairs = 0;
ll correctionAmount = 0;
ll overlapPairs = 0;

int countFirstA[MAX_N]; 
int countSecondB[MAX_N]; 

bool inSetA[MAX_N];
bool inSetB[MAX_N];

void addA(int u) {
    if (inSetA[u]) return;
    inSetA[u] = true;
    if (inSetB[u]) overlapPairs++;
    
    int D = distanceArray[u];
    
    globalPairs += bitB.countBigger(D);
    bitA.treeAdd(D, 1);
    
    if (secondC != -1 && firstV[u]) {
        countFirstA[D]++;
        ll term = 0;
        if (D <= N) term += countSecondB[D];
        if (D + 1 <= N) term += countSecondB[D + 1];
        correctionAmount += term;
    }
}

void removeA(int u) {
    if (!inSetA[u]) return;
    inSetA[u] = false;
    if (inSetB[u]) overlapPairs--;
    
    int D = distanceArray[u];
    bitA.treeAdd(D, -1);
    globalPairs -= bitB.countBigger(D);
    
    if (secondC != -1 && firstV[u]) {
        countFirstA[D]--;
        ll term = 0;
        if (D <= N) term += countSecondB[D];
        if (D + 1 <= N) term += countSecondB[D + 1];
        correctionAmount -= term;
    }
}

void addB(int u) {
    if (inSetB[u]) return;
    inSetB[u] = true;
    if (inSetA[u]) overlapPairs++;
    
    int D = distanceArray[u];
    
    globalPairs += bitA.countSmaller(D);
    bitB.treeAdd(D, 1);
    
    if (secondC != -1 && !firstV[u]) { 
        countSecondB[D]++;
        ll term = 0;
        if (D <= N) term += countFirstA[D];
        if (D - 1 >= 0) term += countFirstA[D - 1];
        correctionAmount += term;
    }
}

void removeB(int u) {
    if (!inSetB[u]) return;
    inSetB[u] = false;
    if (inSetA[u]) overlapPairs--;
    
    int D = distanceArray[u];
    bitB.treeAdd(D, -1);
    globalPairs -= bitA.countSmaller(D);
    
    if (secondC != -1 && !firstV[u]) {
        countSecondB[D]--;
        ll term = 0;
        if (D <= N) term += countFirstA[D];
        if (D - 1 >= 0) term += countFirstA[D - 1];
        correctionAmount -= term;
    }
}

void solveTestCase() {
    cin >> N;
    for(int i = 0; i < N-1; ++i){
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }
    
    sizeDFS(1, 0);
    distanceBFS(firstC);
    
    if (secondC != -1) {
        markDFS(firstC, 0, secondC);
    }
    
    bitA.init();
    bitB.init();
    
    int A, B, Q;
    cin >> A >> B >> Q;
    
    vector<int> initA(A);
    for(int i = 0; i < A; ++i) cin >> initA[i];
    vector<int> initB(B);
    for(int i = 0; i < B; ++i) cin >> initB[i];
    
    for(int x : initA) addA(x);
    for(int x : initB) addB(x);
    
    cout << (globalPairs - correctionAmount - overlapPairs) << endl;
    
    for(int i = 0; i < Q; ++i){
        char z, t;
        int w;
        cin >> z >> t >> w;
        if(z == 'A'){
            if(t == '+') addA(w);
            else removeA(w);
        } else {
            if(t == '+') addB(w);
            else removeB(w);
        }
        cout << (globalPairs - correctionAmount - overlapPairs) << endl;
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

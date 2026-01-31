// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e6+1;
const ll MOD = 998244353; 

const int MAX_BITS = 60;
const int MAX_TRIE_NODES = 13000000;

int trieArray[MAX_TRIE_NODES][2];
int sizeArray[MAX_TRIE_NODES];
int rootNode;
int nodesCount;
ll twoPowers[MAX_N];
bool isInitialized = false;

int newNode() {
    int U = ++nodesCount;
    trieArray[U][0] = trieArray[U][1] = 0;
    sizeArray[U] = 0;
    return U;
}

void insertNode(ll value) {
    int U = rootNode;
    sizeArray[U]++;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int b = (value >> i) & 1;
        if (!trieArray[U][b]) trieArray[U][b] = newNode();
        U = trieArray[U][b];
        sizeArray[U]++;
    }
}

ll countPairs(int U, int v, int bit, ll X) {
    if (!U || !v) return 0;
    if (bit < 0) return (1LL * sizeArray[U] * sizeArray[v]) % MOD;

    int B = (X >> bit) & 1;
    ll finalResult = 0;
    int firstU = trieArray[U][0], secondU = trieArray[U][1];
    int firstV = trieArray[v][0], secondV = trieArray[v][1];

    if (B == 0) {
        if (firstU && secondV) finalResult = (finalResult + 1LL * sizeArray[firstU] * sizeArray[secondV]) % MOD;
        if (secondU && firstV) finalResult = (finalResult + 1LL * sizeArray[secondU] * sizeArray[firstV]) % MOD;
        finalResult = (finalResult + countPairs(firstU, firstV, bit - 1, X)) % MOD;
        finalResult = (finalResult + countPairs(secondU, secondV, bit - 1, X)) % MOD;
    } else {
        finalResult = (finalResult + countPairs(firstU, secondV, bit - 1, X)) % MOD;
        finalResult = (finalResult + countPairs(secondU, firstV, bit - 1, X)) % MOD;
    }
    return finalResult;
}

ll recursiveSolver(int U, int bit, ll X) {
    if (!U) return 1;
    if (bit < 0) return twoPowers[sizeArray[U]];

    int B = (X >> bit) & 1;
    int leftNode = trieArray[U][0], rightNode = trieArray[U][1];

    if (B == 0) {
        ll L = recursiveSolver(leftNode, bit - 1, X);
        ll R = recursiveSolver(rightNode, bit - 1, X);
        return (L * R) % MOD;
    } else {
        ll finalResult = 1;
        if (leftNode) finalResult = (finalResult + sizeArray[leftNode]) % MOD;
        if (rightNode) finalResult = (finalResult + sizeArray[rightNode]) % MOD;
        finalResult = (finalResult + countPairs(leftNode, rightNode, bit - 1, X)) % MOD;
        return finalResult;
    }
}

void solveTestCase() {
    if (!isInitialized) {
        twoPowers[0] = 1;
        for (int i = 1; i < MAX_N; i++) twoPowers[i] = (twoPowers[i - 1] * 2) % MOD;
        isInitialized = true;
    }

    int N;
    ll X;
    cin >> N >> X;

    nodesCount = 0;
    rootNode = newNode();

    for (int i = 0; i < N; i++) {
        ll A;
        cin >> A;
        insertNode(A);
    }

    ll finalAnswer = recursiveSolver(rootNode, MAX_BITS - 1, X);
    finalAnswer = (finalAnswer - 1 + MOD) % MOD;
    cout << finalAnswer << endl;
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
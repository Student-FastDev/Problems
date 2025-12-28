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
const ll MAX_N = 1e9+1;
const ll MOD = 998244353; // 998244353

ll factorialArray[400005], inverseFactorialArray[400005];

ll modularExponentiation(ll base, ll exponent) {
    ll result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent /= 2;
    }
    return result;
}

ll calculateModularInverse(ll number) {
    return modularExponentiation(number, MOD - 2);
}

void precomputeFactorials() {
    factorialArray[0] = 1;
    inverseFactorialArray[0] = 1;
    for (int i = 1; i <= 400000; i++) {
        factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
        inverseFactorialArray[i] = calculateModularInverse(factorialArray[i]);
    }
}

struct FactorialPrecomputer { FactorialPrecomputer() { precomputeFactorials(); } } factorialPrecomputerInstance;

ll combinations(int n, int r) {
    if (r < 0 || r > n) return 0;
    return factorialArray[n] * inverseFactorialArray[r] % MOD * inverseFactorialArray[n - r] % MOD;
}

struct TreapNode {
    int leftChildIndex, rightChildIndex;
    ll nodeWeight;
    int nodeValue;
    ll subtreeTotalWeight;
    int priority;
} treapNodes[1200005];
int nodePoolPointer = 0;

int createNode(ll weight, int value) {
    int nodeIndex = ++nodePoolPointer;
    treapNodes[nodeIndex].leftChildIndex = treapNodes[nodeIndex].rightChildIndex = 0;
    treapNodes[nodeIndex].nodeWeight = weight;
    treapNodes[nodeIndex].nodeValue = value;
    treapNodes[nodeIndex].subtreeTotalWeight = weight;
    treapNodes[nodeIndex].priority = (int)rng();
    return nodeIndex;
}

void updateNodeSize(int nodeIndex) {
    if (!nodeIndex) return;
    treapNodes[nodeIndex].subtreeTotalWeight = treapNodes[nodeIndex].nodeWeight + 
        (treapNodes[nodeIndex].leftChildIndex ? treapNodes[treapNodes[nodeIndex].leftChildIndex].subtreeTotalWeight : 0) + 
        (treapNodes[nodeIndex].rightChildIndex ? treapNodes[treapNodes[nodeIndex].rightChildIndex].subtreeTotalWeight : 0);
}

void splitTreap(int nodeIndex, ll k, int &outLeft, int &outRight) {
    if (!nodeIndex) { outLeft = outRight = 0; return; }
    ll leftSubtreeWeight = treapNodes[nodeIndex].leftChildIndex ? treapNodes[treapNodes[nodeIndex].leftChildIndex].subtreeTotalWeight : 0;
    if (k <= leftSubtreeWeight) {
        splitTreap(treapNodes[nodeIndex].leftChildIndex, k, outLeft, treapNodes[nodeIndex].leftChildIndex);
        updateNodeSize(nodeIndex);
        outRight = nodeIndex;
    } else if (k < leftSubtreeWeight + treapNodes[nodeIndex].nodeWeight) {
        int splitLeftNode = createNode(k - leftSubtreeWeight, treapNodes[nodeIndex].nodeValue);
        int splitRightNode = createNode(treapNodes[nodeIndex].nodeWeight - (k - leftSubtreeWeight), treapNodes[nodeIndex].nodeValue);
        
        treapNodes[splitLeftNode].leftChildIndex = treapNodes[nodeIndex].leftChildIndex;
        updateNodeSize(splitLeftNode);
        
        treapNodes[splitRightNode].rightChildIndex = treapNodes[nodeIndex].rightChildIndex;
        updateNodeSize(splitRightNode);
        
        outLeft = splitLeftNode;
        outRight = splitRightNode;
    } else {
        splitTreap(treapNodes[nodeIndex].rightChildIndex, k - leftSubtreeWeight - treapNodes[nodeIndex].nodeWeight, treapNodes[nodeIndex].rightChildIndex, outRight);
        updateNodeSize(nodeIndex);
        outLeft = nodeIndex;
    }
}

void mergeTreap(int &nodeIndex, int leftTree, int rightTree) {
    if (!leftTree || !rightTree) nodeIndex = leftTree ? leftTree : rightTree;
    else if (treapNodes[leftTree].priority > treapNodes[rightTree].priority) {
        mergeTreap(treapNodes[leftTree].rightChildIndex, treapNodes[leftTree].rightChildIndex, rightTree);
        updateNodeSize(leftTree);
        nodeIndex = leftTree;
    } else {
        mergeTreap(treapNodes[rightTree].leftChildIndex, leftTree, treapNodes[rightTree].leftChildIndex);
        updateNodeSize(rightTree);
        nodeIndex = rightTree;
    }
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    vector<pii> operations(M);
    for(int i = 0; i < M; ++i) cin >> operations[i].first >> operations[i].second;

    nodePoolPointer = 0;
    int treapRoot = 0;
    int countValueOne = 0;
    int currentStepIndex = 2;

    for (int i = 0; i < M; ++i) {
        int operationStep = operations[i].first;
        int insertionPosition = operations[i].second;

        if (operationStep > currentStepIndex) {
            int gapNode = createNode(operationStep - currentStepIndex, 0);
            mergeTreap(treapRoot, treapRoot, gapNode);
        }
        currentStepIndex = operationStep + 1;

        if (insertionPosition == 1) {
            int newNode = createNode(1, 1);
            mergeTreap(treapRoot, newNode, treapRoot);
            countValueOne++;
        } else {
            int treePrefix, treeSuffixWithTarget, treeTargetElement, treeSuffixRest;
            splitTreap(treapRoot, insertionPosition - 2, treePrefix, treeSuffixWithTarget);
            splitTreap(treeSuffixWithTarget, 1, treeTargetElement, treeSuffixRest);
            
            if (treapNodes[treeTargetElement].nodeValue == 1) countValueOne--;
            
            int newZeroNode = createNode(1, 0);
            int newOneNode = createNode(1, 1);
            countValueOne++;

            mergeTreap(treapRoot, treePrefix, newZeroNode);
            mergeTreap(treapRoot, treapRoot, newOneNode);
            mergeTreap(treapRoot, treapRoot, treeSuffixRest);
        }
    }

    if (currentStepIndex <= N) {
        int finalGapNode = createNode((ll)N - currentStepIndex + 1, 0);
        mergeTreap(treapRoot, treapRoot, finalGapNode);
    }

    cout << combinations(2 * N - 1 - countValueOne, N) << endl;
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
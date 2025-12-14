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
const ll MAX_N = 150005;
const ll MOD = 998244353; // 998244353

ll modularExponentiation(ll baseValue, ll exponentValue) {
    ll resultValue = 1;
    baseValue %= MOD;
    while (exponentValue > 0) {
        if (exponentValue % 2 == 1) resultValue = (resultValue * baseValue) % MOD;
        baseValue = (baseValue * baseValue) % MOD;
        exponentValue /= 2;
    }
    return resultValue;
}

ll modularInverse(ll N) {
    return modularExponentiation(N, MOD - 2);
}

vector<int> neighbourList[MAX_N];
int parentNode[MAX_N], depthLevel[MAX_N], heavyChild[MAX_N], chainHead[MAX_N], positionInArray[MAX_N], subtreeSize[MAX_N];
int currentPosition;
ll weightArray[MAX_N]; 
ll accumulatedH[MAX_N];

struct BitRangeAddPointQuery {
    ll treeArray[MAX_N];
    int limitIndex;
    void initialize(int N) {
        limitIndex = N;
        fill(treeArray, treeArray + limitIndex + 1, 0);
    }
    void addValue(int indexNumber, ll valueToAdd) {
        for (; indexNumber <= limitIndex; indexNumber += indexNumber & -indexNumber)
            treeArray[indexNumber] = (treeArray[indexNumber] + valueToAdd) % MOD;
    }
    void rangeAdd(int L, int R, ll valueToAdd) {
        if (L > R) return;
        addValue(L, valueToAdd);
        addValue(R + 1, (MOD - valueToAdd) % MOD);
    }
    ll queryValue(int indexNumber) {
        ll sumValue = 0;
        for (; indexNumber > 0; indexNumber -= indexNumber & -indexNumber)
            sumValue = (sumValue + treeArray[indexNumber]) % MOD;
        return sumValue;
    }
} rangeAddBit;

struct BitPointUpdateRangeSum {
    ll treeArray[MAX_N];
    int limitIndex;
    void initialize(int N) {
        limitIndex = N;
        fill(treeArray, treeArray + limitIndex + 1, 0);
    }
    void addValue(int indexNumber, ll valueToAdd) {
        for (; indexNumber <= limitIndex; indexNumber += indexNumber & -indexNumber)
            treeArray[indexNumber] = (treeArray[indexNumber] + valueToAdd) % MOD;
    }
    ll queryPrefix(int indexNumber) {
        ll sumValue = 0;
        for (; indexNumber > 0; indexNumber -= indexNumber & -indexNumber)
            sumValue = (sumValue + treeArray[indexNumber]) % MOD;
        return sumValue;
    }
    ll queryRange(int L, int R) {
        if (L > R) return 0;
        return (queryPrefix(R) - queryPrefix(L - 1) + MOD) % MOD;
    }
} pointUpdateBit;

void dfsSubtreeSize(int U, int P) {
    subtreeSize[U] = 1;
    parentNode[U] = P;
    depthLevel[U] = depthLevel[P] + 1;
    int maxSubtreeSize = 0;
    heavyChild[U] = -1;
    for (int V : neighbourList[U]) {
        if (V != P) {
            dfsSubtreeSize(V, U);
            subtreeSize[U] += subtreeSize[V];
            if (subtreeSize[V] > maxSubtreeSize) {
                maxSubtreeSize = subtreeSize[V];
                heavyChild[U] = V;
            }
        }
    }
}

void dfsHeavyLight(int U, int H) {
    chainHead[U] = H;
    positionInArray[U] = ++currentPosition;
    if (heavyChild[U] != -1) {
        weightArray[U] = subtreeSize[heavyChild[U]];
        dfsHeavyLight(heavyChild[U], H);
    } else {
        weightArray[U] = 0;
    }
    for (int V : neighbourList[U]) {
        if (V != parentNode[U] && V != heavyChild[U]) {
            dfsHeavyLight(V, V);
        }
    }
}

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    for (int i = 0; i < N - 1; ++i) {
        int U, V;
        cin >> U >> V;
        neighbourList[U].push_back(V);
        neighbourList[V].push_back(U);
    }

    depthLevel[0] = 0;
    dfsSubtreeSize(1, 0);
    currentPosition = 0;
    dfsHeavyLight(1, 1);

    rangeAddBit.initialize(N);
    pointUpdateBit.initialize(N);
    
    ll inverseN = modularInverse(N);

    for (int i = 0; i < Q; ++i) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            int V;
            ll D;
            cin >> V >> D;
            D %= MOD;

            ll termOne = (D * subtreeSize[V]) % MOD * inverseN % MOD;
            rangeAddBit.rangeAdd(1, N, termOne);

            ll termTwo = (D * (N - subtreeSize[V])) % MOD * inverseN % MOD;
            rangeAddBit.rangeAdd(positionInArray[V], positionInArray[V] + subtreeSize[V] - 1, termTwo);

            ll deltaHValue = D * inverseN % MOD;
            accumulatedH[V] = (accumulatedH[V] + deltaHValue) % MOD;
            
            ll deltaWValue = deltaHValue * weightArray[V] % MOD;
            pointUpdateBit.addValue(positionInArray[V], deltaWValue);
        } else {
            int U;
            cin >> U;
            ll answerValue = rangeAddBit.queryValue(positionInArray[U]);
            
            int currentNode = U;
            ll subtractedValue = 0;
            while (currentNode != 0) {
                int topNode = chainHead[currentNode];
                if (topNode != currentNode) {
                     int parentCurrent = parentNode[currentNode];
                     ll chainSumValue = pointUpdateBit.queryRange(positionInArray[topNode], positionInArray[parentCurrent]);
                     subtractedValue = (subtractedValue + chainSumValue) % MOD;
                }
                
                int parentTop = parentNode[topNode];
                if (parentTop != 0) {
                    ll lightChildValue = accumulatedH[parentTop] * subtreeSize[topNode] % MOD;
                    subtractedValue = (subtractedValue + lightChildValue) % MOD;
                }
                currentNode = parentTop;
            }
            
            answerValue = (answerValue - subtractedValue + MOD) % MOD;
            cout << answerValue << endl;
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
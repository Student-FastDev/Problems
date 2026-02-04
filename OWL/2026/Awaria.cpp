// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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
#define size(x)  (int)x.size()

const ll INF = 1e18 + 67;
const int MAX_N = 2e5 + 5;
const ll MOD = 1e9 + 7;
const int MAX_VALUE = 6e5 + 67;

ll factorialArray[MAX_VALUE];
ll inverseFactorialArray[MAX_VALUE];

ll fastPower(ll base, ll power) {
    if(power == 0) return 1;
    if(power == 1) return base;

    if(power % 2 == 0) {
        ll helperValue = fastPower(base, power / 2) % MOD;
        return (helperValue * helperValue) % MOD;
    } else {
        return (fastPower(base, power - 1) * base) % MOD;
    }
}

ll getInverse(ll a) {
    return fastPower(a, MOD - 2);
}

void precomputeFactorials() {
    factorialArray[0] = 1;
    inverseFactorialArray[0] = 1;

    for(ll i = 1; i < MAX_VALUE; i++) {
        factorialArray[i] = (factorialArray[i - 1] * i) % MOD;
        inverseFactorialArray[i] = getInverse(factorialArray[i]);
    }
}

ll getBinomial(ll a, ll b) {
    if(b < 0 || b > a) return 0;
    return (factorialArray[a] * inverseFactorialArray[b]) % MOD * inverseFactorialArray[a - b] % MOD;
}

ll calculateWays(ll remainingCapacity, int remainingSize) {
    if(remainingCapacity < 0) return 0;
    if(remainingSize == 0) return remainingCapacity == 0 ? 1 : 0;
    return getBinomial(remainingCapacity + remainingSize - 1, remainingSize - 1);
}

vector<vector<int>> neighbourList;
int timeIn[MAX_N], timeOut[MAX_N], subtreeSize[MAX_N];
int nodeAtPreorderIndex[MAX_N];
int timeCounter = 0;

void performDFS(int u, int P) {
    timeCounter++;
    timeIn[u] = timeCounter;
    nodeAtPreorderIndex[timeCounter] = u;
    subtreeSize[u] = 1;
    for(int v : neighbourList[u]) {
        if(v != P) {
            performDFS(v, u);
            subtreeSize[u] += subtreeSize[v];
        }
    }
    timeOut[u] = timeCounter;
}

int maxSegTree[4 * MAX_N];

void updateMaxTree(int node, int start, int end, int index, int value) {
    if(start == end) {
        maxSegTree[node] = value;
        return;
    }
    int middleValue = (start + end) / 2;
    if(index <= middleValue) updateMaxTree(2 * node, start, middleValue, index, value);
    else updateMaxTree(2 * node + 1, middleValue + 1, end, index, value);
    maxSegTree[node] = max(maxSegTree[2 * node], maxSegTree[2 * node + 1]);
}

int queryNearestAncestor(int node, int start, int end, int queryLimit, int valueLimit) {
    if(start > queryLimit || maxSegTree[node] < valueLimit) return 0;
    
    if(start == end) return nodeAtPreorderIndex[start];

    int middleValue = (start + end) / 2;
    int finalResult = queryNearestAncestor(2 * node + 1, middleValue + 1, end, queryLimit, valueLimit);
    if(finalResult != 0) return finalResult;
    
    return queryNearestAncestor(2 * node, start, middleValue, queryLimit, valueLimit);
}

struct ValueNode {
    ll capacity;
    int size;
};

ValueNode sumArray[4 * MAX_N];

void updateSumTree(int node, int start, int end, int index, ll capacityValue, int sizeValue) {
    if(start == end) {
        sumArray[node] = {capacityValue, sizeValue};
        return;
    }
    int middleValue = (start + end) / 2;
    if(index <= middleValue) updateSumTree(2 * node, start, middleValue, index, capacityValue, sizeValue);
    else updateSumTree(2 * node + 1, middleValue + 1, end, index, capacityValue, sizeValue);
    
    sumArray[node].capacity = sumArray[2 * node].capacity + sumArray[2 * node + 1].capacity;
    sumArray[node].size = sumArray[2 * node].size + sumArray[2 * node + 1].size;
}

void addToSumTree(int node, int start, int end, int index, ll capacityValue, int sizeValue) {
    if(start == end) {
        sumArray[node].capacity += capacityValue;
        sumArray[node].size += sizeValue;
        return;
    }
    int middleValue = (start + end) / 2;
    if(index <= middleValue) addToSumTree(2 * node, start, middleValue, index, capacityValue, sizeValue);
    else addToSumTree(2 * node + 1, middleValue + 1, end, index, capacityValue, sizeValue);
    
    sumArray[node].capacity = sumArray[2 * node].capacity + sumArray[2 * node + 1].capacity;
    sumArray[node].size = sumArray[2 * node].size + sumArray[2 * node + 1].size;
}

ValueNode querySumTree(int node, int start, int end, int l, int r) {
    if(r < start || end < l) return {0, 0};
    if(l <= start && end <= r) return sumArray[node];
    
    int middleValue = (start + end) / 2;
    ValueNode firstPoint = querySumTree(2 * node, start, middleValue, l, r);
    ValueNode secondPoint = querySumTree(2 * node + 1, middleValue + 1, end, l, r);
    return {firstPoint.capacity + secondPoint.capacity, firstPoint.size + secondPoint.size};
}

ll currentWaysArray[MAX_N];
ll cachedRemainingCapacity[MAX_N];
int cachedRemainingSize[MAX_N];

int zeroWaysCount = 0;
ll totalWaysProduct = 1;

void updateWaysForNode(int u, ll newWays) {
    if(currentWaysArray[u] == 0) zeroWaysCount--;
    else totalWaysProduct = (totalWaysProduct * getInverse(currentWaysArray[u])) % MOD;

    currentWaysArray[u] = newWays;

    if(currentWaysArray[u] == 0) zeroWaysCount++;
    else totalWaysProduct = (totalWaysProduct * currentWaysArray[u]) % MOD;
}

void solveTestCase() {
    precomputeFactorials();

    int N;
    ll R;
    if(!(cin >> N >> R)) return;

    neighbourList.assign(N + 1, vector<int>());
    for(int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }

    timeCounter = 0;
    performDFS(1, 0);

    updateMaxTree(1, 1, N, timeIn[1], timeOut[1]);

    cachedRemainingCapacity[1] = R;
    cachedRemainingSize[1] = subtreeSize[1];
    updateSumTree(1, 1, N, timeIn[1], R, subtreeSize[1]);

    for(int i = 1; i <= N; i++) currentWaysArray[i] = 1;
    
    updateWaysForNode(1, calculateWays(R, subtreeSize[1]));

    cout << (zeroWaysCount > 0 ? 0 : totalWaysProduct) << endl;

    int Q;
    cin >> Q;
    while(Q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int u;
            ll v;
            cin >> u >> v;

            int P = queryNearestAncestor(1, 1, N, timeIn[u], timeOut[u]);

            ValueNode childrenSum = querySumTree(1, 1, N, timeIn[u] + 1, timeOut[u]);

            ll currentRemainingCapacity = v - childrenSum.capacity;
            int currentRemainingSize = subtreeSize[u] - childrenSum.size;

            cachedRemainingCapacity[u] = currentRemainingCapacity;
            cachedRemainingSize[u] = currentRemainingSize;

            updateSumTree(1, 1, N, timeIn[u], currentRemainingCapacity, currentRemainingSize);

            addToSumTree(1, 1, N, timeIn[P], -currentRemainingCapacity, -currentRemainingSize);
            cachedRemainingCapacity[P] -= currentRemainingCapacity;
            cachedRemainingSize[P] -= currentRemainingSize;

            updateMaxTree(1, 1, N, timeIn[u], timeOut[u]);

            updateWaysForNode(u, calculateWays(currentRemainingCapacity, currentRemainingSize));
            updateWaysForNode(P, calculateWays(cachedRemainingCapacity[P], cachedRemainingSize[P]));

        } else {
            int u;
            cin >> u;

            updateMaxTree(1, 1, N, timeIn[u], 0);

            int P = queryNearestAncestor(1, 1, N, timeIn[u], timeOut[u]);

            ll currentRemainingCapacity = cachedRemainingCapacity[u];
            int currentRemainingSize = cachedRemainingSize[u];

            addToSumTree(1, 1, N, timeIn[P], currentRemainingCapacity, currentRemainingSize);
            cachedRemainingCapacity[P] += currentRemainingCapacity;
            cachedRemainingSize[P] += currentRemainingSize;

            updateSumTree(1, 1, N, timeIn[u], 0, 0);
            cachedRemainingCapacity[u] = 0;
            cachedRemainingSize[u] = 0;

            updateWaysForNode(u, 1);
            updateWaysForNode(P, calculateWays(cachedRemainingCapacity[P], cachedRemainingSize[P]));
        }

        cout << (zeroWaysCount > 0 ? 0 : totalWaysProduct) << endl;
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

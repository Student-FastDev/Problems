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
const ll MAX_N = 100005;
const ll MAX_A = 100005;
const ll MOD = 998244353; // 998244353

int N;
int A[MAX_N];
vector<int> neighbourList[MAX_N];

long long phiValues[MAX_A];
vector<int> divisorsArray[MAX_A];
vector<int> nodesG[MAX_A];

bool isCandidate[MAX_N];
bool visitedDFS[MAX_N];
int subtreeSize[MAX_N];

long long F[MAX_A];
long long twoInverse;

long long fastPower(long long powerBase, long long powerExponent) {
    long long resultValue = 1;
    powerBase %= MOD;
    while (powerExponent > 0) {
        if (powerExponent % 2 == 1) resultValue = (resultValue * powerBase) % MOD;
        powerBase = (powerBase * powerBase) % MOD;
        powerExponent /= 2;
    }
    return resultValue;
}

long long modInverse(long long N) {
    return fastPower(N, MOD - 2);
}

void phiSieve() {
    for (int i = 0; i < MAX_A; ++i) phiValues[i] = i;
    for (int i = 2; i < MAX_A; ++i) {
        if (phiValues[i] == i) {
            for (int j = i; j < MAX_A; j += i) {
                phiValues[j] -= phiValues[j] / i;
            }
        }
    }
}

void precomputeDivisors() {
    for (int i = 1; i < MAX_A; ++i) {
        for (int j = i; j < MAX_A; j += i) {
            divisorsArray[j].push_back(i);
        }
    }
}

long long currentSumDistance;
long long currentSize;

int sizeDFS(int u, int p) {
    subtreeSize[u] = 1;
    for (int v : neighbourList[u]) {
        if (v != p && visitedDFS[v]) {
            int childSize = sizeDFS(v, u);
            long long term = (long long)childSize * (currentSize - childSize) % MOD;
            currentSumDistance = (currentSumDistance + term) % MOD;
            subtreeSize[u] += childSize;
        }
    }
    return subtreeSize[u];
}

void solveTestCase() {
    phiSieve();
    precomputeDivisors();
    twoInverse = modInverse(2);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        for (int g : divisorsArray[A[i]]) {
            nodesG[g].push_back(i);
        }
    }
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }

    for (int g = 1; g < MAX_A; ++g) {
        if (nodesG[g].empty()) continue;

        vector<int>& V = nodesG[g];
        for (int u : V) isCandidate[u] = true;

        long long currentF = 0;

        for (int u : V) {
            if (isCandidate[u]) {
                vector<int> componentNodes;
                vector<int> queueVector;
                queueVector.push_back(u);
                isCandidate[u] = false;
                
                int headIndex = 0;
                while(headIndex < size(queueVector)){
                    int currentElement = queueVector[headIndex++];
                    componentNodes.push_back(currentElement);
                    for(int neighbor : neighbourList[currentElement]){
                        if(isCandidate[neighbor]){
                            isCandidate[neighbor] = false;
                            queueVector.push_back(neighbor);
                        }
                    }
                }
                
                currentSize = size(componentNodes);
                if (currentSize > 1) {
                    for(int node : componentNodes) visitedDFS[node] = true;
                    
                    currentSumDistance = 0;
                    sizeDFS(u, 0);

                    long long K = currentSize;
                    long long pairsNumber = (K * (K - 1)) % MOD;
                    pairsNumber = (pairsNumber * twoInverse) % MOD;
                    
                    long long sumLength = (currentSumDistance + pairsNumber) % MOD;
                    currentF = (currentF + sumLength) % MOD;

                    for(int node : componentNodes) visitedDFS[node] = false;
                }
            }
        }
        F[g] = currentF;
        for (int u : V) isCandidate[u] = false;
    }
    
    long long totalSum = 0;
    for (int g = 1; g < MAX_A; ++g) {
        if (F[g] > 0) {
            totalSum = (totalSum + phiValues[g] * F[g]) % MOD;
        }
    }
    
    if (totalSum < 0) totalSum += MOD;

    cout << totalSum << endl;
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

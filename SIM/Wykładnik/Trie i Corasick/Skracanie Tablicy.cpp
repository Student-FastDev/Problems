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
const ll MAX_N = 6e6+7;
const ll MOD = 1e9+7; // 998244353

const int MAX_BITS = 30;

struct Node {
    int nodeChildren[2];
    int maxIndex;
};

Node trieArray[MAX_N];
int nodesCount = 1;

void initializeNode(int u) {
    trieArray[u].nodeChildren[0] = trieArray[u].nodeChildren[1] = 0;
    trieArray[u].maxIndex = -1;
}

void insertTrie(int value, int index) {
    int currentStatus = 1;
    trieArray[currentStatus].maxIndex = max(trieArray[currentStatus].maxIndex, index);
    
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        int bit = (value >> i) & 1;
        if (!trieArray[currentStatus].nodeChildren[bit]) {
            nodesCount++;
            initializeNode(nodesCount);
            trieArray[currentStatus].nodeChildren[bit] = nodesCount;
        }
        currentStatus = trieArray[currentStatus].nodeChildren[bit];
        trieArray[currentStatus].maxIndex = max(trieArray[currentStatus].maxIndex, index);
    }
}

int queryTrie(int value, int K) {
    int currentStatus = 1;
    int bestIndex = -1;
    
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        if (currentStatus == 0) break;
        
        int bitValue = (value >> i) & 1;
        int bitK = (K >> i) & 1;
        
        if (bitK == 0) {
            int oneValue = 1 - bitValue;
            if (trieArray[currentStatus].nodeChildren[oneValue]) bestIndex = max(bestIndex, trieArray[trieArray[currentStatus].nodeChildren[oneValue]].maxIndex);
            currentStatus = trieArray[currentStatus].nodeChildren[bitValue];
        } else {
            int oneValue = 1 - bitValue;
            currentStatus = trieArray[currentStatus].nodeChildren[oneValue];
        }
    }
    if (currentStatus != 0) bestIndex = max(bestIndex, trieArray[currentStatus].maxIndex);
    
    return bestIndex;
}

void solveTestCase() {
    int N, K; 
    cin >> N >> K;
    
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    if (K == 0) {
        cout << 1 << endl;
        return;
    }

    nodesCount = 1;
    initializeNode(1);
    
    int minimumLength = N + 1;
    
    for (int i = 0; i < N; ++i) {
        if (i > 0) { 
            int j = queryTrie(A[i], K);
            if (j != -1) {
                minimumLength = min(minimumLength, i - j + 1);
            }
        }
        insertTrie(A[i], i);
    }
    
    if (minimumLength > N) cout << -1 << endl;
    else cout << minimumLength << endl;
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
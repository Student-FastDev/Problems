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

typedef unsigned int uint;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  int((X).size())

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

static inline int readUInt(){
    int c = getc_unlocked(stdin);
    while(c < '0') c = getc_unlocked(stdin);
    int X = 0;
    for(; c>='0'; c=getc_unlocked(stdin))
        X = X*10 + (c - '0');
    return X;
}

static const int MAX_BITS = 30;
static const int MAX_PAIRS = 1000000 + 5;
static const int MAX_NODES = MAX_PAIRS * (MAX_BITS+1);

int trieNext[MAX_NODES][2];
int nodeCount;

inline void trieInit(){
    nodeCount = 1;
    trieNext[0][0] = trieNext[0][1] = -1;
}

inline void trieInsert(uint X){
    int V = 0;
    for(int b = MAX_BITS; b >= 0; --b){
        int currentBit = (X >> b) & 1;
        int &nextValue = trieNext[V][currentBit];
        if(nextValue < 0){
            nextValue = nodeCount;
            trieNext[nodeCount][0] = trieNext[nodeCount][1] = -1;
            ++nodeCount;
        }
        V = nextValue;
    }
}

inline uint trieQueryMax(uint X){
    int V = 0;
    uint finalResult = 0;
    for(int b = MAX_BITS; b >= 0; --b){
        int currentBit = (X >> b) & 1;
        int want = currentBit ^ 1;
        if(trieNext[V][want] >= 0){
            finalResult |= (1u << b);
            V = trieNext[V][want];
        } else {
            V = trieNext[V][currentBit];
        }
    }
    return finalResult;
}

void solveTestCase() {
    int N = readUInt();
    int M = readUInt();

    vector<uint> A(N), B(M);
    for(int i = 0; i < N; ++i) A[i] = readUInt();
    for(int j = 0; j < M; ++j) B[j] = readUInt();

    vector<uint> prefixA(N+1, 0), prefixB(M+1, 0);
    for(int i = 0; i < N; ++i) prefixA[i + 1] = prefixA[i] ^ A[i];
    for(int j = 0; j < M; ++j) prefixB[j + 1] = prefixB[j] ^ B[j];

    static uint oddA[MAX_PAIRS], oddB[MAX_PAIRS];
    int subarraysA = 0;
    uint bestEvenA = 0;

    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
            uint X = prefixA[j+1] ^ prefixA[i];
            if(((j-i+1)&1)==1){
                oddA[subarraysA++] = X;
            } else {
                bestEvenA = max(bestEvenA, X);
            }
        }
    }

    int subarraysB = 0;
    uint bestEvenB = 0;
    for(int i = 0; i < M; i++){
        for(int j = i; j < M; j++){
            uint X = prefixB[j+1] ^ prefixB[i];
            if(((j - i + 1) & 1)==1){
                oddB[subarraysB++] = X;
            } else {
                bestEvenB = max(bestEvenB, X);
            }
        }
    }

    uint bestOddOdd = 0;
    if(subarraysA < subarraysB){
        trieInit();
        for(int i = 0; i < subarraysA; i++) trieInsert(oddA[i]);
        for(int j = 0; j < subarraysB; j++){
            bestOddOdd = max(bestOddOdd, trieQueryMax(oddB[j]));
        }
    } else {
        trieInit();
        for(int j = 0; j < subarraysB; j++) trieInsert(oddB[j]);
        for(int i = 0; i < subarraysA; i++){
            bestOddOdd = max(bestOddOdd, trieQueryMax(oddA[i]));
        }
    }

    uint finalAnswer = max({0u, bestEvenA, bestEvenB, bestOddOdd});
    cout << finalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

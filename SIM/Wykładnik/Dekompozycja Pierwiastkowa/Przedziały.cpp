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
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; 

//
template <typename T>
inline void fastRead(T &n) {
    register char c = 0;
    T sign = 1;
    while (c < 33) c = getchar_unlocked();
    
    if (c == 45) {
        sign = -1;
        c = getchar_unlocked();
    }
    
    n = 0;
    while (c > 32) {
        n = (n * 10) + (c - 48);
        c = getchar_unlocked();
    }
    n *= sign;
}

template <typename T>
inline void fastWrite(T n) {
    if (n == 0) {
        putchar_unlocked('48');
        putchar_unlocked('\n');
        return;
    }
    
    if (n < 0) {
        putchar_unlocked('-');
        n = -n;
    }

    char tab[40];
    int p = 0;
    while (n != 0) {
        tab[p++] = (char)((n % 10) + 48);
        n /= 10;
    }
    
    while (p--) {
        putchar_unlocked(tab[p]);
    }
    putchar_unlocked('\n');
}

//

struct Fenwick {
    vector<ll> treeArray;
    int n;
    Fenwick(int n) : treeArray(n+1, 0), n(n) {}
    
    inline void update(int index, ll value) {
        while(index <= n) {
            treeArray[index] += value;
            index += index & -index;
        }
    }
    
    inline ll query(int index) {
        ll S = 0;
        while(index > 0) {
            S += treeArray[index];
            index -= index & -index;
        }
        return S;
    }
};

void solveTestCase() {
    int N;
    fastRead(N);
    
    vector<ll> A(N+1);
    for(int i = 1; i <= N; i++) fastRead(A[i]);
    
    vector<int> L(N+1), R(N+1);
    for(int i = 1; i <= N; i++){
        fastRead(L[i]);
        fastRead(R[i]);
    }
    
    int Q;
    fastRead(Q);

    Fenwick treeArray(N);
    for (int i = 1; i <= N; i++) {
        treeArray.update(i, A[i]);
    }

    int bI = max(1, (int)(sqrt(N) * 0.6)); 
    int numberBI = (N + bI - 1) / bI;

    vector<int> flatCountBlocks((N + 2) * numberBI, 0);
    vector<__int128_t> blockSum(numberBI, 0);
    vector<int> tempDiff(N + 2, 0);

    for(int b = 0; b < numberBI; ++b){
        int iL = b * bI + 1;
        int iR = min(N, (b+1) * bI);
        
        for(int i = iL; i <= iR; ++i){
            tempDiff[L[i]]++;
            if(R[i] + 1 <= N) tempDiff[R[i] + 1]--;
        }
        
        int currentValue = 0;
        __int128_t S = 0;
        
        int* blockPointer = flatCountBlocks.data() + numberBI + b; 
        
        for(int j = 1; j <= N; ++j){
            currentValue += tempDiff[j];
            tempDiff[j] = 0;
            
            *blockPointer = currentValue; 
            blockPointer += numberBI;
            
            if(currentValue) S += (__int128_t)currentValue * (__int128_t)A[j];
        }
        tempDiff[N+1] = 0;
        blockSum[b] = S;
    }

    for(int p = 0; p < Q; ++p){
        int operatorType;
        fastRead(operatorType);
        
        if(operatorType == 1){
            int K;
            ll X;
            fastRead(K);
            fastRead(X);
            
            ll currentDelta = X - A[K];
            if(currentDelta != 0){
                A[K] = X;
                treeArray.update(K, currentDelta);
                
                int* countPointer = &flatCountBlocks[K * numberBI];
                for(int b = 0; b < numberBI; ++b){
                    int mutliplicator = countPointer[b];
                    if(mutliplicator) {
                        blockSum[b] += (__int128_t)mutliplicator * (__int128_t)currentDelta;
                    }
                }
            }
        } else if(operatorType == 2){
            int l, r;
            fastRead(l);
            fastRead(r);
            
            int bL = (l - 1) / bI;
            int bR = (r - 1) / bI;
            __int128_t finalAnswer = 0;
            
            if(bL == bR){
                for(int i = l; i <= r; ++i)finalAnswer += (__int128_t) (treeArray.query(R[i]) - treeArray.query(L[i] - 1));
            } else {
                int endBl = (bL + 1) * bI; 
                if(endBl > N) endBl = N;

                for(int i = l; i <= endBl; ++i) finalAnswer += (__int128_t) (treeArray.query(R[i]) - treeArray.query(L[i] - 1));
                
                int startBr = bR * bI + 1;
                for(int i = startBr; i <= r; ++i) finalAnswer += (__int128_t) (treeArray.query(R[i]) - treeArray.query(L[i] - 1));
                
                for(int b = bL + 1; b < bR; ++b) finalAnswer += blockSum[b];
            }
            fastWrite(finalAnswer); 
        }
    }
}

int main() {    
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}

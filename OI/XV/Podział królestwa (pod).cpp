// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.isFirst,o){return o<<'('<<P.isFirst<<", "<<P.second <<')';}
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
const ll MOD = 1e9+7; 

int neighbourMask[27]; 
int N, M;

void solveTestCase() {
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        neighbourMask[u] |= (1 << v);
        neighbourMask[v] |= (1 << u);
    }

    vector<int> P(N);
    P[0] = 0; 

    int zeroNeeded = N / 2 - 1;
    int oneNeeded = N / 2;

    for (int i = 1; i < N; i++) {
        if (i <= zeroNeeded) P[i] = 0;
        else P[i] = 1;
    }

    int minimumCut = 1e9;
    ll bestMask = 0;

    do {
        int maskOnes = 0; 
        
        for (int i = 1; i < N; i++) if (P[i]) maskOnes |= (1 << i);
        int currentCut = 0;
        
        int temporaryMask = maskOnes;
        while(temporaryMask) {
            int u = __builtin_ctz(temporaryMask);
            currentCut += __builtin_popcount(neighbourMask[u] & ~maskOnes);
            if (currentCut >= minimumCut) break; 
            temporaryMask ^= (1 << u);
        }

        if (currentCut < minimumCut) {
            minimumCut = currentCut;
            bestMask = maskOnes;
        }

    } while (next_permutation(P.begin() + 1, P.end()));

    bool isFirst = true;
    for (int i = 0; i < N; i++) {
        if (!((bestMask >> i) & 1)) {
            if (!isFirst) cout << " ";
            cout << i + 1;
            isFirst = false;
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
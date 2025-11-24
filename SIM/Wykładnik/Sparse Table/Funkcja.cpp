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
typedef pair<int,int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(),(x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // or 998244353

const ll M = 1000000069LL;
const ll C = 620689698LL;

// ===== FAST I/O =====
inline void putUI(unsigned int n) {
    if (n == 0) {
        putc_unlocked('0', stdout);
        return;
    }
    char tab[12];
    int p = 0;
    while (n != 0) {
        tab[p++] = (n % 10) + '0';
        n /= 10;
    }
    while (p--) putc_unlocked(tab[p], stdout);
}

inline void readUI(int *n) {
    register char c = 0;
    while (c < 33) c = getc_unlocked(stdin);
    (*n) = 0;
    while (c > 32) {
        (*n) = (*n) * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
}
// ====================

inline int apply(int a, int b) {
    ll result = C * (ll)a - (C - 1) * (ll)b;
    result %= M;
    if (result < 0) result += M;
    return (int)result;
}

void solveTestCase() {
    int N, Q;
    readUI(&N);
    readUI(&Q);

    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        readUI(&A[i]);
        if (A[i] >= (int)M) A[i] %= (int)M;
    }

    int LOG = 1;
    while ((1 << LOG) <= N) ++LOG;
    vector<vector<int>> sparseTable(LOG, vector<int>(N));
    for (int i = 0; i < N; ++i) sparseTable[0][i] = A[i];
    for (int K = 1; K < LOG; ++K) {
        int currentLength = 1 << K;
        int halfLength = 1 << (K - 1);
        for (int i = 0; i + currentLength - 1 < N; ++i) {
            sparseTable[K][i] = apply(sparseTable[K-1][i], sparseTable[K-1][i + halfLength]);
        }
    }

    vector<int> logarithmTable(N + 1);
    logarithmTable[1] = 0;
    for (int i = 2; i <= N; ++i)
        logarithmTable[i] = logarithmTable[i/2] + 1;

    for (int p = 0; p < Q; ++p) {
        int L, R;
        readUI(&L);
        readUI(&R);
        --L; --R;

        int currentLength = R - L + 1;
        int K = logarithmTable[currentLength];
        int leftValue = sparseTable[K][L];
        int rightValue = sparseTable[K][R - (1 << K) + 1];
        int finalAnswer = apply(leftValue, rightValue);

        putUI(finalAnswer);
        putc_unlocked('\n', stdout);
    }
}

int main() {
    int T = 1;
    while (T--) {
        solveTestCase();
    }
    return 0;
}

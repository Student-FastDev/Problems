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

const ll INF = 9223372036854775806LL;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;

// ===== FAST I/O =====
static inline int readChar() {
    int c = getchar_unlocked();
    return c;
}
static inline long long readLongLong() {
    long long x = 0;
    int c = readChar();
    while (c <= ' ') c = readChar();
    int neg = 0;
    if (c == '-') { neg = 1; c = readChar(); }
    for (; c > ' '; c = readChar()) {
        x = x * 10 + (c - '0');
    }
    return neg ? -x : x;
}
static inline int readInt() {
    return (int)readLongLong();
}

inline void putChar(int c) {
    putchar_unlocked((char)c);
}

inline void writeLongLong(long long x) {
    if (x == 0) {
        putChar('0');
        return;
    }
    if (x < 0) {
        putChar('-');
        x = -x;
    }
    char buf[24];
    int p = 0;
    while (x > 0) {
        buf[p++] = char('0' + (x % 10));
        x /= 10;
    }
    while (p--) putChar(buf[p]);
}

inline void writeEndl() { putChar('\n'); }
// ====================

void solveTestCase() {
    int N = readInt();
    vector<int> A(N);
    for (int i = 0; i < N - 1; ++i) {
        A[i] = readInt();
        --A[i];
    }
    A[N-1] = N - 1;

    vector<int> logarithmArray(N + 1);
    logarithmArray[1] = 0;
    for (int i = 2; i <= N; ++i) logarithmArray[i] = logarithmArray[i/2] + 1;
    int K = logarithmArray[N] + 1;

    vector<vector<int>> sparseTable(K, vector<int>(N));
    for (int i = 0; i < N; ++i) sparseTable[0][i] = i;
    for (int k = 1; k < K; ++k) {
        int length = 1 << k;
        for (int i = 0; i + length <= N; ++i) {
            int firstI = sparseTable[k-1][i];
            int secondI = sparseTable[k-1][i + (1 << (k-1))];
            sparseTable[k][i] = (A[firstI] >= A[secondI]) ? firstI : secondI;
        }
    }

    auto indexRMQ = [&](int l, int r) {
        int length = r - l + 1;
        int k = logarithmArray[length];
        int firstI = sparseTable[k][l];
        int secondI = sparseTable[k][r - (1 << k) + 1];
        return (A[firstI] >= A[secondI]) ? firstI : secondI;
    };

    vector<ll> DP(N, 0);
    ll finalAnswer = 0;
    DP[N-1] = 0;
    for (int i = N - 2; i >= 0; --i) {
        int m = indexRMQ(i + 1, A[i]);
        DP[i] = DP[m] - (ll)(A[i] - m) + (ll)(N - i - 1);
        finalAnswer += DP[i];
    }

    writeLongLong(finalAnswer);
    writeEndl();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}

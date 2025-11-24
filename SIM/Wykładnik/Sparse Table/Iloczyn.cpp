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
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll moduloNumber = 1e9+7; // 998244353

struct DisjointSparseTable {
    int twoPowerValue;
    int levelsNumber;
    int moduloNumber;
    vector<vector<ll>> sparseTable;

    DisjointSparseTable() = default;

    DisjointSparseTable(const vector<ll> &A, int modulo) {
        moduloNumber = modulo;
        int arraySize = (int)size(A);
        int LOG = 0;
        while ((1 << LOG) < arraySize) ++LOG;
        twoPowerValue = 1 << LOG;
        levelsNumber = LOG + 1;
        sparseTable.assign(levelsNumber, vector<ll>(twoPowerValue, 1));

        for (int i = 0; i < arraySize; ++i) sparseTable[0][i] = A[i] % moduloNumber;

        for (int h = 1; h < levelsNumber; ++h) {
            int range = 1 << h;
            int half = range >> 1;
            for (int i = half; i < twoPowerValue; i += range) {
                sparseTable[h][i - 1] = (i - 1 < arraySize) ? sparseTable[0][i - 1] : 1;
                for (int j = i - 2; j >= i - half; --j) {
                    ll right = sparseTable[h][j + 1];
                    ll current = (j < arraySize) ? sparseTable[0][j] : 1;
                    sparseTable[h][j] = (right * current) % moduloNumber;
                }
                sparseTable[h][i] = (i < arraySize) ? sparseTable[0][i] : 1;
                for (int j = i + 1; j < i + half; ++j) {
                    ll left = sparseTable[h][j - 1];
                    ll current = (j < arraySize) ? sparseTable[0][j] : 1;
                    sparseTable[h][j] = (left * current) % moduloNumber;
                }
            }
        }
    }

    ll query(int l, int r) const {
        if (l == r) return sparseTable[0][l];
        unsigned x = (unsigned)(l ^ r);
        int h = 32 - __builtin_clz(x);
        return (sparseTable[h][l] * sparseTable[h][r]) % moduloNumber;
    }
};

void solveTestCase() {
    int N, P, Q;
    cin >> N >> P >> Q;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    DisjointSparseTable DST(A, P);

    int sizeB = Q / 64 + 2;
    vector<int> B(sizeB);
    for (int i = 0; i < sizeB; ++i) cin >> B[i];

    ll previousAnswer = -1;
    int leftI = 0, rightI = 0;

    for (int i = 0; i < Q; ++i) {
        ll x = (previousAnswer + 1) % P;
        if (i % 64 == 0) {
            leftI = (B[i / 64] + x) % N;
            rightI = (B[i / 64 + 1] + x) % N;
        } else {
            leftI = (leftI + x) % N;
            rightI = (rightI + x) % N;
        }
        if (leftI > rightI) swap(leftI, rightI);
        previousAnswer = DST.query(leftI, rightI);
    }

    cout << (previousAnswer + 1) % P << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

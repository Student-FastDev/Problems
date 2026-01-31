#pragma GCC optimize("O3,unroll-loops,fast-math")
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353
const ll BASE = 911382629;

vector<ll> powBase;

inline void putUI(unsigned int n) {
    if(n == 0) {
        putc_unlocked(48, stdout);
        return;
    }
    char tab[12];
    int p = 0;
    while(n != 0) {
        tab[p++] = (n % 10) + 48;
        n /= 10;
    }
    while(p--) 
        putc_unlocked(tab[p], stdout);
}

inline void readINT(int *n) {
    register char c = 0, znak_liczby = 1;
    while (c < 33) c = getc_unlocked(stdin);
    if(c == 45) { znak_liczby = -1; c = getc_unlocked(stdin); }
    (*n) = 0;
    while (c > 32) { (*n) = (*n) * 10 + c - 48; c = getc_unlocked(stdin); }
    (*n) *= znak_liczby;
}

class SegmentTree {
    struct Node {
        ll hash;
        int length;
    };
    vector<Node> treeArray;
    int N;
    vector<int>& numberArray;

    Node combine(const Node& a, const Node& b) {
        if (a.length == 0) return b;
        if (b.length == 0) return a;
        return {
            (a.hash * powBase[b.length] + b.hash) % MOD,
            a.length + b.length
        };
    }

public:
    SegmentTree(vector<int>& numberArray) : numberArray(numberArray), N(size(numberArray)) {
        treeArray.resize(2 * N);
        for (int i = 0; i < N; ++i) {
            treeArray[i + N] = {numberArray[i], 1};
        }
        for (int i = N - 1; i > 0; --i) {
            treeArray[i] = combine(treeArray[2*i], treeArray[2*i+1]);
        }
    }

    void update(int position) {
        position += N;
        treeArray[position] = {numberArray[position - N], 1};
        for (position >>= 1; position > 0; position >>= 1) {
            treeArray[position] = combine(treeArray[2*position], treeArray[2*position+1]);
        }
    }

    ll getHash(int L, int r) {
        Node resL{}, resR{};
        for (L += N, r += N; L <= r; L >>= 1, r >>= 1) {
            if (L % 2 == 1) resL = combine(resL, treeArray[L++]);
            if (r % 2 == 0) resR = combine(treeArray[r--], resR);
        }
        return combine(resL, resR).hash;
    }
};

void solveTestCases() {
    int N, M;
    readINT(&N); readINT(&M);

    powBase.resize(N + 1);
    powBase[0] = 1;
    for (int i = 1; i <= N; ++i)
        powBase[i] = (powBase[i-1] * BASE) % MOD;

    vector<int> current(N);
    vector<vector<int>> position(N);
    for (int i = 0; i < N; ++i) {
        current[i] = i;
        position[i].push_back(i);
    }

    SegmentTree ST(current);
    int P = N;

    auto mergeSets = [&](int a, int b) {
        if (current[a] == current[b]) return;
        int currentA = current[a], currentB = current[b];
        if (size(position[currentA]) < size(position[currentB])) {
            swap(currentA, currentB);
            swap(a, b);
        }
        for (int P : position[currentB]) {
            current[P] = currentA;
            ST.update(P);
        }
        position[currentA].insert(position[currentA].end(), position[currentB].begin(), position[currentB].end());
        position[currentB].clear();
        P--;
    };

    auto firstDifference = [&](int X, int Y, int length) {
        int left = 0, right = length - 1, answer = length;
        while (left <= right) {
            int mid = (left + right) / 2;
            ll Hx = ST.getHash(X, X + mid);
            ll Hy = ST.getHash(Y, Y + mid);
            if (Hx == Hy) {
                left = mid + 1;
            } else {
                answer = mid;
                right = mid - 1;
            }
        }
        return answer;
    };

    for (int i = 1; i <= M; ++i) {
        ll A, B, C;
        readINT((int*)&A); readINT((int*)&B); readINT((int*)&C);

        if (P == 1) {
            putUI(1);
            putc_unlocked('\n', stdout);
            continue;
        }

        int Xi = (A + P) % N;
        int Yi = (B + (ll)P * i) % N;
        int Li = (C % (N - max(Xi, Yi))) + 1;

        int X = Xi, Y = Yi, L = Li;
        while (L > 0) {
            int current = firstDifference(X, Y, L);
            if (current == L) break;
            mergeSets(X + current, Y + current);
            L -= current + 1;
            X += current + 1;
            Y += current + 1;
        }
        putUI(P);
        putc_unlocked('\n', stdout);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    solveTestCases();
    return 0;
}

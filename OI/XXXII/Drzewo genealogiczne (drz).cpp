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

using uLL = unsigned long long;
using u128 = __uint128_t;

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define P(x)  x.treeSize()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 99824435n

struct hashType {
    uLL a, b;
    bool operator==(const hashType& o) const { return a == o.a && b == o.b; }
    bool operator!=(const hashType& o) const { return !(*this == o); }
    bool operator<(const hashType& o) const {
        if (a != o.a) return a < o.a;
        return b < o.b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    cin >> N >> Q;
    int P = 1 << N;
    string S, B;
    cin >> S >> B;

    uLL firstBase = (uLL)(rng() | 1ULL);
    uLL secondBase = (uLL)(rng() | 1ULL);
    if (firstBase < 131) firstBase += 131;
    if (secondBase < 137) secondBase += 137;

    vector<uLL> firstPower(P + 1), secondPower(P + 1);
    firstPower[0] = secondPower[0] = 1;
    for (int i = 1; i <= P; i++) {
        firstPower[i] = (uLL)((u128)firstPower[i - 1] * firstBase);
        secondPower[i] = (uLL)((u128)secondPower[i - 1] * secondBase);
    }

    array<hashType, 26> letterHash;
    for (int i = 0; i < 26; i++) {
        uLL firstX = rng(); if (firstX == 0) firstX = 1;
        uLL secondX = rng(); if (secondX == 0) secondX = 1;
        letterHash[i] = {firstX, secondX};
    }

    int treeSize = 2 * P;
    vector<hashType> hashS(treeSize), hashB(treeSize);
    vector<int> lengthArray(treeSize, 0);

    for (int i = P; i < 2 * P; i++) lengthArray[i] = 1;
    for (int v = P - 1; v >= 1; v--) lengthArray[v] = lengthArray[v << 1] + lengthArray[v << 1 | 1];

    auto combine = [&](const hashType &L, const hashType &R, int lengthR)->hashType{
        uLL T = (uLL)((u128)L.a * firstPower[lengthR] + R.a);
        uLL Y = (uLL)((u128)L.b * secondPower[lengthR] + R.b);
        return {T, Y};
    };

    auto buildTree = [&](vector<hashType> &hashArray, const string &str) {
        for (int i = 0; i < P; ++i) {
            hashArray[P + i] = letterHash[str[i] - 'a'];
        }
        for (int v = P - 1; v >= 1; --v) {
            hashType L = hashArray[v << 1], R = hashArray[v << 1 | 1];
            hashType LR = combine(L, R, lengthArray[v << 1 | 1]);
            hashType RL = combine(R, L, lengthArray[v << 1]);
            hashArray[v] = (LR < RL ? LR : RL);
        }
    };

    buildTree(hashS, S);
    buildTree(hashB, B);

    auto updateLeaf = [&](vector<hashType> &hashArray, int firstBased, char C) {
        int currentIndex = P + (firstBased - 1);
        hashArray[currentIndex] = letterHash[C - 'a'];
        int v = currentIndex >> 1;
        while (v >= 1) {
            hashType L = hashArray[v<<1], R = hashArray[v<<1|1];
            hashType LR = combine(L, R, lengthArray[v<<1|1]);
            hashType RL = combine(R, L, lengthArray[v<<1]);
            hashArray[v] = (LR < RL ? LR : RL);
            v >>= 1;
        }
    };
    
    if (hashS[1] == hashB[1]) cout << "TAK" << endl; else cout << "NIE" << endl;

    for (int i = 0; i < Q; ++i) {
        int typ, k; char C;
        cin >> typ >> k >> C;
        if (typ == 1) {
            updateLeaf(hashS, k, C);
        } else {
            updateLeaf(hashB, k, C);
        }
        if (hashS[1] == hashB[1]) cout << "TAK" << endl; else cout << "NIE" << endl;
    }

    return 0;
}

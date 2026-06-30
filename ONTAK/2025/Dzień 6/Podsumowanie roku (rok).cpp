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
#define N(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 99824435n

const int MINUS_INF = -1;

class SegmentTree {
    int N;
    vector<int> treeArray;

public:
    SegmentTree(int O) {
        N = 1;
        while (N < O) N *= 2;
        treeArray.assign(2 * N, MINUS_INF);
    }

    void updateTree(int indexValue, int updateValue) {
        indexValue += N;
        treeArray[indexValue] = max(treeArray[indexValue], updateValue);
        while (indexValue > 1) {
            indexValue /= 2;
            treeArray[indexValue] = max(treeArray[2 * indexValue], treeArray[2 * indexValue + 1]);
        }
    }

    int queryTree(int L, int R) {
        L += N;
        R += N;
        int resultValue = MINUS_INF;
        while (L <= R) {
            if (L % 2 == 1) resultValue = max(resultValue, treeArray[L++]);
            if (R % 2 == 0) resultValue = max(resultValue, treeArray[R--]);
            L /= 2;
            R /= 2;
        }
        return resultValue;
    }
};


void solveTestCase() {
    int N, D, P, Q; cin >> N >> D >> P >> Q;
    string C; cin >> C;

    vector<int> S(N + 1);
    for (int i = 0; i < N; ++i) S[i + 1] = S[i] + (C[i] == 'Y');

    vector<long long> F(N + 1);
    for (int K = 0; K <= N; ++K) F[K] = 1LL * Q * S[K] - 1LL * P * K;

    vector<long long> uniqueF = F;
    sort(uniqueF.begin(), uniqueF.end());
    uniqueF.erase(unique(uniqueF.begin(), uniqueF.end()), uniqueF.end());

    unordered_map<long long, int> rankMap;
    for (int i = 0; i < (int)size(uniqueF); ++i) rankMap[uniqueF[i]] = i;

    int M = size(uniqueF);
    SegmentTree helperTree(M);

    vector<int> DP(N + 1);
    helperTree.updateTree(rankMap[F[0]], 0);

    for (int i = 1; i <= N; ++i) {
        DP[i] = DP[i - 1];

        if (i >= D) {
            int K = i - D;
            if (K > 0) helperTree.updateTree(rankMap[F[K]], DP[K]);
            int rankI = rankMap[F[i]];
            int maxPreviousDP = helperTree.queryTree(0, rankI);
            if (maxPreviousDP != MINUS_INF) DP[i] = max(DP[i], maxPreviousDP + 1);
        }
    }

    cout << DP[N] << endl;
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

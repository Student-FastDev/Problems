// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&phasesValue,auto p)->decltype(p.first,phasesValue){return phasesValue<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&phasesValue,auto x)->decltype(x.end(),phasesValue){phasesValue<<'{';int i=2;for(auto e:x)phasesValue<<(", ")+i<<e,i=0;return phasesValue<<'}';}
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

const ll INF = INT_MAX / 4;
const ll MAX_N = 1e6+123;
const ll MOD = 1e9+7; // 998244353

int N, K, L;
string S;
int A[MAX_N];
pii DP[MAX_N];

int solveDP(int penalty) {
    for (int i = 0; i <= N; ++i) DP[i] = make_pair(INF, INF);

    DP[0] = make_pair(0, 0);

    for (int i = 0; i < N; ++i) {
        pii firstCandidate = make_pair(DP[i].first + A[i], DP[i].second);
        if (DP[i + 1] > firstCandidate)
            DP[i + 1] = firstCandidate;

        int to = min(N, i + L);
        pii secondCandidate = make_pair(DP[i].first + penalty, DP[i].second + 1);
        if (DP[to] > secondCandidate)
            DP[to] = secondCandidate;
    }
    return DP[N].second;
}

int solveOneSide() {
    int leftRange = 0, rightRange = N;
    int finalResult = 0;

    while (leftRange <= rightRange) {
        int mid = (leftRange + rightRange) >> 1;
        if (solveDP(mid) > K) {
            finalResult = mid;
            leftRange = mid + 1;
        } else {
            rightRange = mid - 1;
        }
    }

    if (solveDP(finalResult) <= K) return 0;

    solveDP(finalResult + 1);
    return DP[N].first - (finalResult + 1) * 1LL * K;
}

void solveTestCase() {
    cin >> N >> K >> L >> S;
    int outputAnswer = INF;

    for (int i = 0; i < N; ++i) A[i] = islower(S[i]) ? 1 : 0;
    outputAnswer = min(outputAnswer, solveOneSide());

    for (int i = 0; i < N; ++i) A[i] = isupper(S[i]) ? 1 : 0;
    outputAnswer = min(outputAnswer, solveOneSide());

    cout << outputAnswer << endl;
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

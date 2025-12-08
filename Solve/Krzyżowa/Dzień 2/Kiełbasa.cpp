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
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

ll getDifference(int leftRange, int rightRange, vector<ll>& P) {
    ll currentValue = P[rightRange] - P[leftRange - 1];
    if (leftRange % 2 != 0) currentValue = -currentValue;
    return currentValue;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<int> A(N + 1);
    ll totalSum = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        totalSum += A[i];
    }

    vector<ll> P(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        ll currentValue = A[i];
        if (i % 2 != 0) currentValue = -currentValue;
        P[i] = P[i - 1] + currentValue;
    }

    ll differenceValue = 0;

    if (N % 2 != 0) differenceValue = getDifference(1, N, P);
    else {
        int K = N / 2;
        vector<ll> DP(K + 2, 0);

        for (int i = K; i >= 1; --i) {
            int leftRange = i;
            int rightRange = N - i + 1;

            ll valueBoth = (ll)A[leftRange] + A[rightRange] - DP[i + 1];
            ll valueLeft = A[leftRange] - getDifference(leftRange + 1, rightRange, P);
            ll valueRight = A[rightRange] - getDifference(leftRange, rightRange - 1, P);

            DP[i] = max({valueBoth, valueLeft, valueRight});
        }
        differenceValue = DP[1];
    }

    ll firstScore = (totalSum + differenceValue) / 2;
    ll secondScore = (totalSum - differenceValue) / 2;

    cout << firstScore << " " << secondScore << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

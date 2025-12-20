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

void solveTestCase() {
    ll N, K, P;
    cin >> N >> K >> P;

    if (K == 0) {
        for (int i = 0; i < P; ++i) {
            ll X;
            cin >> X;
            cout << '.';
        }
        cout << endl;
        return;
    }

    ll requiredOddSegments;
    if (N < 2 * K) {
        requiredOddSegments = 2 * K - N;
    } else {
        requiredOddSegments = N % 2;
    }

    bool isLargestSegmentEven = false;
    if (K - 1 >= requiredOddSegments) {
        ll minimumRemainingSum = requiredOddSegments + (K - 1 - requiredOddSegments) * 2;
        if (N - minimumRemainingSum >= 2) {
            isLargestSegmentEven = true;
        }
    }

    ll largestSegmentValue, countOfTwos, countOfOnes;
    if (isLargestSegmentEven) {
        ll minimumRemainingSum = requiredOddSegments + (K - 1 - requiredOddSegments) * 2;
        largestSegmentValue = N - minimumRemainingSum;
        countOfTwos = K - 1 - requiredOddSegments;
        countOfOnes = requiredOddSegments;
    } else {
        ll minimumRemainingSum = (requiredOddSegments - 1) + (K - 1 - (requiredOddSegments - 1)) * 2;
        largestSegmentValue = N - minimumRemainingSum;
        countOfTwos = K - requiredOddSegments;
        countOfOnes = requiredOddSegments - 1;
    }

    ll twosRangeEnd = largestSegmentValue + countOfTwos * 2;

    for (int i = 0; i < P; ++i) {
        ll X;
        cin >> X;
        char resultChar = '.';
        if (X <= largestSegmentValue) {
            if (X == largestSegmentValue) resultChar = 'X';
        } else if (X <= twosRangeEnd) {
            if ((X - largestSegmentValue) % 2 == 0) resultChar = 'X';
        } else {
            resultChar = 'X';
        }
        cout << resultChar;
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
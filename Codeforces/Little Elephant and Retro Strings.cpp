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

int N, K;
string S;

ll getRangeSum(const vector<ll>& prefixSumArray, int leftIndex, int rightIndex) {
    if (leftIndex > rightIndex) return 0;
    ll result = prefixSumArray[rightIndex];
    if (leftIndex > 0) result = (result - prefixSumArray[leftIndex - 1] + MOD) % MOD;
    return result;
}

void solveTestCase() {
    cin >> N >> K >> S;
    S = " " + S;

    vector<int> lastWhiteIndex(N + 1, 0);
    vector<int> lastBlackIndex(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        lastWhiteIndex[i] = (S[i] == 'W' ? i : lastWhiteIndex[i - 1]);
        lastBlackIndex[i] = (S[i] == 'B' ? i : lastBlackIndex[i - 1]);
    }

    vector<ll> countWhiteZero(N + 1, 0), countBlackZero(N + 1, 0);
    vector<ll> countWhiteOne(N + 1, 0), countBlackOne(N + 1, 0);
    vector<ll> prefixSumWhiteZero(N + 1, 0);
    vector<ll> prefixSumBlackOne(N + 1, 0);

    countWhiteZero[0] = 1;
    prefixSumWhiteZero[0] = 1;

    for (int i = 1; i <= N; ++i) {
        if (S[i] != 'B') {
            countWhiteZero[i] = (countWhiteZero[i - 1] + countBlackZero[i - 1]) % MOD;
        }

        if (S[i] != 'W') {
            int lowerIndex = max(i - K + 1, lastWhiteIndex[i]);
            int upperIndex = i - 1;
            countBlackZero[i] = getRangeSum(prefixSumWhiteZero, lowerIndex, upperIndex);
        }

        prefixSumWhiteZero[i] = (prefixSumWhiteZero[i - 1] + countWhiteZero[i]) % MOD;

        ll influxValue = 0;
        if (S[i] != 'W') {
            if (i >= K && lastWhiteIndex[i] <= i - K) {
                influxValue = countWhiteZero[i - K];
            }
        }

        if (S[i] != 'W') {
            countBlackOne[i] = (countBlackOne[i - 1] + countWhiteOne[i - 1]) % MOD;
            countBlackOne[i] = (countBlackOne[i] + influxValue) % MOD;
        }

        prefixSumBlackOne[i] = (prefixSumBlackOne[i - 1] + countBlackOne[i]) % MOD;

        if (S[i] != 'B') {
            int lowerIndex = max(i - K + 1, lastBlackIndex[i]);
            int upperIndex = i - 1;
            countWhiteOne[i] = getRangeSum(prefixSumBlackOne, lowerIndex, upperIndex);
        }
    }

    ll totalCombinations = 1;
    for (int i = 1; i <= N; ++i) {
        if (S[i] == 'X') totalCombinations = (totalCombinations * 2) % MOD;
    }

    ll invalidCombinations = (countWhiteZero[N] + countBlackZero[N]) % MOD;
    invalidCombinations = (invalidCombinations + countWhiteOne[N]) % MOD;
    invalidCombinations = (invalidCombinations + countBlackOne[N]) % MOD;

    cout << (totalCombinations - invalidCombinations + MOD) % MOD << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
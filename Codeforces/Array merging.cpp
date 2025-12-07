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
const ll MOD = 1e9+7;

vector<int> calculateMaxConsecutive(int limitValue, const vector<int>& arrayData) {
    vector<int> maxCounts(limitValue + 1, 0);
    int arraySize = size(arrayData);
    if (arraySize == 0) return maxCounts;

    int currentLength = 0;
    for (int i = 0; i < arraySize; ++i) {
        if (i > 0 && arrayData[i] == arrayData[i - 1]) {
            currentLength++;
        } else {
            currentLength = 1;
        }
        maxCounts[arrayData[i]] = max(maxCounts[arrayData[i]], currentLength);
    }
    return maxCounts;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<int> arrayA(N);
    for (int i = 0; i < N; ++i) cin >> arrayA[i];

    vector<int> arrayB(N);
    for (int i = 0; i < N; ++i) cin >> arrayB[i];

    int limitValue = 2 * N;

    vector<int> countsA = calculateMaxConsecutive(limitValue, arrayA);
    vector<int> countsB = calculateMaxConsecutive(limitValue, arrayB);

    int maxTotalLength = 0;
    for (int i = 1; i <= limitValue; ++i) {
        maxTotalLength = max(maxTotalLength, countsA[i] + countsB[i]);
    }

    cout << maxTotalLength << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
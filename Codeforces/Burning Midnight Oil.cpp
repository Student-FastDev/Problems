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

bool canWriteEnoughLines(ll startValue, ll targetLines, ll reductionCoefficient) {
    ll totalLinesWritten = 0;
    ll currentValue = startValue;
    while (currentValue > 0) {
        totalLinesWritten += currentValue;
        currentValue /= reductionCoefficient;
    }
    return totalLinesWritten >= targetLines;
}

void solveTestCase() {
    ll N, K;
    cin >> N >> K;

    ll leftRange = 1;
    ll rightRange = N;
    ll minimumStartValue = N;

    while (leftRange <= rightRange) {
        ll middleValue = leftRange + (rightRange - leftRange) / 2;
        if (canWriteEnoughLines(middleValue, N, K)) {
            minimumStartValue = middleValue;
            rightRange = middleValue - 1;
        } else {
            leftRange = middleValue + 1;
        }
    }

    cout << minimumStartValue << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
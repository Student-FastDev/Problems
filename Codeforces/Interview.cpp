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
    int N;
    cin >> N;
    vector<ll> stoneWeights(N + 1);
    vector<ll> prefixSum(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> stoneWeights[i];
        prefixSum[i] = prefixSum[i - 1] + stoneWeights[i];
    }

    int rangeLeft = 1;
    int rangeRight = N;
    while (rangeLeft < rangeRight) {
        int rangeMid = rangeLeft + (rangeRight - rangeLeft) / 2;
        int currentRangeLength = rangeMid - rangeLeft + 1;

        cout << "? " << currentRangeLength;
        for (int i = rangeLeft; i <= rangeMid; ++i) {
            cout << " " << i;
        }
        cout << endl;
        cout.flush();

        ll responseWeight;
        cin >> responseWeight;

        ll expectedWeight = prefixSum[rangeMid] - prefixSum[rangeLeft - 1];
        if (responseWeight == expectedWeight + 1) {
            rangeRight = rangeMid;
        } else {
            rangeLeft = rangeMid + 1;
        }
    }

    cout << "! " << rangeLeft << endl;
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
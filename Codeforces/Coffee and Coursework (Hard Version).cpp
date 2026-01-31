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
    ll M;
    cin >> N >> M;
    vector<ll> caffeineArray(N);
    ll maxPossibleSum = 0;
    for (int i = 0; i < N; ++i) {
        cin >> caffeineArray[i];
        maxPossibleSum += caffeineArray[i];
    }

    if (maxPossibleSum < M) {
        cout << -1 << endl;
        return;
    }

    sort(all(caffeineArray), greater<ll>());

    int low = 1, high = N;
    int answer = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        ll currentPages = 0;
        for (int i = 0; i < N; ++i) {
            ll penalty = i / mid;
            if (caffeineArray[i] <= penalty) break;
            currentPages += (caffeineArray[i] - penalty);
        }

        if (currentPages >= M) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << answer << endl;
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
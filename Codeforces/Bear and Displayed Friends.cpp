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
    int N, K, Q;
    cin >> N >> K >> Q;

    vector<ll> friendshipValues(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> friendshipValues[i];
    }

    vector<pair<ll, int>> displayedFriends;
    vector<bool> isDisplayed(N + 1, false);

    for (int i = 0; i < Q; ++i) {
        int queryType, friendId;
        cin >> queryType >> friendId;
        if (queryType == 1) {
            displayedFriends.push_back({friendshipValues[friendId], friendId});
            isDisplayed[friendId] = true;
            sort(all(displayedFriends));

            if ((int)size(displayedFriends) > K) {
                isDisplayed[displayedFriends[0].second] = false;
                displayedFriends.erase(displayedFriends.begin());
            }
        } else {
            if (isDisplayed[friendId]) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}
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
    int N, M;
    ll H;
    cin >> N >> M >> H;

    int rudolfRank = 1;
    pair<int, ll> rudolfScore = {-1, -1};

    for (int i = 0; i < N; ++i) {
        vector<ll> taskTimes(M);
        for (int j = 0; j < M; ++j) {
            cin >> taskTimes[j];
        }
        sort(all(taskTimes));

        int scoreCount = 0;
        ll totalPenalty = 0;
        ll timeElapsed = 0;

        for (ll t : taskTimes) {
            if (timeElapsed + t > H) break;
            timeElapsed += t;
            totalPenalty += timeElapsed;
            scoreCount++;
        }

        if (i == 0) {
            rudolfScore = {scoreCount, totalPenalty};
        } else {
            if (scoreCount > rudolfScore.first) {
                rudolfRank++;
            } else if (scoreCount == rudolfScore.first && totalPenalty < rudolfScore.second) {
                rudolfRank++;
            }
        }
    }

    cout << rudolfRank << endl;
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
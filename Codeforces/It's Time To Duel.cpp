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
    vector<int> A(N);
    for(int& x : A) cin >> x;

    vector<int> duelOutcomeArray(N - 1, -1);
    bool isPossible = true;

    auto setOutcome = [&](int index, int value) {
        if (duelOutcomeArray[index] != -1 && duelOutcomeArray[index] != value) return false;
        duelOutcomeArray[index] = value;
        return true;
    };

    if (!setOutcome(0, A[0] == 1 ? 1 : 0)) isPossible = false;
    if (!setOutcome(N - 2, A[N - 1] == 1 ? 0 : 1)) isPossible = false;

    for (int i = 1; i < N - 1; ++i) {
        if (A[i] == 0) {
            if (!setOutcome(i - 1, 1)) isPossible = false;
            if (!setOutcome(i, 0)) isPossible = false;
        }
    }

    if (!isPossible) {
        cout << "YES" << endl;
        return;
    }

    int lastOneIndex = -1;
    for (int i = 0; i < N - 1; ++i) {
        if (duelOutcomeArray[i] == 1) {
            lastOneIndex = i;
        } else if (duelOutcomeArray[i] == 0 && lastOneIndex != -1) {
            cout << "YES" << endl;
            return;
        }

        if (i < N - 2) {
            if (A[i + 1] == 0) {
                lastOneIndex = -1;
            }
        }
    }

    cout << "NO" << endl;
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
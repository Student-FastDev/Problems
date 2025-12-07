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
    string S;
    cin >> S;

    string A = "0" + S;
    vector<int> list01, list10;
    int transitions = 0;

    for (int i = 0; i < N; ++i) {
        if (A[i] != A[i+1]) {
            transitions++;
            if (A[i] == '0' && A[i+1] == '1') {
                list01.push_back(i);
            } else {
                list10.push_back(i);
            }
        }
    }

    ll baseCost = N + transitions;
    ll maxGain = 0;

    if (size(list01) >= 2 || size(list10) >= 2) {
        maxGain = 2;
    } else {
        char lastChar = A.back();
        
        for (int idx : list01) {
            if (A[idx] == lastChar) {
                maxGain = max(maxGain, 1LL);
            }
        }
        for (int idx : list10) {
            if (A[idx] == lastChar) {
                maxGain = max(maxGain, 1LL);
            }
        }
    }

    cout << baseCost - maxGain << endl;
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
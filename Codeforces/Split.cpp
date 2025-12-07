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
    
    vector<int> countArray(2 * N + 1, 0);
    for (int i = 0; i < 2 * N; ++i) {
        int x;
        cin >> x;
        countArray[x]++;
    }
    
    int K = 0;
    int M = 0;
    
    for (int i = 1; i <= 2 * N; ++i) {
        if (countArray[i] > 0) {
            if (countArray[i] % 2 != 0) {
                K++;
            } else {
                M++;
            }
        }
    }
    
    if (K == 0) {
        if (M % 2 == N % 2) {
            cout << 2 * M << endl;
        } else {
            cout << 2 * M - 2 << endl;
        }
    } else {
        cout << K + 2 * M << endl;
    }
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

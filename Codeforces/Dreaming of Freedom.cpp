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

const int MAX_VALUE = 1000005;
vector<int> minPrimeFactor(MAX_VALUE);

void precompute() {
    iota(all(minPrimeFactor), 0);
    for (int i = 2; i * i < MAX_VALUE; ++i) {
        if (minPrimeFactor[i] == i) {
            for (int j = i * i; j < MAX_VALUE; j += i) {
                if (minPrimeFactor[j] == j) minPrimeFactor[j] = i;
            }
        }
    }
}

void solveTestCase() {
    static bool isInitialized = false;
    if (!isInitialized) {
        precompute();
        isInitialized = true;
    }

    int N, M;
    cin >> N >> M;

    if (N == 1) {
        cout << "YES" << endl;
        return;
    }

    if (minPrimeFactor[N] <= M) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
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
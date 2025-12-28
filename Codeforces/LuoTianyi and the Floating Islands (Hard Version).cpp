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
const ll MAX_N = 2e5+5;
const ll MOD = 1e9+7; // 998244353

ll factorial[MAX_N], inverseFactorial[MAX_N];

ll power(ll base, ll exponent) {
    ll result = 1;
    base %= MOD;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent /= 2;
    }
    return result;
}

ll modularInverse(ll n) {
    return power(n, MOD - 2);
}

void precompute() {
    factorial[0] = 1;
    inverseFactorial[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
        inverseFactorial[i] = modularInverse(factorial[i]);
    }
}

ll combinations(int n, int r) {
    if (r < 0 || r > n) return 0;
    return factorial[n] * inverseFactorial[r] % MOD * inverseFactorial[n - r] % MOD;
}

int N, K;
vector<vector<int>> neighbourList;
vector<int> subtreeSizeArray;

void dfs(int currentNode, int parentNode) {
    subtreeSizeArray[currentNode] = 1;
    for (int neighbor : neighbourList[currentNode]) {
        if (neighbor == parentNode) continue;
        dfs(neighbor, currentNode);
        subtreeSizeArray[currentNode] += subtreeSizeArray[neighbor];
    }
}

void solveTestCase() {
    cin >> N >> K;
    neighbourList.assign(N + 1, vector<int>());
    subtreeSizeArray.assign(N + 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }

    if (K % 2 != 0) {
        cout << 1 << endl;
        return;
    }

    dfs(1, 0);

    ll totalWays = combinations(N, K);
    ll validSplitCount = 0;

    for (int i = 2; i <= N; ++i) {
        int currentSize = subtreeSizeArray[i];
        ll ways = combinations(currentSize, K / 2) * combinations(N - currentSize, K / 2) % MOD;
        validSplitCount = (validSplitCount + ways) % MOD;
    }

    ll answer = (validSplitCount * modularInverse(totalWays)) % MOD;
    answer = (answer + 1) % MOD;

    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    precompute();

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
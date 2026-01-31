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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806LL;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;

struct RollingHash {
    static const ll mod = 1000000007LL;
    static const ll base = 137LL;

    vector<ll> hash, power;

    RollingHash(const string& s) {
        int n = size(s);
        hash.resize(n + 1, 0);
        power.resize(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            power[i] = (power[i - 1] * base) % mod;
            hash[i] = (hash[i - 1] * base + s[i - 1]) % mod;
        }
    }

    ll getHash(int l, int r) {
        return (hash[r + 1] - hash[l] * power[r - l + 1] % mod + mod) % mod;
    }

    bool isEqual(int l1, int r1, int l2, int r2) {
        return getHash(l1, r1) == getHash(l2, r2);
    }
};



void solveTestCase() {
    string S;
    cin >> S;
    
    int N = size(S);

    int currentStart = 0;
    int currentEnd = 0;
    int currentScore = 0;

    RollingHash stringHash(S);

    int mid = N / 2;
    while(currentEnd < mid) {
        if(stringHash.isEqual(currentStart, currentEnd, N-1-currentEnd, N-1-currentStart)) {
            currentScore += 2;
            currentStart = currentEnd + 1;
        }
        currentEnd++;
    }

    if(2 * currentStart < N) currentScore++;
    cout << max(1, currentScore) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        solveTestCase();
    }
    
    return 0;
}

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
    int catCount, queryCount;
    cin >> catCount >> queryCount;

    vector<int> catValues(catCount);
    for(int i = 0; i < catCount; ++i) cin >> catValues[i];

    vector<unsigned long long> randomHashValues(catCount + 1);
    for(int i = 1; i <= catCount; ++i) randomHashValues[i] = rng();

    vector<unsigned long long> prefixHashSums(catCount + 1, 0);
    for(int i = 0; i < catCount; ++i) {
        prefixHashSums[i+1] = prefixHashSums[i] + randomHashValues[catValues[i]];
    }

    for(int i = 0; i < queryCount; ++i) {
        int left1, right1, left2, right2;
        cin >> left1 >> right1 >> left2 >> right2;
        
        unsigned long long hash1 = prefixHashSums[right1] - prefixHashSums[left1 - 1];
        unsigned long long hash2 = prefixHashSums[right2] - prefixHashSums[left2 - 1];

        if(hash1 == hash2) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
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

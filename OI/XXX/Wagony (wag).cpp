// Catling
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ull INF_COST = ULLONG_MAX;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; 

struct CustomHash {
    static uint64_t splitMix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = 0x9e3779b97f4a7c15;
        return splitMix64(x + FIXED_RANDOM);
    }
};

ll N, D, A, B;

typedef gp_hash_table<ll, ull, CustomHash> FastMap;
FastMap MEMO;

const int SMALL_LIMIT = 2500;
ull dpSmall[SMALL_LIMIT];
bool visitedSmall[SMALL_LIMIT];

ull getMinCost(ll currentN) {
    if (currentN == 1) return 0;

    if (currentN < SMALL_LIMIT) {
        if (visitedSmall[currentN]) return dpSmall[currentN];
    } else {
        auto it = MEMO.find(currentN);
        if (it != MEMO.end()) return it->second;
    }

    ull minCost = INF_COST;

    ll startI = (currentN - D + 1) / 2;
    ll endI = (currentN + D) / 2;

    if (startI < 1) startI = 1;
    if (endI >= currentN) endI = currentN - 1;

    for (ll i = startI; i <= endI; ++i) {
        ll j = currentN - i;
        
        ull firstTerm = (ull)A * (i % 1001);
        ull secondTerm = (ull)B * (j % 1001);
        ull mergeCost = (firstTerm + secondTerm) % 1001;
        
        ull currentTotal = getMinCost(i) + getMinCost(j) + mergeCost;
        
        if (currentTotal < minCost) {
            minCost = currentTotal;
        }
    }

    if (currentN < SMALL_LIMIT) {
        visitedSmall[currentN] = true;
        dpSmall[currentN] = minCost;
    } else {
        MEMO[currentN] = minCost;
    }

    return minCost;
}

void solveTestCase() {
    if (cin >> N >> D >> A >> B) {
        cout << getMinCost(N) << endl;
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
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
const ll MOD = 1e9+7; 

void solveTestCase() {
    ll K;
    if (!(cin >> K)) return;

    if (K % 2 != 0 && K < 17) {
        cout << "-1 -1" << endl;
        return;
    }

    struct Node {
        int id;
        ll c;
    };
    vector<Node> pool;
    vector<pii> edges;
    int nextId = 2;
    ll currentK = 0;

    // Base setup
    if (K % 2 != 0) {
        // Odd K >= 17
        pool.push_back({2, 1}); edges.push_back({1, 2}); currentK += 2;
        pool.push_back({3, 2}); edges.push_back({1, 3}); edges.push_back({2, 3}); currentK += 6;
        pool.push_back({4, 3}); edges.push_back({1, 4}); edges.push_back({3, 4}); currentK += 9;
        nextId = 5;
    } else {
        // Even K
        pool.push_back({2, 1}); edges.push_back({1, 2}); currentK += 2;
        nextId = 3;
    }

    while (currentK < K) {
        ll rem = K - currentK;
        ll bestCost = 2;
        ll bestC = 1;
        vector<int> bestIndices; 

        // Strategy 1: Connect to all available nodes
        {
            ll cSum = 0;
            for(auto& p : pool) cSum += p.c;
            ll cNew = 1 + cSum;
            ll cost = cNew * (2 + size(pool));
            if (cost <= rem && cost % 2 == 0) {
                if (cost > bestCost) {
                    bestCost = cost;
                    bestC = cNew;
                    bestIndices.resize(size(pool));
                    iota(all(bestIndices), 0);
                }
            }
        }

        // Strategy 2: Connect to suffixes of the pool
        {
            ll cSum = 0;
            ll currentSz = 0;
            for (int i = (int)size(pool) - 1; i >= 0; --i) {
                cSum += pool[i].c;
                currentSz++;
                ll cNew = 1 + cSum;
                ll cost = cNew * (2 + currentSz);
                
                // If the cost already exceeds rem, and since we are summing from the end (larger values usually),
                // it's likely to keep exceeding. However, to be safe against non-monotonicity due to small 
                // insertions, we could continue, but for efficiency we break if it's way too large.
                // Given the construction, C values grow exponentially, so break is safe.
                if (cost > rem) break; 
                
                if (cost % 2 == 0) {
                    if (cost > bestCost) {
                        bestCost = cost;
                        bestC = cNew;
                        bestIndices.clear();
                        for(int k = i; k < (int)size(pool); ++k) bestIndices.push_back(k);
                    }
                }
            }
        }

        // Strategy 3: Connect to single elements (check last 60 for efficiency)
        int limit = max(0, (int)size(pool) - 60);
        for (int i = (int)size(pool) - 1; i >= limit; --i) {
            ll cNew = 1 + pool[i].c;
            ll cost = cNew * 3;
            if (cost <= rem && cost % 2 == 0) {
                if (cost > bestCost) {
                    bestCost = cost;
                    bestC = cNew;
                    bestIndices = {i};
                }
            }
        }

        // Apply the best move
        int u = nextId++;
        edges.push_back({1, u});
        for (int idx : bestIndices) {
            edges.push_back({pool[idx].id, u});
        }
        pool.push_back({u, bestC});
        currentK += bestCost;
    }

    cout << nextId - 1 << " " << size(edges) << endl;
    for (auto& p : edges) cout << p.first << " " << p.second << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T; 

    while(T--) {
        solveTestCase();
    }
    return 0;
}
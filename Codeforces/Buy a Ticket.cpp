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
    int numberOfCities, numberOfRoutes;
    cin >> numberOfCities >> numberOfRoutes;

    vector<vector<pair<int, ll>>> neighbourList(numberOfCities + 1);
    for (int i = 0; i < numberOfRoutes; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        neighbourList[u].push_back({v, 2 * w});
        neighbourList[v].push_back({u, 2 * w});
    }

    vector<ll> concertCosts(numberOfCities + 1);
    for (int i = 1; i <= numberOfCities; ++i) {
        cin >> concertCosts[i];
    }

    vector<ll> minimumCosts(numberOfCities + 1, INF);
    priority_queue<pll, vector<pll>, greater<pll>> priorityQueue;

    for (int i = 1; i <= numberOfCities; ++i) {
        minimumCosts[i] = concertCosts[i];
        priorityQueue.push({minimumCosts[i], i});
    }

    while (!priorityQueue.empty()) {
        pll current = priorityQueue.top();
        priorityQueue.pop();

        ll currentCost = current.first;
        int u = (int)current.second;

        if (currentCost > minimumCosts[u]) {
            continue;
        }

        for (auto& edge : neighbourList[u]) {
            int v = edge.first;
            ll weight = edge.second;

            if (minimumCosts[u] + weight < minimumCosts[v]) {
                minimumCosts[v] = minimumCosts[u] + weight;
                priorityQueue.push({minimumCosts[v], v});
            }
        }
    }

    for (int i = 1; i <= numberOfCities; ++i) {
        cout << minimumCosts[i] << (i == numberOfCities ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
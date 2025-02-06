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
typedef pair<ll, ll> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    ll N;
    cin >> N;
    
    vector<vector<ll>> allowedGirls(N);
    for (ll i = 0; i < N; ++i) {
        ll M;
        cin >> M;
        allowedGirls[i].resize(M);
        for (ll j = 0; j < M; ++j) {
            cin >> allowedGirls[i][j];
        }
    }
    
    vector<ll> A(N);
    for (ll i = 0; i < N; ++i) {
        cin >> A[i];
    }

    ll totalNodes = 2 * N;
    vector<vector<ll>> neighbourHood(totalNodes + 1);

    for (ll guy = 0; guy < N; ++guy) {
        ll originalGirl = A[guy];
        for (ll p : allowedGirls[guy]) {
            if (p != originalGirl) {
                neighbourHood[guy + 1].push_back(p + N);
            } else {
                neighbourHood[originalGirl + N].push_back(guy + 1);
            }
        }
    }

    vector<bool> visited(totalNodes + 1, false);
    vector<ll> order;
    for (ll node = 1; node <= totalNodes; ++node) {
        if (!visited[node]) {
            stack<pair<ll, bool>> stackArray;
            stackArray.push({node, false});
            while (!stackArray.empty()) {
                auto [v, processed] = stackArray.top();
                stackArray.pop();
                if (processed) {
                    order.push_back(v);
                    continue;
                }
                if (visited[v]) continue;
                visited[v] = true;
                stackArray.push({v, true});
                for (ll u : neighbourHood[v]) {
                    if (!visited[u]) {
                        stackArray.push({u, false});
                    }
                }
            }
        }
    }

    vector<vector<ll>> changedNeighbourHood(totalNodes + 1);
    for (ll v = 1; v <= totalNodes; ++v) {
        for (ll u : neighbourHood[v]) {
            changedNeighbourHood[u].push_back(v);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<ll> component(totalNodes + 1, 0);
    ll currentComponent = 0;
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        ll node = *it;
        if (!visited[node]) {
            currentComponent++;
            stack<ll> stackArray;
            stackArray.push(node);
            visited[node] = true;
            component[node] = currentComponent;
            while (!stackArray.empty()) {
                ll v = stackArray.top();
                stackArray.pop();
                for (ll u : changedNeighbourHood[v]) {
                    if (!visited[u]) {
                        visited[u] = true;
                        component[u] = currentComponent;
                        stackArray.push(u);
                    }
                }
            }
        }
    }

    for (ll guy = 0; guy < N; ++guy) {
        ll originalGirlNode = A[guy] + N;
        ll originalComponent = component[originalGirlNode];
        vector<ll> valid;
        for (ll p : allowedGirls[guy]) {
            if (p == A[guy]) {
                valid.push_back(p);
            } else {
                ll girlNode = p + N;
                if (component[girlNode] == originalComponent) {
                    valid.push_back(p);
                }
            }
        }
        sort(valid.begin(), valid.end());
        cout << size(valid);
        if (!valid.empty()) {
            cout << " ";
            for (ll j = 0; j < size(valid); ++j) {
                if (j > 0) cout << " ";
                cout << valid[j];
            }
        }
        cout << endl;;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

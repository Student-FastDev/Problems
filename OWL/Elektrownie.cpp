#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int I=2;for(auto e:X)o<<(", ")+I<<e,I=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct customHash {
    size_t operator()(const std::pair<long long, long long>& p) const {
        size_t hash1 = std::hash<long long>{}(p.first);
        size_t hash2 = std::hash<long long>{}(p.second);
        
        return hash1 ^ (hash2 << 1);
    }
};

vector<pll> plants;
ll N;

bool isPossible(ll S) {
    if (S == 0) return true;

    long double D = sqrtl(S);
    long double cellSize = D / 2.0L;

    unordered_map<pair<ll, ll>, vector<ll>, customHash> cellMap;
    for (ll idx = 0; idx < N; ++idx) {
        ll X = plants[idx].first;
        ll Y = plants[idx].second;
        ll I = floor(X / cellSize);
        ll j = floor(Y / cellSize);
        pair<ll, ll> key = {I, j};
        cellMap[key].push_back(idx);
        if (size(cellMap[key]) >= 3) {
            return false;
        }
    }

    vector<vector<ll>> adj(N);
    for (ll idx = 0; idx < N; ++idx) {
        ll X = plants[idx].first;
        ll Y = plants[idx].second;
        ll I = floor(X / cellSize);
        ll j = floor(Y / cellSize);

        for (ll di = -2; di <= 2; ++di) {
            for (ll dj = -2; dj <= 2; ++dj) {
                pair<ll, ll> neighbourKey = {I + di, j + dj};
                auto it = cellMap.find(neighbourKey);
                if (it == cellMap.end()) continue;
                for (ll neighbour : it->second) {
                    if (neighbour <= idx) continue;
                    ll dx = X - plants[neighbour].first;
                    ll dy = Y - plants[neighbour].second;
                    ll distSquared = dx * dx + dy * dy;
                    if (distSquared < S) {
                        adj[idx].push_back(neighbour);
                        adj[neighbour].push_back(idx);
                    }
                }
            }
        }
    }

    vector<int> color(N, -1);
    function<bool(int, int)> dfs = [&](int node, int c) -> bool {
        color[node] = c;
        for (int neighbour : adj[node]) {
            if (color[neighbour] == -1) {
                if (!dfs(neighbour, 1 - c)) return false;
            } else if (color[neighbour] == c) {
                return false;
            }
        }
        return true;
    };

    for (int I = 0; I < N; ++I) {
        if (color[I] == -1) {
            if (!dfs(I, 0)) return false;
        }
    }
    return true;
}

void solveTestCase() {
    cin >> N;
    plants.resize(N);

    for (ll I = 0; I < N; ++I) {
        cin >> plants[I].first >> plants[I].second;
    }

    ll left = 0, right = 2e18, ans = 0;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (isPossible(mid)) {
            right = mid - 1;
        } else {
            ans = mid;
            left = mid + 1;
        }
    }

    left = 0, right = ans;
    ll bestValue = 0;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (isPossible(mid)) {
            bestValue = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    vector<vector<ll>> adj(N);
    if (bestValue > 0) {
        long double D = sqrtl(bestValue);
        long double cellSize = D / 2.0L;

        unordered_map<pair<ll, ll>, vector<ll>, customHash> cellMap;
        for (ll idx = 0; idx < N; ++idx) {
            ll X = plants[idx].first;
            ll Y = plants[idx].second;
            ll I = floor(X / cellSize);
            ll j = floor(Y / cellSize);
            cellMap[{I, j}].push_back(idx);
        }

        for (ll idx = 0; idx < N; ++idx) {
            ll X = plants[idx].first;
            ll Y = plants[idx].second;
            ll I = floor(X / cellSize);
            ll j = floor(Y / cellSize);

            for (ll di = -2; di <= 2; ++di) {
                for (ll dj = -2; dj <= 2; ++dj) {
                    pair<ll, ll> neighbourKey = {I + di, j + dj};
                    auto it = cellMap.find(neighbourKey);
                    if (it == cellMap.end()) continue;
                    for (ll neighbour : it->second) {
                        if (neighbour <= idx) continue;
                        ll dx = X - plants[neighbour].first;
                        ll dy = Y - plants[neighbour].second;
                        ll distSquared = dx * dx + dy * dy;
                        if (distSquared < bestValue) {
                            adj[idx].push_back(neighbour);
                            adj[neighbour].push_back(idx);
                        }
                    }
                }
            }
        }
    }

    vector<int> color(N, -1);
    function<void(int, int)> dfsColor = [&](int node, int c) {
        color[node] = c;
        for (int neighbour : adj[node]) {
            if (color[neighbour] == -1) {
                dfsColor(neighbour, 1 - c);
            }
        }
    };

    for (int I = 0; I < N; ++I) {
        if (color[I] == -1) {
            dfsColor(I, 0);
        }
    }

    vector<int> group0, group1;
    for (int I = 0; I < N; ++I) {
        if (color[I] == 0) group0.push_back(I + 1);
        else group1.push_back(I + 1);
    }

    cout << bestValue << '\n';
    cout << size(group0) << '\n';
    for (int X : group0) cout << X << ' ';
    cout << '\n';
    cout << size(group1) << '\n';
    for (int X : group1) cout << X << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solveTestCase();
    return 0;
}

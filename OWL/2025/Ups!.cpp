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
const ll MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, S, T;
    cin >> N >> M >> S >> T;
    S--; T--;

    vector<pll> coordinates(N);
    for (int i = 0; i < N; ++i) {
        cin >> coordinates[i].first >> coordinates[i].second;
    }

    vector<set<pair<int, int>>> neighbourHood(N);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        A--; B--;
        int weightA = rng();
        int weightB = rng();
        neighbourHood[A].emplace(weightA, B);
        neighbourHood[B].emplace(weightB, A);
    }

    unordered_set<ll> visited;
    queue<tuple<int, int, int>> q;

    for (auto it = neighbourHood[S].begin(); it != neighbourHood[S].end(); ) {
        int u = it->second;
        if (u == S) {
            ++it;
            continue;
        }
        if (u == T) {
            cout << "1" << endl;
            return 0;
        }
        ll key = (ll(u) << 32) | S;
        if (visited.insert(key).second) {
            q.emplace(u, S, 1);
            it = neighbourHood[S].erase(it);
        } else {
            ++it;
        }
    }

    while (!q.empty()) {
        auto [current, prev, distance] = q.front();
        q.pop();

        if (current == T) {
            cout << distance << endl;
            return 0;
        }

        ll dxIn = coordinates[current].first - coordinates[prev].first;
        ll dyIn = coordinates[current].second - coordinates[prev].second;

        vector<int> toErase;
        for (auto &p : neighbourHood[current]) {
            int z = p.second;
            if (z == prev) continue;

            ll dxOut = coordinates[z].first - coordinates[current].first;
            ll dyOut = coordinates[z].second - coordinates[current].second;

            ll cross = dxIn * dyOut - dyIn * dxOut;

            if (cross <= 0) {
                ll key = (ll(z) << 32) | current;
                if (visited.insert(key).second) {
                    q.emplace(z, current, distance + 1);
                    toErase.push_back(z);
                }
            }
        }

        for (int z : toErase) {
            for (auto it = neighbourHood[current].begin(); it != neighbourHood[current].end(); ++it) {
                if (it->second == z) {
                    neighbourHood[current].erase(it);
                    break;
                }
            }
        }
    }
    cout << "-1" << endl;
}

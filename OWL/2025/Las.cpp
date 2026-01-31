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
typedef pair<ll,ll> pll;
typedef pair<ll, ll> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;

vector<ll> SPF;

template<typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void sieveOfErastotenes(ll maxN) {
    SPF.resize(maxN + 1);
    iota(SPF.begin(), SPF.end(), 0);
    for (ll i = 2; i * i <= maxN; ++i) {
        if (SPF[i] == i) {
            for (ll j = i * i; j <= maxN; j += i) {
                if (SPF[j] == j) SPF[j] = i;
            }
        }
    }
}

vector<ll> numberFactors(ll x) {
    vector<ll> factors;
    if (x == 1) return factors;
    while (x != 1) {
        ll P = SPF[x];
        factors.push_back(P);
        while (x % P == 0) x /= P;
    }
    sort(factors.begin(), factors.end());
    factors.erase(unique(factors.begin(), factors.end()), factors.end());
    return factors;
}

void solveTestCase() {
    ll N, Q, M;
    cin >> N >> Q >> M;

    vector<vector<ll>> numberDivisors(M + 1);
    for (ll d = 1; d <= M; ++d) {
        for (ll multiple = d; multiple <= M; multiple += d) {
            numberDivisors[multiple].push_back(d);
        }
    }

    sieveOfErastotenes(M);

    unordered_map<ll, ordered_set<ll>> divPos;
    unordered_map<ll, ll> current;

    auto update = [&](ll P, ll x) {
        auto it = current.find(P);
        ll oldType = (it != current.end()) ? it->second : 1;

        if (oldType == x) return;

        if (oldType != 1) {
            for (ll d : numberDivisors[oldType]) {
                divPos[d].erase(P);
            }
        }

        if (x != 1) {
            for (ll d : numberDivisors[x]) {
                divPos[d].insert(P);
            }
            current[P] = x;
        } else {
            if (it != current.end()) {
                current.erase(it);
            }
        }
    };

    auto query = [&](ll L, ll R, ll X) {
        if (X == 1) {
            cout << 0 << endl;
            return;
        }
        vector<ll> primes = numberFactors(X);
        if (primes.empty()) {
            cout << 0 << endl;
            return;
        }
        ll K = size(primes);
        ll totalNumber = 0;
        for (ll mask = 1; mask < (1 << K); ++mask) {
            ll bits = __builtin_popcount(mask);
            ll sign = (bits % 2 == 1) ? 1 : -1;
            ll D = 1;
            for (ll i = 0; i < K; ++i) {
                if (mask & (1 << i)) {
                    D *= primes[i];
                }
            }
            if (divPos.find(D) == divPos.end()) continue;
            const auto& S = divPos[D];
            ll count = S.order_of_key(R + 1) - S.order_of_key(L);
            totalNumber += sign * count;
        }
        cout << totalNumber << endl;
    };

    while (Q--) {
        char operationType;
        cin >> operationType;
        if (operationType == '=') {
            ll P, X;
            cin >> P >> X;
            update(P, X);
        } else {
            ll L, R, X;
            cin >> L >> R >> X;
            query(L, R, X);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T = 1;

    while(T--) {
        solveTestCase();
    }
}
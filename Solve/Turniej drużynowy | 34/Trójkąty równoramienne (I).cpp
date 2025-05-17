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

struct directionValue {
    int dX, dY;
    bool operator==(directionValue const &o) const {
        return dX==o.dX && dY==o.dY;
    }
};

struct HashDirectionValue {
    size_t operator()(directionValue const &d) const noexcept {
        return ((uint64_t)(d.dX) << 32) ^ (uint32_t)d.dY;
    }
};

void solveTestCase() {
    int N;
    cin >> N;
    vector<pll> P(N);
    for(int i = 0; i < N; i++) {
        cin >> P[i].first >> P[i].second;
    }

    ll finalAnswer = 0;
    for(int i = 0; i < N; i++) {
        vector<pair<ll, directionValue>> K;
        K.reserve(N-1);
        for(int j = 0; j < N; j++) {
            if(i == j) continue;
            ll dX = P[j].first - P[i].first;
            ll dY = P[j].second - P[i].second;
            ll distanceValue = dX * dX + dY * dY;
            ll divsionValue = gcd(llabs(dX), llabs(dY));
            directionValue pointsDistance{ int(dX / divsionValue), int(dY / divsionValue) };
            K.emplace_back(distanceValue, pointsDistance);
        }

        sort(K.begin(), K.end(), [](auto &a, auto &b){
            return a.first < b.first;
        });

        for(int l = 0, O = size(K); l < O;) {
            int R = l + 1;
            while(R < O && K[R].first == K[l].first) 
                R++;
            int C = R - l;
            ll totalPairs = (ll)C * (C - 1) / 2;

            unordered_map<directionValue, int, HashDirectionValue> countPairs;
            countPairs.reserve(C * 2);
            for(int k = l; k < R; k++) {
                countPairs[K[k].second]++;
            }

            ll degeneratePairs = 0;
            for(auto &k : countPairs) {
                directionValue U = k.first;
                directionValue V{-U.dX, -U.dY};
                auto isFound = countPairs.find(V);
                if(isFound != countPairs.end()) {
                    degeneratePairs += (ll)k.second * isFound->second;
                }
            }
            degeneratePairs /= 2;

            finalAnswer += totalPairs - degeneratePairs;
            l = R;
        }
    }

    cout << finalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

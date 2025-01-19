#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
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

void solveTestCase() {
    int N;
    ll K;
    cin >> N >> K;

    vector<ll> X(N);
    for(int i = 0; i < N; i++) {
        cin >> X[i];
    }
    unordered_map<ll, ll> freq;
    for(int i = 0; i < N; i++) {
        freq[X[i]]++;
    }
    ll M = 0;
    unordered_set<ll> processedMap;
    for(unordered_map<ll, ll>::iterator it = freq.begin(); it != freq.end(); ++it) {
        ll num = it->first;
        ll count = it->second;
        if(processedMap.find(num) != processedMap.end()) continue;
        ll complement = K - num;
        if(freq.find(complement) != freq.end()) {
            if(complement == num) {
                M += count / 2;
            } else {
                M += min(count, freq[complement]);
            }
            processedMap.insert(num);
            processedMap.insert(complement);
        }
    }
    cout << M << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

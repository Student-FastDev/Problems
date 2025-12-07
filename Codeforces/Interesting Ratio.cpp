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

const int MAX_PRIME_LIMIT = 10000005;
bitset<MAX_PRIME_LIMIT> compositeBits;
vector<int> primeNumbers;

void precomputePrimes() {
    compositeBits[0] = 1;
    compositeBits[1] = 1;
    for (int i = 2; i * i < MAX_PRIME_LIMIT; i++) {
        if (!compositeBits[i]) {
            for (int j = i * i; j < MAX_PRIME_LIMIT; j += i)
                compositeBits[j] = 1;
        }
    }
    for (int i = 2; i < MAX_PRIME_LIMIT; i++) {
        if (!compositeBits[i]) primeNumbers.push_back(i);
    }
}

void solveTestCase() {
    int N;
    cin >> N;

    ll interestingRatioCount = 0;
    for (int p : primeNumbers) {
        if (p > N) break;
        interestingRatioCount += (N / p);
    }
    cout << interestingRatioCount << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    precomputePrimes();

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
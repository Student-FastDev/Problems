// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';long long i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<long long, long long> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

vector<long long> getPrimes(long long N) {
    set<long long> primeFactorsSet;
    for(long long i = 2; i * i <= N; i++) {
        while(N % i == 0) {
            primeFactorsSet.insert(i);
            N /= i;
        }
    }
    if(N > 1) primeFactorsSet.insert(N);
    vector<long long> primeFactors(primeFactorsSet.begin(), primeFactorsSet.end());
    return primeFactors;
}

long long getIntervalScore(long long right, vector<long long>& primeFactors) {
    long long N = size(primeFactors);
    long long scoreValue = 0;
    long long segmentSize = max((long long)0, right);

    for(long long i = 1; i < (1 << N); i++) {
        long long product = 1;
        for(long long j = 0; j < N; j++) {
            if(i & (1 << j)) product *= primeFactors[j];
        }
        long long sign = __builtin_popcount(i) % 2 ? 1 : -1;
        scoreValue += sign * (segmentSize / product);
    }

    return segmentSize - scoreValue;
}

long long getKthElement(long long K, vector<long long>& primeFactors) {
    long long N = size(primeFactors);
    long long left = 1, right = 1e18;
    while(left < right) {
        long long mid = (left + right) / 2;
        long long score = getIntervalScore(mid, primeFactors);
        if(score < K) left = mid + 1;
        else right = mid;
    }

    return left;
}

void getNextElements(long long N, long long L, long long C) {
    long long relativelyFirstCount = 0;
    long long iterator = L;
    while(relativelyFirstCount < C) {
        if(gcd(iterator, N) == 1) {
            relativelyFirstCount++; 
            cout << iterator << " ";
        }
        iterator++;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    long long N, K, C;
    cin >> N >> K >> C; 

    vector<long long> primeFactors = getPrimes(N);
    LOG(primeFactors);

    long long elementK = getKthElement(K, primeFactors);
    getNextElements(N, elementK, C);

    return 0;
}

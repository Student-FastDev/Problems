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

const int MAX_VALUE_LIMIT = 100005;
int smallestPrimeFactor[MAX_VALUE_LIMIT];
int signatureCount[MAX_VALUE_LIMIT];

void sieve() {
    iota(smallestPrimeFactor, smallestPrimeFactor + MAX_VALUE_LIMIT, 0);
    for (int i = 2; i * i < MAX_VALUE_LIMIT; i++) {
        if (smallestPrimeFactor[i] == i) {
            for (int j = i * i; j < MAX_VALUE_LIMIT; j += i)
                if (smallestPrimeFactor[j] == j)
                    smallestPrimeFactor[j] = i;
        }
    }
}

void solveTestCase() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    ll answer = 0;

    for(int currentValue : A) {
        ll currentSignature = 1;
        ll neededSignature = 1;
        int temporaryValue = currentValue;

        while (temporaryValue > 1) {
            int primeFactor = smallestPrimeFactor[temporaryValue];
            int exponentCount = 0;
            while (temporaryValue % primeFactor == 0) {
                exponentCount++;
                temporaryValue /= primeFactor;
            }
            
            exponentCount %= K;
            if (exponentCount > 0) {
                for(int i = 0; i < exponentCount; ++i) 
                    currentSignature *= primeFactor;
                
                if (neededSignature < MAX_VALUE_LIMIT) {
                    int neededExponent = K - exponentCount;
                    for(int i = 0; i < neededExponent; ++i) {
                        neededSignature *= primeFactor;
                        if (neededSignature >= MAX_VALUE_LIMIT) break;
                    }
                }
            }
        }

        if (neededSignature < MAX_VALUE_LIMIT) {
            answer += signatureCount[neededSignature];
        }

        signatureCount[currentSignature]++;
    }

    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    sieve();

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
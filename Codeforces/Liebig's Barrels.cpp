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
    int N, K;
    ll L;
    cin >> N >> K >> L;
    
    int M = N * K;
    vector<ll> A(M);
    for(int i = 0; i < M; ++i) cin >> A[i];
    
    sort(all(A));
    
    auto iterator = upper_bound(all(A), A[0] + L);
    int validCount = distance(A.begin(), iterator);
    
    if (validCount < N) {
        cout << 0 << endl;
        return;
    }
    
    ll totalVolume = 0;
    int currentIndex = 0;
    int lastValidIndex = validCount - 1;
    
    for (int i = 1; i <= N; ++i) {
        totalVolume += A[currentIndex];
        
        int remainingRight = lastValidIndex - currentIndex;
        int neededReserve = N - i;
        int availableForFillers = remainingRight - neededReserve;
        
        int take = 0;
        if (availableForFillers > 0) {
            take = min(K - 1, availableForFillers);
        }
        
        currentIndex += 1 + take;
    }
    
    cout << totalVolume << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
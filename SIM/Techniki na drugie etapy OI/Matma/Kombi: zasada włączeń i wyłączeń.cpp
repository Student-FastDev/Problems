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

static const int MAXA = 1000000;

int freq[MAXA+1];
int countDivisor[MAXA+1];
int muVal[MAXA+1];
int G[MAXA+1];

void computeMobius() {
    vector<int> SPF(MAXA+1, 0);
    for(int i = 2; i <= MAXA; i++){
        if(SPF[i] == 0){
            for(long long j = i; j <= MAXA; j += i){
                if(SPF[j] == 0) {
                    SPF[j] = i;
                }
            }
        }
    }
    muVal[1] = 1;
    for(int i = 2; i <= MAXA; i++){
        int p = SPF[i];
        int x = i / p;
        if(x % p == 0) {
            muVal[i] = 0;
        } else {
            muVal[i] = -muVal[x];
        }
    }
}

void solveTestCase() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; 
    cin >> N;

    vector<int> valueArray(N);
    for(int i = 0; i < N; i++){
        cin >> valueArray[i];
        freq[valueArray[i]]++;
    }

    computeMobius();

    for(int d = 1; d <= MAXA; d++){
        for(int m = d; m <= MAXA; m += d){
            countDivisor[d] += freq[m];
        }
    }

    for(int d = 1; d <= MAXA; d++){
        int fVal = muVal[d] * countDivisor[d];
        if(fVal == 0) continue;
        for(int m = d; m <= MAXA; m += d){
            G[m] += fVal;
        }
    }

    for(int i = 0; i < N; i++){
        if(valueArray[i] == 1){
            cout << 0 << (i+1 < N ? ' ' : endl);
        } else {
            int notCoprimeCount = (N - 1) - G[valueArray[i]];
            cout << notCoprimeCount << (i+1 < N ? ' ' : endl);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

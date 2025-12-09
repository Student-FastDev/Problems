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

const ll firstMOD = 1e9 + 7;
const ll firstBASE = 67;
const ll secondMOD = 998244353;
const ll secondBASE = 317;

void solveTestCase() {
    string S;
    cin >> S;
    
    int N = size(S);
    if (N == 0) {
        cout << 0 <<  endl;
        return;
    }

    int leftRange = 0;
    int rightRange = N - 1;
    
    ll firstHashPrefix = 0;
    ll secondHashPrefix = 0;
    
    ll firstHashSuffix = 0;
    ll secondHashSuffix = 0;
    
    ll firstPower = 1;
    ll secondPower = 1;
    
    int finalAnswer = 0;
    bool doesConstruct = false;

    while (leftRange < rightRange) {
        doesConstruct = true;
        LOG(doesConstruct);
        LOG(leftRange);
        LOG(rightRange);
        
        {
            firstHashPrefix = (firstHashPrefix * firstBASE + S[leftRange]) % firstMOD;
            secondHashPrefix = (secondHashPrefix * secondBASE + S[leftRange]) % secondMOD;
            firstHashSuffix = (firstHashSuffix + S[rightRange] * firstPower) % firstMOD;
            secondHashSuffix = (secondHashSuffix + S[rightRange] * secondPower) % secondMOD;
            
            firstPower = (firstPower * firstBASE) % firstMOD;
            secondPower = (secondPower * secondBASE) % secondMOD;
        }

        if (firstHashPrefix == firstHashSuffix && secondHashPrefix == secondHashSuffix) {
            finalAnswer += 2;
            firstHashPrefix = 0; secondHashPrefix = 0;
            firstHashSuffix = 0; secondHashSuffix = 0;
            firstPower = 1; secondPower = 1;
            
            doesConstruct = false;
        }
        
        leftRange++;
        rightRange--;
    }
    
    if (doesConstruct || leftRange == rightRange) {
        finalAnswer++;
    }
    
    cout << finalAnswer << endl;
    return;
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

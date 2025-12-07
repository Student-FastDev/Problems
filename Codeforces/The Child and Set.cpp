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
    int targetSum, limitValue;
    cin >> targetSum >> limitValue;

    vector<vector<int>> bitBuckets(20);
    for(int i = 1; i <= limitValue; ++i) {
        int lb = i & -i;
        int bitPos = __builtin_ctz(lb);
        bitBuckets[bitPos].push_back(i);
    }

    vector<int> chosenNumbers;
    int currentSum = targetSum;

    for(int i = 19; i >= 0; --i) {
        int val = 1 << i;
        while(currentSum >= val && size(bitBuckets[i]) > 0) {
            int num = bitBuckets[i].back();
            bitBuckets[i].pop_back();
            currentSum -= val;
            chosenNumbers.push_back(num);
        }
    }

    if(currentSum == 0) {
        cout << size(chosenNumbers) << endl;
        for(int i = 0; i < (int)size(chosenNumbers); ++i) {
            cout << chosenNumbers[i] << (i == (int)size(chosenNumbers) - 1 ? "" : " ");
        }
        cout << endl;
    } else {
        cout << -1 << endl;
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
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
    cin >> N >> K;

    int baseLength = (N - 1) / K;
    int remainder = (N - 1) % K;

    vector<int> branchLengths;
    for(int i = 0; i < K; ++i) {
        if (i < remainder) {
            branchLengths.push_back(baseLength + 1);
        } else {
            branchLengths.push_back(baseLength);
        }
    }

    int maxDistance = branchLengths[0] + branchLengths[1];
    cout << maxDistance << endl;

    int currentNodeIndex = 2;
    int rootNode = 1;

    for(int length : branchLengths) {
        int previousNode = rootNode;
        for(int j = 0; j < length; ++j) {
            cout << previousNode << " " << currentNodeIndex << endl;
            previousNode = currentNodeIndex;
            currentNodeIndex++;
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
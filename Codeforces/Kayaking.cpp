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
    int N;
    cin >> N;
    int totalPeople = 2 * N;
    vector<int> peopleWeights(totalPeople);
    for(int i = 0; i < totalPeople; ++i) {
        cin >> peopleWeights[i];
    }

    sort(all(peopleWeights));

    int minTotalInstability = 2e9;

    for(int i = 0; i < totalPeople; ++i) {
        for(int j = i + 1; j < totalPeople; ++j) {
            vector<int> currentGroup;
            for(int k = 0; k < totalPeople; ++k) {
                if(k == i || k == j) continue;
                currentGroup.push_back(peopleWeights[k]);
            }

            int currentInstability = 0;
            for(int k = 0; k < size(currentGroup); k += 2) {
                currentInstability += (currentGroup[k+1] - currentGroup[k]);
            }

            if(currentInstability < minTotalInstability) {
                minTotalInstability = currentInstability;
            }
        }
    }
    cout << minTotalInstability << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
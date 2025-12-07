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

    vector<int> hiddenPermutation(N + 1);
    vector<bool> visitedArray(N + 1, false);

    for(int i = 1; i <= N; ++i) {
        if(visitedArray[i]) continue;

        vector<int> cyclePath;
        while(true) {
            cout << "? " << i << endl;
            cout.flush();
            int returnedValue;
            cin >> returnedValue;
            cyclePath.push_back(returnedValue);

            if(size(cyclePath) > 1 && cyclePath.front() == cyclePath.back()) {
                break;
            }
        }

        cyclePath.pop_back();
        int pathLength = size(cyclePath);
        for(int j = 0; j < pathLength; ++j) {
            hiddenPermutation[cyclePath[j]] = cyclePath[(j + 1) % pathLength];
            visitedArray[cyclePath[j]] = true;
        }
    }

    cout << "!";
    for(int i = 1; i <= N; ++i) {
        cout << " " << hiddenPermutation[i];
    }
    cout << endl;
    cout.flush();
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
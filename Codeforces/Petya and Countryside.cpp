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
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> heightArray(N);
    for (int i = 0; i < N; ++i) {
        cin >> heightArray[i];
    }

    int maxWatered = 0;
    for (int i = 0; i < N; ++i) {
        int currentWatered = 1;

        int leftIndex = i - 1;
        while (leftIndex >= 0 && heightArray[leftIndex] <= heightArray[leftIndex + 1]) {
            currentWatered++;
            leftIndex--;
        }

        int rightIndex = i + 1;
        while (rightIndex < N && heightArray[rightIndex] <= heightArray[rightIndex - 1]) {
            currentWatered++;
            rightIndex++;
        }

        if (currentWatered > maxWatered) {
            maxWatered = currentWatered;
        }
    }

    cout << maxWatered << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}
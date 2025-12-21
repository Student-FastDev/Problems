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
    int N, M, minVal, maxVal;
    cin >> N >> M >> minVal >> maxVal;

    vector<int> temperatureArray(M);
    bool hasMinVal = false;
    bool hasMaxVal = false;
    bool isValidRange = true;

    for (int i = 0; i < M; ++i) {
        cin >> temperatureArray[i];
        if (temperatureArray[i] < minVal || temperatureArray[i] > maxVal) isValidRange = false;
        if (temperatureArray[i] == minVal) hasMinVal = true;
        if (temperatureArray[i] == maxVal) hasMaxVal = true;
    }

    if (!isValidRange) {
        cout << "Incorrect" << endl;
        return;
    }

    int neededCount = 0;
    if (!hasMinVal) neededCount++;
    if (!hasMaxVal) neededCount++;

    int availableSlots = N - M;
    if (availableSlots >= neededCount) {
        cout << "Correct" << endl;
    } else {
        cout << "Incorrect" << endl;
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
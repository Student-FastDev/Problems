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
    int formatType;
    cin >> formatType;
    string timeString;
    cin >> timeString;

    int bestHourCost = 100;
    string bestHourString = "";

    int startHour = 0;
    int endHour = 23;
    if (formatType == 12) {
        startHour = 1;
        endHour = 12;
    }

    for (int h = startHour; h <= endHour; ++h) {
        string currentHourString = to_string(h);
        if (size(currentHourString) < 2) currentHourString = "0" + currentHourString;

        int currentCost = 0;
        if (currentHourString[0] != timeString[0]) currentCost++;
        if (currentHourString[1] != timeString[1]) currentCost++;

        if (currentCost < bestHourCost) {
            bestHourCost = currentCost;
            bestHourString = currentHourString;
        }
    }

    int bestMinuteCost = 100;
    string bestMinuteString = "";

    for (int m = 0; m <= 59; ++m) {
        string currentMinuteString = to_string(m);
        if (size(currentMinuteString) < 2) currentMinuteString = "0" + currentMinuteString;

        int currentCost = 0;
        if (currentMinuteString[0] != timeString[3]) currentCost++;
        if (currentMinuteString[1] != timeString[4]) currentCost++;

        if (currentCost < bestMinuteCost) {
            bestMinuteCost = currentCost;
            bestMinuteString = currentMinuteString;
        }
    }

    cout << bestHourString << ":" << bestMinuteString << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
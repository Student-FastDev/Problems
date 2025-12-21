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
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<int> fullCalendar;

    vector<int> yearTypes = {0, 0, 0, 1, 0, 0}; 

    for (int yearType : yearTypes) {
        for (int m = 0; m < 12; ++m) {
            if (m == 1 && yearType == 1) fullCalendar.push_back(29);
            else fullCalendar.push_back(daysInMonth[m]);
        }
    }

    bool isPossible = false;
    for (int i = 0; i + N <= (int)size(fullCalendar); ++i) {
        bool isMatch = true;
        for (int j = 0; j < N; ++j) {
            if (fullCalendar[i + j] != A[j]) {
                isMatch = false;
                break;
            }
        }
        if (isMatch) {
            isPossible = true;
            break;
        }
    }

    if (isPossible) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
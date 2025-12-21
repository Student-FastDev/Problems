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
    int H, M;
    cin >> H >> M;
    string timeString;
    cin >> timeString;

    int currentHour = (timeString[0] - '0') * 10 + (timeString[1] - '0');
    int currentMinute = (timeString[3] - '0') * 10 + (timeString[4] - '0');

    vector<int> reflectionMapping(10, -1);
    reflectionMapping[0] = 0;
    reflectionMapping[1] = 1;
    reflectionMapping[2] = 5;
    reflectionMapping[5] = 2;
    reflectionMapping[8] = 8;

    while (true) {
        int hourDigit0 = currentHour / 10;
        int hourDigit1 = currentHour % 10;
        int minuteDigit0 = currentMinute / 10;
        int minuteDigit1 = currentMinute % 10;

        if (reflectionMapping[hourDigit0] != -1 && reflectionMapping[hourDigit1] != -1 && 
            reflectionMapping[minuteDigit0] != -1 && reflectionMapping[minuteDigit1] != -1) {
            
            int reflectedHour = reflectionMapping[minuteDigit1] * 10 + reflectionMapping[minuteDigit0];
            int reflectedMinute = reflectionMapping[hourDigit1] * 10 + reflectionMapping[hourDigit0];

            if (reflectedHour < H && reflectedMinute < M) {
                cout << (currentHour < 10 ? "0" : "") << currentHour << ":" << (currentMinute < 10 ? "0" : "") << currentMinute << endl;
                return;
            }
        }

        currentMinute++;
        if (currentMinute == M) {
            currentMinute = 0;
            currentHour++;
        }
        if (currentHour == H) {
            currentHour = 0;
        }
    }
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
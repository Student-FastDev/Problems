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
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

bool queryFunction(const string& t) {
    cout << "? " << t << endl;
    int response;
    cin >> response;
    return response == 1;
}

void solveTestCase() {
    int N;
    cin >> N;

    string finalResult = "";

    if (!queryFunction("0")) {
        finalResult = string(N, '1');
    } else {
        string S = "0";

        while ((int)size(S) < N) {
            char firstTry = (rand() % 2 == 0) ? '0' : '1';
            char secondTry = (firstTry == '0') ? '1' : '0';

            if (queryFunction(S + firstTry)) {
                S += firstTry;
            } else if (queryFunction(S + secondTry)) {
                S += secondTry;
            } else {
                break;
            }
        }

        while ((int)size(S) < N) {
            if (queryFunction("0" + S)) S = "0" + S;
            else S = "1" + S;
        }
        finalResult = S;
    }

    cout << "! " << finalResult << endl;
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

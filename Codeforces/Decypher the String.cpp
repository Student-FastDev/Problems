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
    string finalString;
    cin >> finalString;
    int N = size(finalString);

    string queryOne(N, ' ');
    string queryTwo(N, ' ');
    string queryThree(N, ' ');

    for(int i = 0; i < N; ++i) {
        queryOne[i] = 'a' + (i % 26);
        queryTwo[i] = 'a' + ((i / 26) % 26);
        queryThree[i] = 'a' + ((i / 676) % 26);
    }

    auto askQuery = [&](string S) {
        cout << "? " << S << endl;
        cout.flush();
        string response;
        cin >> response;
        return response;
    };

    string responseOne = askQuery(queryOne);
    string responseTwo = askQuery(queryTwo);
    string responseThree = askQuery(queryThree);

    string originalS(N, ' ');
    for(int i = 0; i < N; ++i) {
        int valOne = responseOne[i] - 'a';
        int valTwo = responseTwo[i] - 'a';
        int valThree = responseThree[i] - 'a';
        
        int originalIndex = valOne + valTwo * 26 + valThree * 676;
        originalS[originalIndex] = finalString[i];
    }

    cout << "! " << originalS << endl;
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
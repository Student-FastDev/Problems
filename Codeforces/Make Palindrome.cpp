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
    string S;
    cin >> S;

    vector<int> charCounts(26, 0);
    for(char c : S) {
        charCounts[c - 'a']++;
    }

    vector<char> oddChars;
    for(int i = 0; i < 26; ++i) {
        if (charCounts[i] % 2 != 0) {
            oddChars.push_back((char)('a' + i));
        }
    }

    int K = size(oddChars);
    for(int i = 0; i < K / 2; ++i) {
        char smallChar = oddChars[i];
        char largeChar = oddChars[K - 1 - i];
        charCounts[smallChar - 'a']++;
        charCounts[largeChar - 'a']--;
    }

    string halfString = "";
    char middleChar = 0;

    for(int i = 0; i < 26; ++i) {
        char currentChar = (char)('a' + i);
        if (charCounts[i] % 2 != 0) {
            middleChar = currentChar;
            charCounts[i]--;
        }
        for(int j = 0; j < charCounts[i] / 2; ++j) {
            halfString += currentChar;
        }
    }

    string resultString = halfString;
    if (middleChar != 0) {
        resultString += middleChar;
    }
    reverse(all(halfString));
    resultString += halfString;

    cout << resultString << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
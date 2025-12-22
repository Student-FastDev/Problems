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
const ll MAX_N = 1200000;
const ll MOD = 1e9+7; // 998244353

int trieArray[MAX_N][26];
int nodesCount = 1; 

void solveTestCase() {
    string S;
    cin >> S;

    string inputString;
    cin >> inputString;

    int K;
    cin >> K;

    bool isBad[26];
    for (int i = 0; i < 26; ++i) {
        if (inputString[i] == '0') isBad[i] = true;
        else isBad[i] = false;
    }

    for (int i = 0; i < 26; ++i) {
        trieArray[0][i] = -1;
    }

    ll distinctCount = 0;
    int N = S.length();

    for (int i = 0; i < N; ++i) {
        int currentNode = 0;
        int badCount = 0;

        for (int j = i; j < N; ++j) {
            int characterIndex = S[j] - 'a';

            if (isBad[characterIndex]) badCount++;
            if (badCount > K) break;

            if (trieArray[currentNode][characterIndex] == -1) {
                distinctCount++;
                
                for (int z = 0; z < 26; ++z) trieArray[nodesCount][z] = -1;
                trieArray[currentNode][characterIndex] = nodesCount;
                nodesCount++;
            }

            currentNode = trieArray[currentNode][characterIndex];
        }
    }

    cout << distinctCount << endl;

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
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
    int N, K;
    cin >> N >> K;
    int maxPairs = K / 2;
    int totalPairs = (1 << N) - 1;

    vector<long long> pairValue(totalPairs + 1, 0);

    for (int level = 1; level <= N; ++level) {
        int numCards = 1 << level;
        vector<long long> cards(numCards);
        for (int I = 0; I < numCards; ++I) {
            cin >> cards[I];
        }

        int pairStartIndex = 1 << (level - 1);
        for (int J = 0; J < numCards / 2; ++J) {
            int index = pairStartIndex + J;
            pairValue[index] = cards[2 * J] + cards[2 * J + 1];
        }
    }

    vector<vector<long long>> DP(totalPairs + 1, vector<long long>(maxPairs + 1, -INF));

    for (int currentNode = totalPairs; currentNode >= 1; --currentNode) {
        int leftChild = currentNode * 2;
        int rightChild = currentNode * 2 + 1;

        if (leftChild > totalPairs) {
            DP[currentNode][0] = 0;
            if (maxPairs >= 1) {
                DP[currentNode][1] = pairValue[currentNode];
            }
        } else {
            DP[currentNode][0] = 0;
            for (int T = 1; T <= maxPairs; ++T) {
                long long bestValue = -INF;
                for (int X = 0; X <= T - 1; ++X) {
                    int Y = (T - 1) - X;
                    if (DP[leftChild][X] == -INF || DP[rightChild][Y] == -INF) continue;
                    bestValue = max(bestValue, pairValue[currentNode] + DP[leftChild][X] + DP[rightChild][Y]);
                }
                DP[currentNode][T] = bestValue;
            }
        }
    }

    long long finalAnswer = 0;
    for (int T = 0; T <= maxPairs; ++T) {
        finalAnswer = max(finalAnswer, DP[1][T]);
    }
    cout << finalAnswer << endl;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

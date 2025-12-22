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
const ll MAX_N = 5e4+7;
const ll MOD = 1e9+7; // 998244353

struct Node {
    int childrenNode[26];
    int failEdge;
    bool isBad;
} trieArray[MAX_N];

int nodesCount = 1;
int DP[2][MAX_N];

void insertTrie(const string& s) {
    int currentValue = 0;
    for (char c : s) {
        int idx = c - 'a';
        if (trieArray[currentValue].childrenNode[idx] == 0) {
            trieArray[currentValue].childrenNode[idx] = nodesCount++;
        }
        currentValue = trieArray[currentValue].childrenNode[idx];
    }
    trieArray[currentValue].isBad = true;
}

void buildCorasick() {
    queue<int> queueArray;
    for (int i = 0; i < 26; ++i) {
        if (trieArray[0].childrenNode[i] != 0) {
            trieArray[trieArray[0].childrenNode[i]].failEdge = 0;
            queueArray.push(trieArray[0].childrenNode[i]);
        }
    }

    while (!queueArray.empty()) {
        int u = queueArray.front();
        queueArray.pop();
        trieArray[u].isBad |= trieArray[trieArray[u].failEdge].isBad;

        for (int i = 0; i < 26; ++i) {
            if (trieArray[u].childrenNode[i] != 0) {
                int v = trieArray[u].childrenNode[i];
                trieArray[v].failEdge = trieArray[trieArray[u].failEdge].childrenNode[i];
                queueArray.push(v);
            } else {
                trieArray[u].childrenNode[i] = trieArray[trieArray[u].failEdge].childrenNode[i];
            }
        }
    }
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        insertTrie(s);
    }

    buildCorasick();

    DP[0][0] = 1;

    for (int i = 0; i < N; ++i) {
        int currentValue = i % 2;
        int nextRow = (i + 1) % 2;
        
        memset(DP[nextRow], 0, sizeof(int) * nodesCount);

        for (int u = 0; u < nodesCount; ++u) {
            if (DP[currentValue][u] == 0) continue;
            
            int waysCount = DP[currentValue][u];
            
            for (int c = 0; c < 26; ++c) {
                int v = trieArray[u].childrenNode[c];
                if (!trieArray[v].isBad) {
                    DP[nextRow][v] += waysCount;
                    if (DP[nextRow][v] >= MOD) DP[nextRow][v] -= MOD;
                }
            }
        }
    }

    int finalResult = 0;
    int finalRow = N % 2;
    for (int u = 0; u < nodesCount; ++u) {
        if (!trieArray[u].isBad) {
            finalResult += DP[finalRow][u];
            if (finalResult >= MOD) finalResult -= MOD;
        }
    }

    cout << finalResult << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

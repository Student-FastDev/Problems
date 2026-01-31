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

struct TrieNode {
    int nextNodes[26];
    bool canWin;
    bool canLose;
    TrieNode() {
        memset(nextNodes, -1, sizeof(nextNodes));
        canWin = false;
        canLose = false;
    }
};

vector<TrieNode> trie;

void computeGameStates(int nodeIndex) {
    bool isLeaf = true;
    for (int i = 0; i < 26; ++i) {
        if (trie[nodeIndex].nextNodes[i] != -1) {
            isLeaf = false;
            int childIndex = trie[nodeIndex].nextNodes[i];
            computeGameStates(childIndex);
            if (!trie[childIndex].canWin) trie[nodeIndex].canWin = true;
            if (!trie[childIndex].canLose) trie[nodeIndex].canLose = true;
        }
    }
    if (isLeaf) {
        trie[nodeIndex].canWin = false;
        trie[nodeIndex].canLose = true;
    }
}

void solveTestCase() {
    int N;
    ll K;
    cin >> N >> K;

    trie.clear();
    trie.emplace_back();

    for (int i = 0; i < N; ++i) {
        string inputString;
        cin >> inputString;
        int currentNode = 0;
        for (char character : inputString) {
            int charIndex = character - 'a';
            if (trie[currentNode].nextNodes[charIndex] == -1) {
                int nextNodeIndex = size(trie);
                trie.emplace_back();
                trie[currentNode].nextNodes[charIndex] = nextNodeIndex;
            }
            currentNode = trie[currentNode].nextNodes[charIndex];
        }
    }

    computeGameStates(0);

    if (trie[0].canWin && trie[0].canLose) {
        cout << "First" << endl;
    } else if (trie[0].canWin) {
        if (K % 2 != 0) cout << "First" << endl;
        else cout << "Second" << endl;
    } else {
        cout << "Second" << endl;
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
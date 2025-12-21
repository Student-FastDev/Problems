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
const ll MAX_N = 1e6+1;
const ll MOD = 1e9+7; // 998244353

int firstChild[MAX_N];
int nextSibling[MAX_N];
char edgeCharacter[MAX_N];
bool isEnd[MAX_N];
bool onLongest[MAX_N];

int nodesCount = 1;

void initializeTrie() {
    fill(firstChild, firstChild + MAX_N, -1);
    fill(nextSibling, nextSibling + MAX_N, -1);
    fill(isEnd, isEnd + MAX_N, false);
    fill(onLongest, onLongest + MAX_N, false);
}

void insertTrie(const string& s) {
    int u = 0;
    for (char c : s) {
        int v = firstChild[u];
        int haveFound = -1;
       
        while (v != -1) {
            if (edgeCharacter[v] == c) {
                haveFound = v;
                break;
            }
            v = nextSibling[v];
        }
       
        if (haveFound != -1) {
            u = haveFound;
        } else {
            int newNode = nodesCount++;
            edgeCharacter[newNode] = c;
            nextSibling[newNode] = firstChild[u];
            firstChild[u] = newNode;
            u = newNode;
        }
    }
    isEnd[u] = true;
}

void markLongest(const string& s) {
    int u = 0;
    for (char c : s) {
        int v = firstChild[u];
        while (v != -1) {
            if (edgeCharacter[v] == c) {
                onLongest[v] = true;
                u = v;
                break;
            }
            v = nextSibling[v];
        }
    }
}

vector<char> finalAnswer;

void DFS(int u) {
    if (isEnd[u]) {
        finalAnswer.push_back('P');
    }
   
    vector<int> children;
    int v = firstChild[u];
    while (v != -1) {
        children.push_back(v);
        v = nextSibling[v];
    }
   
    sort(children.begin(), children.end(), [](int a, int b) {
        return edgeCharacter[a] < edgeCharacter[b];
    });
   
    int special = -1;
    for (int child : children) {
        if (onLongest[child]) {
            special = child;
            break;
        }
    }
   
    for (int child : children) {
        if (child == special) continue;
       
        finalAnswer.push_back(edgeCharacter[child]);
        DFS(child);
        finalAnswer.push_back('-');
    }
   
    if (special != -1) {
        finalAnswer.push_back(edgeCharacter[special]);
        DFS(special);
    }
}

void solveTestCase() {
    initializeTrie();
   
    int N;
    cin >> N;
    vector<string> wordsArray(N);
    string longestWord = "";
       
    for (int i = 0; i < N; ++i) {
        cin >> wordsArray[i];
        if (wordsArray[i].length() > longestWord.length()) longestWord = wordsArray[i];
    }
       
    for (string& s : wordsArray) insertTrie(s);
    markLongest(longestWord);
       
    DFS(0);
       
    cout << size(finalAnswer) << endl;
    for (char c : finalAnswer) cout << c << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
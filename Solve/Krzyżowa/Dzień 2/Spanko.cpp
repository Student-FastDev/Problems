// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.right(),o){o<<'{';int i=2;for(auto event:X)o<<(", ")+i<<event,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 100005;
const ll MOD = 1e9+7; // 998244353

const int MAX_NODES = 6e6 + 1; 

int getIndex(char character) {
    if (character == 'A') return 0;
    if (character == 'G') return 1;
    if (character == 'C') return 2;
    if (character == 'U') return 3;
    return 0;
}

int prefixTrie[MAX_NODES][4];
int suffixTrie[MAX_NODES][4];
int nodesPrefix = 1;
int nodesSuffix = 1;

int finalNodePrefix[MAX_N];
int finalNodeSuffix[MAX_N];

int inPrefix[MAX_NODES], outPrefix[MAX_NODES], timerPreffix = 0;
int inSuffix[MAX_NODES], outSuffix[MAX_NODES], timerSuffix = 0;

int treeArray[MAX_NODES * 4];
int maxBit;

void updateTree(int node, int left, int right, int index, int value) {
    if (left == right) {
        treeArray[node] += value;
        return;
    }
    int middleValue = (left + right) / 2;
    if (index <= middleValue) updateTree(node * 2, left, middleValue, index, value);
    else updateTree(node * 2 + 1, middleValue + 1, right, index, value);
    treeArray[node] = treeArray[node * 2] + treeArray[node * 2 + 1];
}

int queryTree(int node, int left, int right, int l, int r) {
    if (r < left || right < l) return 0;
    if (l <= left && right <= r) return treeArray[node];
    int middleValue = (left + right) / 2;
    return queryTree(node * 2, left, middleValue, l, r) + queryTree(node * 2 + 1, middleValue + 1, right, l, r);
}

struct Event {
    int X;         
    int currentType; 
    int firstY, secondY; 
    int ID;         
    int currentSign;

    bool operator<(Event &other) const {
        if (X != other.X) return X < other.X;
        return currentType < other.currentType;
    }
};

int finalAnswers[MAX_N];

void insertTrie(int trieArray[][4], int &nodeCount, const string &S, int ID, int finalArray[]) {
    int U = 0;
    for (char c : S) {
        int V = getIndex(c);
        if (!trieArray[U][V]) trieArray[U][V] = nodeCount++;
        U = trieArray[U][V];
    }
    finalArray[ID] = U;
}

int findNode(int trieArray[][4], const string &S) {
    int U = 0;
    for (char c : S) {
        int V = getIndex(c);
        if (!trieArray[U][V]) return -1;
        U = trieArray[U][V];
    }
    return U;
}

void DFS(int U, int trieArray[][4], int timeIn[], int timeOut[], int &currentTimer) {
    timeIn[U] = ++currentTimer;
    for (int i = 0; i < 4; i++) {
        if (trieArray[U][i]) DFS(trieArray[U][i], trieArray, timeIn, timeOut, currentTimer);
    }
    timeOut[U] = currentTimer;
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    string S;
    for (int i = 0; i < N; ++i) {
        cin >> S;
        insertTrie(prefixTrie, nodesPrefix, S, i, finalNodePrefix);
        
        reverse(all(S));
        insertTrie(suffixTrie, nodesSuffix, S, i, finalNodeSuffix);
    }

    DFS(0, prefixTrie, inPrefix, outPrefix, timerPreffix);
    DFS(0, suffixTrie, inSuffix, outSuffix, timerSuffix);

    vector<Event> eventsArray;
    eventsArray.reserve(N + 2 * M);

    for (int i = 0; i < N; ++i) {
        int X = inPrefix[finalNodePrefix[i]];
        int y = inSuffix[finalNodeSuffix[i]];
        eventsArray.push_back({X, 0, y, 0, 0, 0});
    }

    string P, Q;
    for (int i = 0; i < M; ++i) {
        cin >> P >> Q;
        
        int U = findNode(prefixTrie, P);
        reverse(all(Q));
        int V = findNode(suffixTrie, Q);

        if (U == -1 || V == -1) {
            finalAnswers[i] = 0;
            continue;
        }

        int firstX = inPrefix[U];
        int secondX = outPrefix[U];
        int firstY = inSuffix[V];
        int secondY = outSuffix[V];

        eventsArray.push_back({secondX, 1, firstY, secondY, i, 1});
        eventsArray.push_back({firstX - 1, 1, firstY, secondY, i, -1});
    }

    sort(all(eventsArray));
    maxBit = timerSuffix;
    for (auto &event : eventsArray) {
        if (event.currentType == 0) {
            updateTree(1, 1, maxBit, event.firstY, 1);
            LOG(treeArray);
        } else {
            if (event.X < 0) continue;
            int currentCount = queryTree(1, 1, maxBit, event.firstY, event.secondY);
            LOG(currentCount);
            LOG(event.currentSign);
            finalAnswers[event.ID] += event.currentSign * currentCount;
        }
    }

    for (int i = 0; i < M; ++i) {
        cout << finalAnswers[i] << endl;
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

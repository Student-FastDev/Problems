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
const ll MAX_N = 1000005;
const ll MOD = 1e9+7;

int N, Q;
vector<int> neighbourList[MAX_N];
int depthArray[MAX_N];
int countArray[MAX_N];
int suffixArray[MAX_N];
int maxValueD[MAX_N];
int answerMEMO[MAX_N];
bool computedArray[MAX_N];
int queueArray[MAX_N];
int maxDepth = 0;

void BFS(int startNode) {
    int head = 0, tail = 0;
    queueArray[tail++] = startNode;
    depthArray[startNode] = 1;
    maxDepth = 1;
    countArray[1]++;

    while (head < tail) {
        int u = queueArray[head++];
        for (int v : neighbourList[u]) {
            depthArray[v] = depthArray[u] + 1;
            if (depthArray[v] > maxDepth) maxDepth = depthArray[v];
            countArray[depthArray[v]]++;
            queueArray[tail++] = v;
        }
    }
}

int solveQuery(int k) {
    if (k >= N) return maxDepth;
    if (computedArray[k]) return answerMEMO[k];
    int currentAnswer = maxDepth;
    
    for (int v = 2; ; ++v) {
        ll threshold = (ll)(v - 1) * k + 1;
        if (threshold > N) break;
        
        int d = maxValueD[threshold];
        if (d == 0) break;
        
        if (d - 1 + v > currentAnswer) {
            currentAnswer = d - 1 + v;
        }
    }

    computedArray[k] = true;
    answerMEMO[k] = currentAnswer;
    return currentAnswer;
}

void solveTestCase() {
    cin >> N >> Q;

    vector<int> queriesArray(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queriesArray[i];
    }

    for (int i = 2; i <= N; i++) {
        int p;
        cin >> p;
        neighbourList[p].push_back(i);
    }

    BFS(1);

    for (int d = maxDepth; d >= 1; d--) {
        suffixArray[d] = countArray[d] + suffixArray[d + 1];
    }

    for (int d = maxDepth; d >= 1; d--) {
        int lower = suffixArray[d + 1] + 1;
        int upper = suffixArray[d];
        for (int value = lower; value <= upper; value++) {
            maxValueD[value] = d;
        }
    }

    for (int i = 0; i < Q; i++) {
        cout << solveQuery(queriesArray[i]) << (i == Q - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
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

int N, M, K;
vector<vector<pii>> neighbourList;
vector<pii> edges;
vector<int> degreeArray;
vector<bool> isActive;
vector<bool> isEdgeRemoved;
queue<int> deletionQueue;
int currentActiveCount;

void processDeletions() {
    while (!deletionQueue.empty()) {
        int u = deletionQueue.front();
        deletionQueue.pop();

        for (auto& edge : neighbourList[u]) {
            int v = edge.first;
            int edgeIdx = edge.second;

            if (isEdgeRemoved[edgeIdx]) continue;
            if (!isActive[v]) continue;

            degreeArray[v]--;
            if (degreeArray[v] < K && isActive[v]) {
                isActive[v] = false;
                currentActiveCount--;
                deletionQueue.push(v);
            }
        }
    }
}

void solveTestCase() {
    cin >> N >> M >> K;

    neighbourList.assign(N, vector<pii>());
    edges.resize(M);
    degreeArray.assign(N, 0);
    isActive.assign(N, true);
    isEdgeRemoved.assign(M, false);
    currentActiveCount = N;

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edges[i] = {u, v};
        neighbourList[u].push_back({v, i});
        neighbourList[v].push_back({u, i});
        degreeArray[u]++;
        degreeArray[v]++;
    }

    for (int i = 0; i < N; ++i) {
        if (degreeArray[i] < K) {
            isActive[i] = false;
            currentActiveCount--;
            deletionQueue.push(i);
        }
    }

    processDeletions();

    vector<int> resultVector(M);
    resultVector[M - 1] = currentActiveCount;

    for (int i = M - 1; i > 0; --i) {
        int u = edges[i].first;
        int v = edges[i].second;
        isEdgeRemoved[i] = true;

        if (isActive[u] && isActive[v]) {
            degreeArray[u]--;
            degreeArray[v]--;
            
            if (degreeArray[u] < K) {
                isActive[u] = false;
                currentActiveCount--;
                deletionQueue.push(u);
            }
            if (degreeArray[v] < K && isActive[v]) {
                isActive[v] = false;
                currentActiveCount--;
                deletionQueue.push(v);
            }
            processDeletions();
        }
        resultVector[i - 1] = currentActiveCount;
    }

    for (int i = 0; i < M; ++i) {
        cout << resultVector[i] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
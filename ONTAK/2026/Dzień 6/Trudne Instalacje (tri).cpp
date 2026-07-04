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

struct Edge {
    int to;
    int weight;
};

struct Node {
    ll minW;
    ll minR;
    int bestVertex;
    int currentNode;
};

vector<vector<Edge>> neighbourList;
vector<vector<Edge>> reversedNeighbourList;
vector<int> outDegree;

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    neighbourList.resize(N + 1);
    reversedNeighbourList.resize(N + 1);
    outDegree.resize(N + 1);
    fill(all(outDegree), 0);

    int currentWeight = 0;
    for(int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        neighbourList[a].push_back({b, c});
        reversedNeighbourList[b].push_back({a, c});
        currentWeight = c;
        outDegree[a]++;
    }

    queue<int> queueArray;
    vector<int> DP(N + 1, 0);
    for(int i = 1; i <= N; i++) if(outDegree[i] == 0) queueArray.push(i);

    while(!queueArray.empty()) {
        int currentVertex = queueArray.front();
        queueArray.pop();
        
        for(auto& edge : reversedNeighbourList[currentVertex]) {
            int targetNode = edge.to;
            DP[targetNode] = max(DP[targetNode], DP[currentVertex] + 1);
            outDegree[targetNode]--;
            if(outDegree[targetNode] == 0) queueArray.push(targetNode);
        }
    }

    vector<vector<int>> levelNodes(N + 1);
    int maxValue = -1;
    for(int i = 1; i <= N; i++) {
        if(DP[i] > 0) {
            levelNodes[DP[i]].push_back(i);
            maxValue = max(maxValue, DP[i]);
        }
    }

    vector<ll> S(N + 1, 0);
    vector<int> R(N + 1, 0);

    for(int level = 1; level <= N; level++) {
        vector<Node> levelData(size(levelNodes[level]));
        for(int u : levelNodes[level]) {
            ll minW = INF;
            int minR = INT_MAX / 4;
            int bestVertex = -1;
            
            for(auto& edge : neighbourList[u]) {
                int targetNode = edge.to;
                if(DP[targetNode] == level - 1) {
                    if(edge.weight < minW || (edge.weight == minW && R[targetNode] < minR)) {
                        minW = edge.weight;
                        minR = R[targetNode];
                        bestVertex = targetNode;
                    }
                }
            }
            levelData.push_back({minW, minR, bestVertex, u});
        }

        for(auto& data : levelData) S[data.currentNode] = data.minW + S[data.bestVertex];

        sort(all(levelData), [](const Node& a, const Node& b) {
            if(a.minW != b.minW) return a.minW < b.minW;
            return a.minR < b.minR;
        });

        if(!levelData.empty()) {
            int currentRank = 1;
            R[levelData[0].currentNode] = currentRank;
            for(int i = 1; i < size(levelData); i++) {
                if(levelData[i].minW != levelData[i - 1].minW || levelData[i].minR != levelData[i - 1].minR) currentRank++;
                R[levelData[i].currentNode] = currentRank;
            }
        }
    }

    for(int i = 1; i <= N; i++) cout << DP[i] << " " << S[i] << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

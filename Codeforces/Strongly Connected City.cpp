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

bool checkReachability(int startNode, int totalNodes, const vector<vector<int>>& neighbourList) {
    vector<bool> visitedArray(totalNodes, false);
    queue<int> bfsQueue;
    
    visitedArray[startNode] = true;
    bfsQueue.push(startNode);
    int visitedCount = 0;
    
    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        visitedCount++;
        
        for (int neighborNode : neighbourList[currentNode]) {
            if (!visitedArray[neighborNode]) {
                visitedArray[neighborNode] = true;
                bfsQueue.push(neighborNode);
            }
        }
    }
    
    return visitedCount == totalNodes;
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    
    string horizontalStreets;
    string verticalStreets;
    cin >> horizontalStreets >> verticalStreets;
    
    int totalNodes = N * M;
    vector<vector<int>> neighbourList(totalNodes);
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int currentNodeIndex = i * M + j;
            
            if (j + 1 < M) {
                int rightNodeIndex = i * M + (j + 1);
                if (horizontalStreets[i] == '>') {
                    neighbourList[currentNodeIndex].push_back(rightNodeIndex);
                } else {
                    neighbourList[rightNodeIndex].push_back(currentNodeIndex);
                }
            }
            
            if (i + 1 < N) {
                int downNodeIndex = (i + 1) * M + j;
                if (verticalStreets[j] == 'v') {
                    neighbourList[currentNodeIndex].push_back(downNodeIndex);
                } else {
                    neighbourList[downNodeIndex].push_back(currentNodeIndex);
                }
            }
        }
    }
    
    for (int i = 0; i < totalNodes; ++i) {
        if (!checkReachability(i, totalNodes, neighbourList)) {
            cout << "NO" << endl;
            return;
        }
    }
    
    cout << "YES" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
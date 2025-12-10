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
const ll MAX_N = 1e6 + 5;
const ll MOD = 1e9+7; // 998244353

int N, targetNode, startNode;
vector<vector<int>> neighbourList;
vector<vector<int>> nodeChildren;
vector<int> nodeParent;
vector<int> DP;
vector<int> pathWeight;

bool compareNodes(int x, int y) {
    return DP[x] > DP[y];
}

void DFS(int U, int p) {
    int currentDegree = size(neighbourList[U]);
    int firstMax = 0, secondMax = 0;

    if (p != 0) currentDegree--;

    DP[U] = currentDegree;
    nodeParent[U] = p;
    if (U != targetNode) pathWeight[U] += currentDegree - (U != startNode);

    for (int v : neighbourList[U]) {
        if (v != p) {
            pathWeight[v] = pathWeight[U];
            nodeChildren[U].push_back(v);
            DFS(v, U);

            if (DP[v] > firstMax) {
                secondMax = firstMax;
                firstMax = DP[v];
            } else if (DP[v] > secondMax) {
                secondMax = DP[v];
            }
        }
    }

    DP[U] += secondMax;
    sort(all(nodeChildren[U]), compareNodes);
}

bool check(int k) {
    int lastNode = 0;
    int U = startNode;
    int bufferValue = 0;

    while (U != targetNode) {
        bufferValue++;
        int usedBuffer = 0;

        if (pathWeight[U] > k) {
            return false;
        }

        for (int v : nodeChildren[U]) {
            if (v == lastNode) continue;
            if (DP[v] + pathWeight[U] <= k) break;
            if (bufferValue == 0) return false;

            bufferValue--;
            usedBuffer++;
        }

        k -= usedBuffer;
        lastNode = U;
        U = nodeParent[U];
    }

    return true;
}

void solveTestCase() {
    cin >> N >> targetNode >> startNode;

    neighbourList.assign(N + 1, vector<int>());
    nodeChildren.assign(N + 1, vector<int>());
    nodeParent.assign(N + 1, 0);
    DP.assign(N + 1, 0);
    pathWeight.assign(N + 1, 0);

    for (int i = 1; i < N; i++) {
        int U, v;
        cin >> U >> v;
        neighbourList[U].push_back(v);
        neighbourList[v].push_back(U);
    }

    DFS(targetNode, 0);

    int leftRange = 0, rightRange = N - 1;
    while (leftRange < rightRange) {
        int middleValue = (leftRange + rightRange) / 2;

        if (check(middleValue)) {
            rightRange = middleValue;
        } else {
            leftRange = middleValue + 1;
        }
    }

    cout << leftRange << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }

    return 0;
}

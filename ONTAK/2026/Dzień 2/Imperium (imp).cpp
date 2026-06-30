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

const ll INF = 1e9+67;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, P, Q;
    cin >> N >> P >> Q;

    vector<vector<int>> neighbourList(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }

    vector<int> parentArray(N + 1, 0);
    vector<bool> visitedArray(N + 1, false);
    queue<int> queueArray;
    queueArray.push(P); 
    visitedArray[P] = true;

    while (!queueArray.empty()) {
        int u = queueArray.front();
        queueArray.pop();
        if (u == Q) break;
        for (int v : neighbourList[u]) {
            if (!visitedArray[v]) {
                visitedArray[v] = true;
                parentArray[v] = u;
                queueArray.push(v);
            }
        }
    }

    vector<int> pathArray;
    int currentNode = Q;
    while (currentNode != P) {
        pathArray.push_back(currentNode);
        currentNode = parentArray[currentNode];
    }
    pathArray.push_back(P);
    reverse(all(pathArray));
    LOG(pathArray);

    vector<bool> inPath(N + 1, false);
    for (int u : pathArray) inPath[u] = true;

    vector<int> orderArray;
    vector<int> parentNode(N + 1, 0);
    queue<int> treeQueue;

    for (int u : pathArray) {
        for (int v : neighbourList[u]) {
            if (!inPath[v]) {
                parentNode[v] = u;
                treeQueue.push(v);
            }
        }
    }

    while (!treeQueue.empty()) {
        int u = treeQueue.front();
        treeQueue.pop();
        orderArray.push_back(u);
        for (int v : neighbourList[u]) {
            if (v != parentNode[u] && !inPath[v]) {
                parentNode[v] = u;
                treeQueue.push(v);
            }
        }
    }

    vector<int> T(N + 1, 0);
    for (int i = (int)size(orderArray) - 1; i >= 0; --i) {
        int u = orderArray[i];
        vector<int> childrenValues;
        for (int v : neighbourList[u]) {
            if (v != parentNode[u] && !inPath[v]) {
                childrenValues.push_back(T[v]);
            }
        }
        sort(all(childrenValues), greater<int>());
        int nodeResult = 0;
        for (int j = 0; j < size(childrenValues); ++j) nodeResult = max(nodeResult, (int)j + 1 + childrenValues[j]);
        T[u] = nodeResult;
    }

    LOG(T);
    int M = size(pathArray);
    vector<vector<int>> S(M + 1);
    for (int i = 0; i < M; ++i) {
        int u = pathArray[i];
        for (int v : neighbourList[u]) {
            if (!inPath[v]) S[i + 1].push_back(T[v]);
        }
        sort(all(S[i + 1]), greater<int>()); 
    }

    vector<vector<int>> prefixArray(M + 1), suffixArray(M + 1);
    for (int i = 1; i <= M; ++i) {
        int d = size(S[i]);
        prefixArray[i].assign(d + 1, 0); suffixArray[i].assign(d + 1, 0);
        
        prefixArray[i][0] = 0;
        for (int j = 0; j < d; ++j) prefixArray[i][j + 1] = max(prefixArray[i][j], j + 1 + S[i][j]);
        suffixArray[i][d] = 0;
        for (int j = d - 1; j >= 0; --j) suffixArray[i][j] = max(suffixArray[i][j + 1], j + 2 + S[i][j]);
    }

    for(int i = 1; i <= M; i++) LOG(prefixArray[i]);
    for(int i = 1; i <= M; i++) LOG(suffixArray[i]);

    auto baseTime = [&](int i) { return prefixArray[i][size(S[i])]; };
    auto evaluatePosition = [&](int i, int x) {
        int d = size(S[i]);
        int leftRange = 0, rightRange = d - 1, c = d;
        while (leftRange <= rightRange) {
            int middleValue = (rightRange + leftRange) / 2;
            if (S[i][middleValue] <= x) { c = middleValue; rightRange = middleValue - 1; } 
            else leftRange = middleValue + 1;
        }
        return max({c + 1 + x, prefixArray[i][c], suffixArray[i][c]});
    };

    auto getRight = [&](int k) {
        int value = baseTime(k);
        for (int i = k - 1; i >= 1; --i) value = evaluatePosition(i, value);
        return value;
    };

    auto getLeft = [&](int k) {
        int value = baseTime(k + 1);
        for (int i = k + 2; i <= M; ++i) value = evaluatePosition(i, value);
        return value;
    };

    int leftRange = 1, rightRange = M - 1;
    int optimalSplit = 1;
    while (leftRange <= rightRange) {
        int middleValue = (leftRange + rightRange) / 2;
        if (getRight(middleValue) <= getLeft(middleValue)) {
            optimalSplit = middleValue;
            leftRange = middleValue + 1;
        } else {
            rightRange = middleValue - 1;
        }
    }

    int finalAnswer = INF;
    for (int k = max(1, optimalSplit - 1); k <= min(M - 1, optimalSplit + 1); k++) finalAnswer = min(finalAnswer, max(getRight(k), getLeft(k)));

    cout << finalAnswer << endl; 
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
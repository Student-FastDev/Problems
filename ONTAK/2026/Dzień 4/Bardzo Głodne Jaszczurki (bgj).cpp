// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto currentParent)->decltype(currentParent.first,o){return o<<'('<<currentParent.first<<", "<<currentParent.second <<')';}
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
#define size(x)  (int)(x).size()

const int INF = 1e9+67;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

int N, K;
vector<int> sizeArray;
vector<int> rightArray;
vector<int> parentArray;
vector<int> inDegree;
vector<vector<int>> childrenArray;

vector<int> currentPath;
vector<vector<int>> answersArray;

int getValue(int vertex) {
    return (sizeArray[vertex] == -1) ? INF : sizeArray[vertex];
}

void addEdge(int fromVertex, int toVertex) {
    childrenArray[fromVertex].push_back(toVertex);
    inDegree[toVertex]++;
}

bool buildGraph() {
    vector<int> stackArray;

    for(int i = N; i >= 1; i--) {
        int lastPopped = 0;
        int valueI = getValue(i);

        while(!stackArray.empty()) {
            int topValue = getValue(stackArray.back());

            if (topValue < valueI) {
                int representative = stackArray.back();

                addEdge(representative, i);
                while(!stackArray.empty() && getValue(stackArray.back()) == topValue) {
                    lastPopped = topValue;
                    stackArray.pop_back();
                }
            } else {
                break;
            }
        }

        if (sizeArray[i] == -1) {
            rightArray[i] = N + 1;
            if (!stackArray.empty()) addEdge(stackArray.back(), i);
        } else {
            if (stackArray.empty()) return false;
            rightArray[i] = stackArray.back();

            addEdge(i, stackArray.back());
            if (lastPopped != sizeArray[i] - 1) return false;
        }

        stackArray.push_back(i);
    }

    return true;
}

bool isAcyclic() {
    vector<int> degreeArray = inDegree;
    queue<int> queueArray;

    for(int i = 1; i <= N; i++) {
        if (degreeArray[i] == 0) queueArray.push(i);
    }

    int visitedNumber = 0;
    while(!queueArray.empty()) {
        int currentVertex = queueArray.front();
        queueArray.pop();

        visitedNumber++;
        for(int nextVertex : childrenArray[currentVertex]) {
            degreeArray[nextVertex]--;

            if (degreeArray[nextVertex] == 0) {
                queueArray.push(nextVertex);
            }
        }
    }

    return visitedNumber == N;
}

void DFS(set<int>& availableSet) {
    if (size(answersArray) == K) return;

    if (size(currentPath) == N) {
        answersArray.push_back(currentPath);
        return;
    }

    if (availableSet.empty()) return;
    int currentVertex = *availableSet.begin();

    while (true) {
        LOG(availableSet);
        if (size(answersArray) == K) break;

        availableSet.erase(currentVertex);
        currentPath.push_back(currentVertex);

        vector<int> pushedArray;

        for(int nextVertex : childrenArray[currentVertex]) {
            inDegree[nextVertex]--;

            if (inDegree[nextVertex] == 0) {
                availableSet.insert(nextVertex);
                pushedArray.push_back(nextVertex);
            }
        }

        DFS(availableSet);

        for(int nextVertex : pushedArray) availableSet.erase(nextVertex);
        for(int nextVertex : childrenArray[currentVertex]) inDegree[nextVertex]++;
        currentPath.pop_back();
        availableSet.insert(currentVertex);

        if (size(answersArray) == K) break;
        auto currentIterator = availableSet.upper_bound(currentVertex);
        if (currentIterator == availableSet.end()) break;
        currentVertex = *currentIterator;
    }
}

void solveTestCase() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    sizeArray.assign(N + 1, 0);
    rightArray.assign(N + 2, 0);
    parentArray.assign(N + 1, 0);
    inDegree.assign(N + 1, 0);
    childrenArray.assign(N + 1, vector<int>());

    currentPath.clear();
    answersArray.clear();

    for(int i = 1; i <= N; i++) cin >> sizeArray[i];

    if (!buildGraph() || !isAcyclic()) {
        cout << "-1" << endl;
        return;
    }

    set<int> availableSet;
    for(int i = 1; i <= N; i++) {
        if (inDegree[i] == 0) availableSet.insert(i);
    }

    DFS(availableSet);

    if (size(answersArray) < K) {
        cout << "-1" << endl;
    } else {
        vector<int> B(N + 1);

        for(int i = 0; i < N; i++) B[answersArray.back()[i]] = i + 1;
        for(int i = 1; i <= N; i++) cout << B[i] << " ";
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }

    return 0;
}
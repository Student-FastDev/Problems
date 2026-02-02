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

struct TwoSatSolver {
    int P;
    vector<vector<int>> forwardGraph;
    vector<vector<int>> backwardGraph; 
    vector<int> assignmentResult;

    vector<bool> visitedArray;
    vector<int> executionOrder;
    vector<int> componentArray;
    int componentCounter;

    TwoSatSolver(int variablesCount) : P(variablesCount) {
        forwardGraph.resize(2 * P);
        backwardGraph.resize(2 * P);
    }

    void addImplication(int literalA, int literalB) {
        forwardGraph[literalA].push_back(literalB);
        backwardGraph[literalB].push_back(literalA);
        
        forwardGraph[literalB ^ 1].push_back(literalA ^ 1);
        backwardGraph[literalA ^ 1].push_back(literalB ^ 1);
    }

    void firstDFS(int currentVertex) {
        visitedArray[currentVertex] = true;
        for (int neighborVertex : forwardGraph[currentVertex]) {
            if (!visitedArray[neighborVertex]) {
                firstDFS(neighborVertex);
            }
        }
        executionOrder.push_back(currentVertex);
    }

    void secondDFS(int currentVertex, int currentComponentId) {
        componentArray[currentVertex] = currentComponentId;
        for (int neighborVertex : backwardGraph[currentVertex]) {
            if (componentArray[neighborVertex] == -1) {
                secondDFS(neighborVertex, currentComponentId);
            }
        }
    }

    bool solve() {
        int totalNodes = 2 * P;
        visitedArray.assign(totalNodes, false);
        executionOrder.clear();

        for (int i = 0; i < totalNodes; ++i) {
            if (!visitedArray[i]) {
                firstDFS(i);
            }
        }

        componentArray.assign(totalNodes, -1);
        componentCounter = 0;
        
        reverse(all(executionOrder));
        for (int vertexIndex : executionOrder) {
            if (componentArray[vertexIndex] == -1) {
                secondDFS(vertexIndex, componentCounter++);
            }
        }

        assignmentResult.resize(P);
        for (int i = 0; i < P; ++i) {
            if (componentArray[2 * i] == componentArray[2 * i + 1]) {
                return false;
            }
            
            assignmentResult[i] = (componentArray[2 * i] > componentArray[2 * i + 1] ? 1 : 0);
        }
        return true;
    }
};

struct VertexInfo {
    int colorIndex;
    int typeVariant;
};

int N;
vector<vector<int>> neighbourList;
vector<pii> colorPairs;
vector<VertexInfo> vertexToColor;

int getLiteral(int vertexIndex) {
    VertexInfo info = vertexToColor[vertexIndex];
    if (info.typeVariant == 0) return 2 * info.colorIndex;
    else return 2 * info.colorIndex + 1;
}

bool attemptRooting(int rootVertex) {
    TwoSatSolver solverInstance(N);

    int rootLiteral = getLiteral(rootVertex);
    solverInstance.addImplication(rootLiteral ^ 1, rootLiteral);

    vector<int> parentArray(2 * N + 1, 0);
    vector<int> queueArray;
    queueArray.reserve(2 * N);
    vector<bool> visitedArray(2 * N + 1, false);

    queueArray.push_back(rootVertex);
    visitedArray[rootVertex] = true;

    int headIndex = 0;
    while(headIndex < (int)size(queueArray)){
        int currentVertex = queueArray[headIndex++];
        for(int neighborVertex : neighbourList[currentVertex]){
            if(!visitedArray[neighborVertex]){
                visitedArray[neighborVertex] = true;
                parentArray[neighborVertex] = currentVertex;
                queueArray.push_back(neighborVertex);
            }
        }
    }

    for (int i = 1; i <= 2 * N; ++i) {
        if (i == rootVertex) continue;
        
        int childLiteral = getLiteral(i);
        int parentLiteral = getLiteral(parentArray[i]);
        
        solverInstance.addImplication(childLiteral, parentLiteral);
    }

    if (solverInstance.solve()) {
        cout << "TAK" << endl;
        for (int i = 1; i <= 2 * N; ++i) {
            int C = vertexToColor[i].colorIndex;
            int T = vertexToColor[i].typeVariant;
            
            if (solverInstance.assignmentResult[C] != T) {
                cout << 1;
            } else {
                cout << 0;
            }
            cout << (i == 2 * N ? "" : " ");
        }
        cout << endl;
        return true;
    }

    return false;
}

void solveTestCase() {
    cin >> N;

    neighbourList.assign(2 * N + 1, vector<int>());
    colorPairs.resize(N);
    vertexToColor.resize(2 * N + 1);

    for (int i = 0; i < 2 * N - 1; ++i) {
        int U, V;
        cin >> U >> V;
        neighbourList[U].push_back(V);
        neighbourList[V].push_back(U);
    }

    for (int i = 0; i < N; ++i) {
        int U, V;
        cin >> U >> V;
        colorPairs[i] = {U, V};
        vertexToColor[U] = {i, 0};
        vertexToColor[V] = {i, 1};
    }

    if (attemptRooting(colorPairs[0].first)) return;
    if (attemptRooting(colorPairs[0].second)) return;

    cout << "NIE" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& O, auto P) -> decltype(P.first, O) {
    return O << '(' << P.first << ", " << P.second << ')';
}
auto operator<<(auto& O, auto X) -> decltype(X.end(), O) {
    O << '{';
    int i = 2;
    for (auto E : X) O << (", ") + i << E, i = 0;
    return O << '}';
}
#define LOG(X...) cerr << "[" #X "]: ", [](auto... Args){ ((cerr << Args << "; "), ...) << endl; }(X);
#else
#define LOG(X...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 2e18;
const int MAX_NODES = 205;

int trieNodes[MAX_NODES][26];
int failureLink[MAX_NODES];
ll nodeGain[MAX_NODES];
int nodesCount = 1;

struct Matrix {
    ll matrixData[MAX_NODES][MAX_NODES];
    int matrixDimension;

    Matrix(int dimensionSize) : matrixDimension(dimensionSize) {
        for (int i = 0; i < matrixDimension; ++i)
            for (int j = 0; j < matrixDimension; ++j)
                matrixData[i][j] = -INF;
    }

    static Matrix identity(int dimensionSize) {
        Matrix resultMatrix(dimensionSize);
        for (int i = 0; i < dimensionSize; ++i) resultMatrix.matrixData[i][i] = 0;
        return resultMatrix;
    }
};

Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix resultMatrix(A.matrixDimension);
    for (int i = 0; i < A.matrixDimension; ++i) {
        for (int k = 0; k < A.matrixDimension; ++k) {
            if (A.matrixData[i][k] == -INF) continue;
            for (int j = 0; j < A.matrixDimension; ++j) {
                if (B.matrixData[k][j] == -INF) continue;
                if (A.matrixData[i][k] + B.matrixData[k][j] > resultMatrix.matrixData[i][j]) {
                    resultMatrix.matrixData[i][j] = A.matrixData[i][k] + B.matrixData[k][j];
                }
            }
        }
    }
    return resultMatrix;
}

Matrix power(Matrix A, ll P) {
    Matrix resultMatrix = Matrix::identity(A.matrixDimension);
    while (P > 0) {
        if (P & 1) resultMatrix = multiply(resultMatrix, A);
        A = multiply(A, A);
        P >>= 1;
    }
    return resultMatrix;
}

void insertPattern(const string& patternString, int happinessValue) {
    int currentNode = 0;
    for (char c : patternString) {
        int charIndex = c - 'a';
        if (!trieNodes[currentNode][charIndex]) {
            trieNodes[currentNode][charIndex] = nodesCount++;
        }
        currentNode = trieNodes[currentNode][charIndex];
    }
    nodeGain[currentNode] += happinessValue;
}

void buildAC() {
    queue<int> bfsQueue;
    for (int i = 0; i < 26; ++i) {
        if (trieNodes[0][i]) {
            bfsQueue.push(trieNodes[0][i]);
        }
    }
    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();
        nodeGain[currentNode] += nodeGain[failureLink[currentNode]];

        for (int i = 0; i < 26; ++i) {
            if (trieNodes[currentNode][i]) {
                failureLink[trieNodes[currentNode][i]] = trieNodes[failureLink[currentNode]][i];
                bfsQueue.push(trieNodes[currentNode][i]);
            } else {
                trieNodes[currentNode][i] = trieNodes[failureLink[currentNode]][i];
            }
        }
    }
}

void solveTestCase() {
    int N;
    ll L;
    if (!(cin >> N >> L)) return;

    vector<int> happinessValues(N);
    for (int i = 0; i < N; ++i) cin >> happinessValues[i];
    vector<string> patternStrings(N);
    for (int i = 0; i < N; ++i) cin >> patternStrings[i];

    memset(trieNodes, 0, sizeof(trieNodes));
    memset(failureLink, 0, sizeof(failureLink));
    memset(nodeGain, 0, sizeof(nodeGain));
    nodesCount = 1;

    for (int i = 0; i < N; ++i) {
        insertPattern(patternStrings[i], happinessValues[i]);
    }

    buildAC();

    Matrix transitionMatrix(nodesCount);
    for (int u = 0; u < nodesCount; ++u) {
        for (int c = 0; c < 26; ++c) {
            int nextNode = trieNodes[u][c];
            if (nodeGain[nextNode] > transitionMatrix.matrixData[u][nextNode]) {
                transitionMatrix.matrixData[u][nextNode] = nodeGain[nextNode];
            }
        }
    }

    Matrix finalMatrix = power(transitionMatrix, L);

    ll maxHappiness = 0;
    for (int i = 0; i < nodesCount; ++i) {
        if (finalMatrix.matrixData[0][i] > maxHappiness) {
            maxHappiness = finalMatrix.matrixData[0][i];
        }
    }
    cout << maxHappiness << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
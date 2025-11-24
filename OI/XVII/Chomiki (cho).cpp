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

struct Matrix {
    int N;
    vector<vector<ll>> values;

    Matrix(int S) : N(S), values(S, vector<ll>(S, INF)) {}

    static Matrix identity(int S) {
        Matrix resultMatrix(S);
        for (int i = 0; i < S; ++i) {
            resultMatrix.values[i][i] = 0;
        }
        return resultMatrix;
    }
};

Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    Matrix C(A.N);
    for (int i = 0; i < A.N; ++i) {
        for (int k = 0; k < A.N; ++k) {
            if (A.values[i][k] == INF) continue;
            for (int j = 0; j < A.N; ++j) {
                if (B.values[k][j] != INF) {
                    C.values[i][j] = min(C.values[i][j], A.values[i][k] + B.values[k][j]);
                }
            }
        }
    }
    return C;
}

vector<int> computePrefixTable(const string& P) {
    int M = (int)P.length();
    vector<int> prefixTable(M);
    for (int i = 1, j = 0; i < M; i++) {
        while (j > 0 && P[i] != P[j])
            j = prefixTable[j - 1];
        if (P[i] == P[j])
            j++;
        prefixTable[i] = j;
    }
    return prefixTable;
}

void solveTestCase() {
    int N;
    ll M;
    cin >> N >> M;

    vector<string> hamsterNames(N);
    for (int i = 0; i < N; ++i) {
        cin >> hamsterNames[i];
    }

    Matrix transitionMatrix(N);

    for (int j = 0; j < N; ++j) {
        vector<int> prefixTable = computePrefixTable(hamsterNames[j]);

        for (int i = 0; i < N; ++i) {
            int overlapLength = 0;
            if (i == j) {
                overlapLength = prefixTable.back();
            } else {
                int currentMatch = 0;
                for (char c : hamsterNames[i]) {
                    while (currentMatch > 0 && c != hamsterNames[j][currentMatch])
                        currentMatch = prefixTable[currentMatch - 1];
                    if (c == hamsterNames[j][currentMatch])
                        currentMatch++;
                }
                overlapLength = currentMatch;
            }
            transitionMatrix.values[i][j] = (ll)hamsterNames[j].length() - overlapLength;
        }
    }

    ll exponent = M - 1;
    Matrix resultMatrix = Matrix::identity(N);
    Matrix baseMatrix = transitionMatrix;

    while (exponent > 0) {
        if (exponent & 1) {
            resultMatrix = multiplyMatrices(resultMatrix, baseMatrix);
        }
        baseMatrix = multiplyMatrices(baseMatrix, baseMatrix);
        exponent >>= 1;
    }

    ll finalAnswers = INF;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (resultMatrix.values[i][j] != INF) {
                finalAnswers = min(finalAnswers, (ll)hamsterNames[i].length() + resultMatrix.values[i][j]);
            }
        }
    }

    cout << finalAnswers << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
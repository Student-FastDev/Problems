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

static const int MAX_Q = 200000 + 5;
static const int LOG  = 18; // 2^18 = 262144 > 200k

int parentLifting[MAX_Q][LOG];
char charAtNode[MAX_Q];
int  depthNode[MAX_Q];
int  wordPtr[MAX_Q];

uint64_t hashVal[MAX_Q], powP[MAX_Q];
static const uint64_t P = 91138233;

int getKthAncestor(int V, int k) {
    for (int b = 0; b < LOG; b++) {
        if (k & (1 << b)) {
            V = parentLifting[V][b];
        }
    }
    return V;
}

int LCA(int U, int V) {
    if (depthNode[U] < depthNode[V]) swap(U, V);
    int depthDifference = depthNode[U] - depthNode[V];
    U = getKthAncestor(U, depthDifference);
    if (U == V) return U;
    for (int b = LOG - 1; b >= 0; b--) {
        if (parentLifting[U][b] != parentLifting[V][b]) {
            U = parentLifting[U][b];
            V = parentLifting[V][b];
        }
    }
    return parentLifting[U][0];
}

void solveTestCase() {
    powP[0] = 1;
    for (int i = 1; i < MAX_Q; i++) {
        powP[i] = powP[i-1] * P;
    }

    int N;
    cin >> N;

    int nodeCount = 1;
    int wordCount = 1;
    wordPtr[1]    = 1;
    depthNode[1]  = 0;
    hashVal[1]    = 0;
    for (int b = 0; b < LOG; b++) {
        parentLifting[1][b] = 1;
    }

    while (N--) {
        int operationType;
        cin >> operationType;
        if (operationType == 1) {
            int A; char C;
            cin >> A >> C;
            int wordBase = wordPtr[A];
            ++nodeCount;
            depthNode[nodeCount]  = depthNode[wordBase] + 1;
            charAtNode[nodeCount] = C;
            parentLifting[nodeCount][0] = wordBase;
            for (int b = 1; b < LOG; b++) {
                parentLifting[nodeCount][b] =
                    parentLifting[parentLifting[nodeCount][b-1]][b-1];
            }
            hashVal[nodeCount] = hashVal[wordBase] * P + (uint64_t)(C - 'a' + 1);
            wordPtr[A] = nodeCount;
        }
        else if (operationType == 2) {
            int A;
            cin >> A;
            ++wordCount;
            wordPtr[wordCount] = wordPtr[A];
        }
        else {
            int A, B;
            cin >> A >> B;
            int U = wordPtr[A];
            int V = wordPtr[B];
            int W = LCA(U, V);

            int dU = depthNode[U];
            int dV = depthNode[V];
            int dW = depthNode[W];

            int lenU = dU - dW;
            int lenV = dV - dW;
            int commonLenght = min(lenU, lenV);

            int lowValue = 0, highValue = commonLenght;
            while (lowValue < highValue) {
                int middleValue = (lowValue + highValue + 1) >> 1;
                int nU = getKthAncestor(U, dU - (dW + middleValue));
                int nV = getKthAncestor(V, dV - (dW + middleValue));
                if (hashVal[nU] == hashVal[nV]) {
                    lowValue = middleValue;
                } else {
                    highValue = middleValue - 1;
                }
            }

            if (lowValue == commonLenght) {
                if (lenU == lenV) {
                    cout << "=" << endl;
                } else if (lenU < lenV) {
                    cout << "<" << endl;
                } else {
                    cout << ">" << endl;
                }
            } else {
                int nU = getKthAncestor(U, dU - (dW + lowValue + 1));
                int nV = getKthAncestor(V, dV - (dW + lowValue + 1));
                char cU = charAtNode[nU];
                char cV = charAtNode[nV];
                if (cU < cV) cout << "<" << endl;
                else          cout << ">" << endl;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

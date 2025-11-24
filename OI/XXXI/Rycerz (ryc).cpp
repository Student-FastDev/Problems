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

void solveTestCase() {
    int N, M, D, K;
    cin >> N >> M >> D >> K;

    vector<int> U(M), V(M);
    vector<vector<ll>> A(M, vector<ll>(K));
    for (int i = 0; i < M; ++i) {
        cin >> U[i] >> V[i];
        for (int j = 0; j < K; ++j) {
            cin >> A[i][j];
        }
    }

    vector<vector<pii>> neighbourArray(N + 1);
    for (int i = 0; i < M; ++i) {
        neighbourArray[U[i]].emplace_back(V[i], i);
        neighbourArray[V[i]].emplace_back(U[i], i);
    }

    const int INF_INT = 2000000000;
    const int MAX_MASK_SIZE = 1 << 10;

    vector<int> edgeBit(M, 0);
    int currentBits = 0;

    vector<ll> finalAnswer(K);

    vector<vector<int>> distanceFW(N + 1, vector<int>(MAX_MASK_SIZE, INF_INT));
    vector<vector<int>> distanceBW(N + 1, vector<int>(MAX_MASK_SIZE, INF_INT));

    vector<vector<int>> minimumPrefix(N + 1, vector<int>(MAX_MASK_SIZE, INF_INT));
    vector<vector<int>> minimumSuffix(N + 1, vector<int>(MAX_MASK_SIZE, INF_INT));

    for (int type = 0; type < K; ++type) {
        int currentMaskSize = 1 << currentBits;

        fill(all(distanceFW), vector<int>(currentMaskSize, INF_INT));
        queue<pair<int, int>> q;
        distanceFW[1][0] = 0;
        q.emplace(1, 0);
        while (!q.empty()) {
            auto [x, mask] = q.front();
            q.pop();
            for (auto [y, id] : neighbourArray[x]) {
                int newMask = mask | edgeBit[id];
                if (distanceFW[y][newMask] == INF_INT) {
                    distanceFW[y][newMask] = distanceFW[x][mask] + 1;
                    q.emplace(y, newMask);
                }
            }
        }

        fill(all(distanceBW), vector<int>(currentMaskSize, INF_INT));
        distanceBW[N][0] = 0;
        q.emplace(N, 0);
        while (!q.empty()) {
            auto [x, mask] = q.front();
            q.pop();
            for (auto [y, id] : neighbourArray[x]) {
                int newMask = mask | edgeBit[id];
                if (distanceBW[y][newMask] == INF_INT) {
                    distanceBW[y][newMask] = distanceBW[x][mask] + 1;
                    q.emplace(y, newMask);
                }
            }
        }

        for (int x = 1; x <= N; ++x) {
            vector<int> temporaryArray(currentMaskSize);
            for (int s = 0; s < currentMaskSize; ++s) {
                temporaryArray[s] = distanceFW[x][s];
            }
            for (int b = 0; b < currentBits; ++b) {
                for (int s = 0; s < currentMaskSize; ++s) {
                    if ((s & (1 << b)) == 0) {
                        temporaryArray[s] = min(temporaryArray[s], temporaryArray[s | (1 << b)]);
                    }
                }
            }
            for (int s = 0; s < currentMaskSize; ++s) {
                minimumPrefix[x][s] = temporaryArray[s];
            }

            for (int s = 0; s < currentMaskSize; ++s) {
                temporaryArray[s] = distanceBW[x][s];
            }
            for (int b = 0; b < currentBits; ++b) {
                for (int s = 0; s < currentMaskSize; ++s) {
                    if ((s & (1 << b)) == 0) {
                        temporaryArray[s] = min(temporaryArray[s], temporaryArray[s | (1 << b)]);
                    }
                }
            }
            for (int s = 0; s < currentMaskSize; ++s) {
                minimumSuffix[x][s] = temporaryArray[s];
            }
        }

        ll maxValue = 0;
        vector<int> goodEdges;
        int fullMask = (1 << currentBits) - 1;
        
        for (int i = 0; i < M; ++i) {
            int minimumLength = INF_INT;
            for (int direction = 0; direction < 2; ++direction) {
                int start = direction == 0 ? U[i] : V[i];
                int end = direction == 0 ? V[i] : U[i];
                int bit = edgeBit[i];
                int missing = fullMask & ~bit;
                int candidate = INF_INT;
                for (int maskP = 0; maskP < currentMaskSize; ++maskP) {
                    if (distanceFW[start][maskP] >= INF_INT / 2) continue;
                    int required = missing & ~maskP;
                    int suffix = minimumSuffix[end][required];
                    if (suffix >= INF_INT / 2) continue;
                    candidate = min(candidate, distanceFW[start][maskP] + 1 + suffix);
                }
                minimumLength = min(minimumLength, candidate);
            }
            if (minimumLength <= D) {
                maxValue = max(maxValue, A[i][type]);
            }
        }
        finalAnswer[type] = maxValue;

        for (int i = 0; i < M; ++i) {
            int minimumLength = INF_INT;
            for (int direction = 0; direction < 2; ++direction) {
                int start = direction == 0 ? U[i] : V[i];
                int end = direction == 0 ? V[i] : U[i];
                int bit = edgeBit[i];
                int missing = fullMask & ~bit;
                int candidate = INF_INT;
                for (int maskP = 0; maskP < currentMaskSize; ++maskP) {
                    if (distanceFW[start][maskP] >= INF_INT / 2) continue;
                    int required = missing & ~maskP;
                    int suffix = minimumSuffix[end][required];
                    if (suffix >= INF_INT / 2) continue;
                    candidate = min(candidate, distanceFW[start][maskP] + 1 + suffix);
                }
                minimumLength = min(minimumLength, candidate);
            }
            if (minimumLength <= D && A[i][type] == maxValue) {
                goodEdges.push_back(i);
            }
        }

        int newBit = currentBits;
        currentBits++;
        for (int id : goodEdges) {
            edgeBit[id] |= (1 << newBit);
        }
    }

    for (int i = 0; i < K; ++i) {
        if (i > 0) cout << " ";
        cout << finalAnswer[i];
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
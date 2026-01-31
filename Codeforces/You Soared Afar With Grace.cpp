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

int N;
vector<int> A, C;
vector<int> positionInA;
vector<pii> operationsList;

void applyOperation(int u, int v) {
    if (u == v) return;
    int valueU = A[u];
    int valueV = A[v];
    swap(A[u], A[v]);
    positionInA[valueU] = v;
    positionInA[valueV] = u;

    int uPrime = N - 1 - u;
    int vPrime = N - 1 - v;
    swap(C[uPrime], C[vPrime]);
    
    operationsList.push_back({u + 1, v + 1});
}

void solveTestCase() {
    cin >> N;
    A.resize(N);
    C.resize(N); 
    positionInA.resize(N + 1);
    
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        positionInA[A[i]] = i;
    }
    vector<int> B(N);
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }
    for (int i = 0; i < N; ++i) {
        C[i] = B[N - 1 - i];
    }

    operationsList.clear();
    bool isPossible = true;

    auto performSwapSimulation = [&](int u, int v) {
        swap(A[u], A[v]);
        int uPrime = N - 1 - u;
        int vPrime = N - 1 - v;
        swap(C[uPrime], C[vPrime]);
    };

    for (int i = 0; i < N / 2; ++i) {
        int L = i;
        int R = N - 1 - i;

        if (A[L] == C[L] && A[R] == C[R]) continue;
        
        auto getCandidates = [&]() {
            vector<int> candidates;
            candidates.push_back(L);
            candidates.push_back(R);
            candidates.push_back(positionInA[C[L]]);
            candidates.push_back(positionInA[C[R]]);
            for (int k = L + 1; k < R; ++k) {
                bool used = false;
                for(int x : candidates) if(x == k) used = true;
                if(!used) {
                    candidates.push_back(k);
                    break; 
                }
            }
            vector<int> validCandidates;
            for(int x : candidates) {
                if (x >= L && x <= R) validCandidates.push_back(x);
            }
            sort(all(validCandidates));
            validCandidates.erase(unique(all(validCandidates)), validCandidates.end());
            return validCandidates;
        };

        vector<int> nodes = getCandidates();
        vector<pair<int, int>> potentialMoves;
        for (int x : nodes) {
            if (x != L) potentialMoves.push_back({L, x});
        }
        for (int x : nodes) {
            if (x != R && x != L) potentialMoves.push_back({R, x});
        }

        bool foundSolution = false;
        pii solutionMove1 = {-1, -1}, solutionMove2 = {-1, -1};

        for (auto& p : potentialMoves) {
            performSwapSimulation(p.first, p.second);
            if (A[L] == C[L] && A[R] == C[R]) {
                foundSolution = true;
                solutionMove1 = p;
            }
            performSwapSimulation(p.first, p.second); 
            if (foundSolution) break;
        }

        if (!foundSolution) {
            for (auto& p1 : potentialMoves) {
                performSwapSimulation(p1.first, p1.second);
                for (auto& p2 : potentialMoves) {
                    performSwapSimulation(p2.first, p2.second);
                    if (A[L] == C[L] && A[R] == C[R]) {
                        foundSolution = true;
                        solutionMove1 = p1;
                        solutionMove2 = p2;
                    }
                    performSwapSimulation(p2.first, p2.second); 
                    if (foundSolution) break;
                }
                performSwapSimulation(p1.first, p1.second); 
                if (foundSolution) break;
            }
        }

        if (!foundSolution) {
            isPossible = false;
            break;
        }

        applyOperation(solutionMove1.first, solutionMove1.second);
        if (solutionMove2.first != -1) {
            applyOperation(solutionMove2.first, solutionMove2.second);
        }
    }

    if (isPossible) {
        if (N % 2 == 1) {
            int middleIndex = N / 2;
            if (A[middleIndex] != C[middleIndex]) isPossible = false;
        }
    }

    if (isPossible) {
        cout << size(operationsList) << endl;
        for(auto& p : operationsList) cout << p.first << " " << p.second << endl;
    } else {
        cout << -1 << endl;
    }
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
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
const ll MOD = 998244353; // 998244353

ll binomialCoeffs[60][60];

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

ll modInverse(ll n) {
    return power(n, MOD - 2);
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<ll> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    vector<ll> basisList;
    for(ll x : A) {
        for(ll basisElement : basisList) x = min(x, x ^ basisElement);
        if(x > 0) {
            basisList.push_back(x);
            sort(all(basisList), greater<ll>());
        }
    }

    int basisDimension = size(basisList);
    vector<ll> answerArray(M + 1, 0);

    if (basisDimension <= 26) {
        vector<int> countArray(M + 1, 0);
        ll currentXor = 0;
        countArray[0]++;
        int totalSubsetCount = 1 << basisDimension;
        for(int i = 1; i < totalSubsetCount; ++i) {
            int bitIndex = __builtin_ctz(i);
            currentXor ^= basisList[bitIndex];
            countArray[__builtin_popcountll(currentXor)]++;
        }

        ll scaleFactor = power(2, N - basisDimension);
        for(int i = 0; i <= M; ++i) {
            answerArray[i] = (countArray[i] % MOD * scaleFactor) % MOD;
        }
    } else {
        vector<ll> basisMatrix = basisList;
        vector<int> columnMap(M);
        iota(all(columnMap), 0);

        for(int r = 0; r < basisDimension; ++r) {
            int pivotColumn = -1;
            bool foundPivot = false;
            for(int c = r; c < M; ++c) {
                for(int k = r; k < basisDimension; ++k) {
                    if ((basisMatrix[k] >> columnMap[c]) & 1) {
                        pivotColumn = c;
                        swap(basisMatrix[r], basisMatrix[k]);
                        foundPivot = true;
                        break;
                    }
                }
                if (foundPivot) break;
            }
            
            swap(columnMap[r], columnMap[pivotColumn]);

            for(int k = 0; k < basisDimension; ++k) {
                if (k != r && ((basisMatrix[k] >> columnMap[r]) & 1)) {
                    basisMatrix[k] ^= basisMatrix[r];
                }
            }
        }

        vector<ll> dualBasisList;
        for(int j = 0; j < M - basisDimension; ++j) {
            ll vectorMask = 0;
            int identityColumn = columnMap[basisDimension + j];
            vectorMask |= (1LL << identityColumn);
            for(int i = 0; i < basisDimension; ++i) {
                if ((basisMatrix[i] >> identityColumn) & 1) {
                    int pivotColumn = columnMap[i];
                    vectorMask |= (1LL << pivotColumn);
                }
            }
            dualBasisList.push_back(vectorMask);
        }

        int dualDimension = M - basisDimension;
        vector<ll> dualCountArray(M + 1, 0);
        ll currentXor = 0;
        dualCountArray[0]++;
        int totalDualSubsets = 1 << dualDimension;
        for(int i = 1; i < totalDualSubsets; ++i) {
            int bitIndex = __builtin_ctz(i);
            currentXor ^= dualBasisList[bitIndex];
            dualCountArray[__builtin_popcountll(currentXor)]++;
        }

        for(int j = 0; j <= M; ++j) {
            if (dualCountArray[j] == 0) continue;
            for(int k = 0; k <= M; ++k) {
                ll termCoefficient = 0;
                int minOverlap = max(0, k - (M - j));
                int maxOverlap = min(k, j);
                for(int p = minOverlap; p <= maxOverlap; ++p) {
                    ll val = (binomialCoeffs[M-j][k-p] * binomialCoeffs[j][p]) % MOD;
                    if (p % 2 == 1) termCoefficient = (termCoefficient - val + MOD) % MOD;
                    else termCoefficient = (termCoefficient + val) % MOD;
                }
                ll contribution = (dualCountArray[j] % MOD * termCoefficient) % MOD;
                answerArray[k] = (answerArray[k] + contribution) % MOD;
            }
        }

        ll scaleFactor;
        if (N >= M) scaleFactor = power(2, N - M);
        else scaleFactor = modInverse(power(2, M - N));
        
        for(int k = 0; k <= M; ++k) {
            answerArray[k] = (answerArray[k] * scaleFactor) % MOD;
        }
    }

    for(int i = 0; i <= M; ++i) cout << answerArray[i] << (i == M ? "" : " ");
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    for (int i = 0; i < 60; ++i) {
        binomialCoeffs[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            binomialCoeffs[i][j] = (binomialCoeffs[i-1][j-1] + binomialCoeffs[i-1][j]) % MOD;
        }
    }

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}
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
vector<ll> valuesArray;
vector<bool> isUsed;
ll magicSquare[4][4];
ll rowSums[4], colSums[4], mainDiagSum, secDiagSum;
ll targetSum;
bool solutionFound;

bool isValidPartial(int r, int c, ll val) {
    int remainingInRow = (N - 1) - c;
    if (remainingInRow > 0) {
        ll currentSum = rowSums[r] + val;
        ll needed = targetSum - currentSum;
        ll minSum = 0, maxSum = 0;
        int count = 0;
        for (int i = 0; i < size(valuesArray) && count < remainingInRow; ++i) {
            if (!isUsed[i]) { minSum += valuesArray[i]; count++; }
        }
        if (needed < minSum) return false;
        
        count = 0;
        for (int i = (int)size(valuesArray) - 1; i >= 0 && count < remainingInRow; --i) {
            if (!isUsed[i]) { maxSum += valuesArray[i]; count++; }
        }
        if (needed > maxSum) return false;
    }

    int remainingInCol = (N - 1) - r;
    if (remainingInCol > 0) {
        ll currentSum = colSums[c] + val;
        ll needed = targetSum - currentSum;
        ll minSum = 0, maxSum = 0;
        int count = 0;
        for (int i = 0; i < size(valuesArray) && count < remainingInCol; ++i) {
            if (!isUsed[i]) { minSum += valuesArray[i]; count++; }
        }
        if (needed < minSum) return false;
        
        count = 0;
        for (int i = (int)size(valuesArray) - 1; i >= 0 && count < remainingInCol; --i) {
            if (!isUsed[i]) { maxSum += valuesArray[i]; count++; }
        }
        if (needed > maxSum) return false;
    }
    return true;
}

void solveMagicSquare(int cellIndex) {
    if (solutionFound) return;
    if (cellIndex == N * N) {
        solutionFound = true;
        return;
    }

    int r = cellIndex / N;
    int c = cellIndex % N;

    bool isForced = false;
    ll valNeeded = 0;

    if (c == N - 1) {
        isForced = true;
        valNeeded = targetSum - rowSums[r];
    } else if (r == N - 1) {
        isForced = true;
        valNeeded = targetSum - colSums[c];
    }

    if (isForced) {
        auto iterator = lower_bound(all(valuesArray), valNeeded);
        while (iterator != valuesArray.end() && *iterator == valNeeded) {
            int k = (int)(iterator - valuesArray.begin());
            if (!isUsed[k]) {
                bool isConsistent = true;
                if (c == N - 1 && r == N - 1) {
                    if (colSums[c] + valNeeded != targetSum) isConsistent = false;
                    if (mainDiagSum + valNeeded != targetSum) isConsistent = false;
                }
                if (r == N - 1 && c == 0) {
                    if (secDiagSum + valNeeded != targetSum) isConsistent = false;
                }

                if (isConsistent) {
                    if (isValidPartial(r, c, valNeeded)) {
                        isUsed[k] = true;
                        magicSquare[r][c] = valNeeded;
                        rowSums[r] += valNeeded;
                        colSums[c] += valNeeded;
                        if (r == c) mainDiagSum += valNeeded;
                        if (r + c == N - 1) secDiagSum += valNeeded;

                        solveMagicSquare(cellIndex + 1);
                        if (solutionFound) return;

                        if (r + c == N - 1) secDiagSum -= valNeeded;
                        if (r == c) mainDiagSum -= valNeeded;
                        colSums[c] -= valNeeded;
                        rowSums[r] -= valNeeded;
                        isUsed[k] = false;
                    }
                }
                break; 
            }
            iterator++;
        }
    } else {
        for (int k = 0; k < size(valuesArray); ++k) {
            if (isUsed[k]) continue;
            if (k > 0 && valuesArray[k] == valuesArray[k - 1] && !isUsed[k - 1]) continue;

            ll val = valuesArray[k];
            if (isValidPartial(r, c, val)) {
                isUsed[k] = true;
                magicSquare[r][c] = val;
                rowSums[r] += val;
                colSums[c] += val;
                if (r == c) mainDiagSum += val;
                if (r + c == N - 1) secDiagSum += val;

                solveMagicSquare(cellIndex + 1);
                if (solutionFound) return;

                if (r + c == N - 1) secDiagSum -= val;
                if (r == c) mainDiagSum -= val;
                colSums[c] -= val;
                rowSums[r] -= val;
                isUsed[k] = false;
            }
        }
    }
}

void solveTestCase() {
    cin >> N;
    valuesArray.resize(N * N);
    ll sumTotal = 0;
    for (int i = 0; i < N * N; ++i) {
        cin >> valuesArray[i];
        sumTotal += valuesArray[i];
    }
    sort(all(valuesArray));
    targetSum = sumTotal / N;

    cout << targetSum << endl;

    fill(rowSums, rowSums + 4, 0);
    fill(colSums, colSums + 4, 0);
    mainDiagSum = 0;
    secDiagSum = 0;
    isUsed.assign(N * N, false);
    solutionFound = false;

    solveMagicSquare(0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << magicSquare[i][j] << (j == N - 1 ? "" : " ");
        }
        cout << endl;
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
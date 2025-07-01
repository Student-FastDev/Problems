// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto E:x)o<<(", ")+i<<E,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",{((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define all(x)  x.size() 

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

int N, M, K;
vector<int> studentArrays;
vector<vector<int>> F;

void smawkRecursive(const vector<int>& rowsArray, const vector<int>& columnsArray, const auto& kernelFunction, vector<int>& argumentMax); 

vector<int> runSMAWK(int n, int m, const auto& kernelFunction) {
    vector<int> rowsArray(n);
    iota(rowsArray.begin(), rowsArray.end(), 0);
    vector<int> columnsArray(m);
    iota(columnsArray.begin(), columnsArray.end(), 0);
    vector<int> argumentMax(n);
    smawkRecursive(rowsArray, columnsArray, kernelFunction, argumentMax);
    return argumentMax;
}

void smawkRecursive(const vector<int>& rowsArray, const vector<int>& columnsArray, const auto& kernelFunction, vector<int>& argumentMax) {
    if (rowsArray.empty()) return;

    vector<int> reducedCols;
    for (int j : columnsArray) {
        while (!reducedCols.empty() &&
               kernelFunction(rowsArray[size(reducedCols) - 1], reducedCols.back()) < kernelFunction(rowsArray[size(reducedCols) - 1], j)) {
            reducedCols.pop_back();
        }
        if (size(reducedCols) < size(rowsArray)) {
            reducedCols.push_back(j);
        }
    }

    vector<int> oddRows;
    for (size_t i = 1; i < size(rowsArray); i += 2) {
        oddRows.push_back(rowsArray[i]);
    }
    smawkRecursive(oddRows, reducedCols, kernelFunction, argumentMax);

    for (size_t i = 0; i < size(rowsArray); i += 2) {
        int R = rowsArray[i];

        int startC = (i == 0) ? reducedCols.front() : argumentMax[rowsArray[i - 1]];
        int endC = (i == size(rowsArray) - 1) ? reducedCols.back() : argumentMax[rowsArray[i + 1]];

        auto itStart = lower_bound(reducedCols.begin(), reducedCols.end(), startC);
        auto itEnd = upper_bound(reducedCols.begin(), reducedCols.end(), endC);

        int bestC = *itStart;
        int bestValue = kernelFunction(R, bestC);

        for (auto it = next(itStart); it != itEnd; ++it) {
            int C = *it;
            int currentValue = kernelFunction(R, C);
            if (currentValue > bestValue) {
                bestValue = currentValue;
                bestC = C;
            }
        }
        argumentMax[R] = bestC;
    }
}

void maxPlusConvolution(const vector<int>& A, const vector<int>& B, vector<int>& C, const vector<vector<int>>& precomputedTable, int valueN) {
    (void) B;

    int sizeK = size(A);
    auto kernelFunction = [&](int i, int j) {
        if (j > i) {
            return -1;
        }
        int S = A[j];
        int D = i - j;
        if (S == valueN) {
            return valueN;
        }
        return precomputedTable[S][D];
    };

    vector<int> argumentMaximum = runSMAWK(sizeK, sizeK, kernelFunction);

    C.resize(sizeK);
    for (int i = 0; i < sizeK; ++i) {
        C[i] = kernelFunction(i, argumentMaximum[i]);
    }
}


bool isPossible(int R) {
    vector<int> DP(K + 1);
    for (int k = 0; k <= K; ++k) DP[k] = min(k, N);
    if (N == 0) return true;

    vector<int> B(K + 1);
    iota(B.begin(), B.end(), 0);

    for (int p = 0; p < R; ++p) {
        vector<int> convolutionArray;
        maxPlusConvolution(DP, B, convolutionArray, F, N);

        bool hasFinished = false;
        for (int t = 0; t <= K; ++t) {
            int V = (t < size(convolutionArray) ? convolutionArray[t] : -1);
            if (V < 0) V = 0;
            DP[t] = min(V, N);
            if (DP[t] == N) {
                hasFinished = true;
                break;
            }
        }
        if (hasFinished) return true;
    }
    return false;
}

void preprocessTable() {
    F.assign(N + 1, vector<int>(K + 1, 0));
    for (int D = 0; D <= K; ++D) {
        vector<int> frequenceArray(N, 0);
        int wrongCounter = 0, E = 0;
        for (int S = 0; S <= N; ++S) {
            while (E < N) {
                int currentValue = studentArrays[E];
                int oldFrequence = frequenceArray[currentValue];
                int newWrong = wrongCounter - max(0, oldFrequence - M) + max(0, oldFrequence + 1 - M);
                if (newWrong > D) break;
                frequenceArray[currentValue]++;
                wrongCounter = newWrong;
                E++;
            }
            F[S][D] = E;
            if (S < N) {
                int currentValue = studentArrays[S];
                int oldFrequence = frequenceArray[currentValue];
                if (oldFrequence > 0) {
                    int newWrong = wrongCounter - max(0, oldFrequence - M) + max(0, oldFrequence - 1 - M);
                    frequenceArray[currentValue]--;
                    wrongCounter = newWrong;
                }
            }
        }
    }
}

void solveTestCase() {
    cin >> N >> M >> K;
    studentArrays.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> studentArrays[i];
        --studentArrays[i];
    }

    if (K >= N) {
        cout << 0 << endl;
        return;
    }

    if (M == 1) {
        vector<int> frequencyHelper(N, 0), wasSeen;
        int currentPosition = 0;
        int remainingStudents = K;
        int roomsNumber = 0;

        while (currentPosition < N) {
            ++roomsNumber;
            int usedNumber = 0;
            wasSeen.clear();

            int E = currentPosition;
            while (E < N) {
                int currentCity = studentArrays[E];
                if (frequencyHelper[currentCity] == 0) {
                    frequencyHelper[currentCity] = 1;
                    wasSeen.push_back(currentCity);
                    ++E;
                } else {
                    if (usedNumber == remainingStudents) break;
                    ++usedNumber;
                    ++E;
                }
            }

            remainingStudents -= usedNumber;
            for (int currentCity : wasSeen) {
                frequencyHelper[currentCity] = 0;
            }
            currentPosition = E;
        }

        cout << roomsNumber << endl;
        return;
    }

    preprocessTable();

    int leftRange = 1, rightRange = N, finalAnswer = N;
    while (leftRange <= rightRange) {
        int middleValue = (leftRange + rightRange) / 2;
        if (isPossible(middleValue)) {
            finalAnswer = middleValue;
            rightRange = middleValue - 1;
        } else {
            leftRange = middleValue + 1;
        }
    }

    cout << finalAnswer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}

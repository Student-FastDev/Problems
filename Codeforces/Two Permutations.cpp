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
const ll MOD = 1e9+7;

const int MAXM = 200005;

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<int> sequenceA(N);
    for (int i = 0; i < N; ++i) cin >> sequenceA[i];

    vector<int> sequenceB(M);
    vector<int> positionsInB(M + 1);
    for (int i = 0; i < M; ++i) {
        cin >> sequenceB[i];
        positionsInB[sequenceB[i]] = i;
    }

    if (M < N) {
        cout << 0 << endl;
        return;
    }

    map<int, vector<int>> differenceGroups;
    for (int i = 0; i < N - 1; ++i) {
        differenceGroups[sequenceA[i + 1] - sequenceA[i]].push_back(i);
    }

    ll bruteForceCost = (ll)N * (M - N + 1);
    ll bitsetCost = (ll)size(differenceGroups) * M + (ll)N * (M / 64);

    if (bruteForceCost < bitsetCost * 2) {
        int answerCount = 0;
        int maxShift = M - N;
        for (int shiftAmount = 0; shiftAmount <= maxShift; ++shiftAmount) {
            bool isValid = true;
            for (int i = 0; i < N - 1; ++i) {
                if (positionsInB[sequenceA[i] + shiftAmount] > positionsInB[sequenceA[i + 1] + shiftAmount]) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) answerCount++;
        }
        cout << answerCount << endl;
    } else {
        bitset<MAXM> invalidShifts;
        for (auto& [diffValue, indicesList] : differenceGroups) {
            vector<int> badValues;
            int minValue = 1, maxValue = M;
            if (diffValue > 0) maxValue = M - diffValue;
            else minValue = 1 - diffValue;

            for (int valueU = minValue; valueU <= maxValue; ++valueU) {
                if (positionsInB[valueU] > positionsInB[valueU + diffValue]) {
                    badValues.push_back(valueU);
                }
            }

            if (badValues.empty()) continue;

            if ((ll)size(badValues) * size(indicesList) < (ll)size(indicesList) * (M / 64) + size(badValues)) {
                for (int valueU : badValues) {
                    for (int i : indicesList) {
                        int shiftAmount = valueU - sequenceA[i];
                        if (shiftAmount >= 0 && shiftAmount <= M - N) {
                            invalidShifts[shiftAmount] = 1;
                        }
                    }
                }
            } else {
                bitset<MAXM> tempBitset;
                for (int valueU : badValues) tempBitset[valueU] = 1;
                for (int i : indicesList) {
                    invalidShifts |= (tempBitset >> sequenceA[i]);
                }
            }
        }

        int answerCount = 0;
        for (int shiftAmount = 0; shiftAmount <= M - N; ++shiftAmount) {
            if (!invalidShifts[shiftAmount]) answerCount++;
        }
        cout << answerCount << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int testCases = 1;

    while (testCases--) {
        solveTestCase();
    }
    return 0;
}
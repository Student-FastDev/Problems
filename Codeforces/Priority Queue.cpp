// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& o, auto p) -> decltype(p.first, o) {
    return o << '(' << p.first << ", " << p.second << ')';
}
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) {
    o << '{';
    int i = 2;
    for (auto e : x) o << (", ") + i << e, i = 0;
    return o << '}';
}
#define LOG(x...) cerr << "[" #x "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(x);
#else
#define LOG(x...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MOD = 998244353;

struct Operation {
    int operationType;
    ll operationValue;
};

void solveTestCase() {
    int N;
    if (!(cin >> N)) return;

    vector<Operation> operationsArray(N);
    for (int i = 0; i < N; ++i) {
        char typeCharacter;
        cin >> typeCharacter;
        if (typeCharacter == '+') {
            operationsArray[i].operationType = 1;
            cin >> operationsArray[i].operationValue;
        } else {
            operationsArray[i].operationType = 0;
            operationsArray[i].operationValue = 0;
        }
    }

    vector<ll> powersOfTwoArray(N + 1);
    powersOfTwoArray[0] = 1;
    for (int i = 1; i <= N; ++i) {
        powersOfTwoArray[i] = (powersOfTwoArray[i - 1] * 2) % MOD;
    }

    ll totalSum = 0;
    vector<ll> dynamicProgrammingArray(N + 2);

    for (int i = 0; i < N; ++i) {
        if (operationsArray[i].operationType == 0) continue;

        ll targetValue = operationsArray[i].operationValue;
        int largerCount = 0;

        fill(dynamicProgrammingArray.begin(), dynamicProgrammingArray.end(), 0);
        dynamicProgrammingArray[0] = 1;

        for (int j = 0; j < N; ++j) {
            if (i == j) {
                continue;
            }

            if (operationsArray[j].operationType == 1) {
                bool isSmaller = false;
                if (operationsArray[j].operationValue < targetValue) isSmaller = true;
                else if (operationsArray[j].operationValue == targetValue && j < i) isSmaller = true;

                if (isSmaller) {
                    for (int c = N; c >= 1; --c) {
                        dynamicProgrammingArray[c] = dynamicProgrammingArray[c] + dynamicProgrammingArray[c - 1];
                        if (dynamicProgrammingArray[c] >= MOD) dynamicProgrammingArray[c] -= MOD;
                    }
                } else {
                    largerCount++;
                }
            } else {
                if (j < i) {
                    ll dpZero = dynamicProgrammingArray[0];
                    ll dpOne = dynamicProgrammingArray[1];

                    ll newDpZero = (2 * dpZero + dpOne) % MOD;

                    for (int c = 1; c <= N; ++c) {
                        dynamicProgrammingArray[c] = dynamicProgrammingArray[c] + dynamicProgrammingArray[c + 1];
                        if (dynamicProgrammingArray[c] >= MOD) dynamicProgrammingArray[c] -= MOD;
                    }
                    dynamicProgrammingArray[0] = newDpZero;
                } else {
                    for (int c = 0; c <= N; ++c) {
                        dynamicProgrammingArray[c] = dynamicProgrammingArray[c] + dynamicProgrammingArray[c + 1];
                        if (dynamicProgrammingArray[c] >= MOD) dynamicProgrammingArray[c] -= MOD;
                    }
                }
            }
        }

        ll validWays = 0;
        for (int c = 0; c <= N; ++c) {
            validWays += dynamicProgrammingArray[c];
            if (validWays >= MOD) validWays -= MOD;
        }

        ll currentTerm = (validWays * powersOfTwoArray[largerCount]) % MOD;
        currentTerm = (currentTerm * targetValue) % MOD;
        totalSum = (totalSum + currentTerm) % MOD;
    }

    cout << totalSum << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    solveTestCase();

    return 0;
}
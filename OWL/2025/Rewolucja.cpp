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

char getChar(ll mask, int index) {
    return (char)((((1 << 4) - 1) & (mask >> 4 * index)) + 'a');
}

ll createConcatenation(ll current_mask, int len, char c) {
    return current_mask | ((ll)(c - 'a') << (4 * len));
}

struct State {
    struct SubState {
        int count = 0;
        ll bitMask = 0;
        int length = 0;
    };
    
    vector<SubState> values;
    int maxIndex = 0;

    State(int M) : values(M) {}
};

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;

    vector<State> DP(1 << M, State(M));

    for (int index = 0; index < N; index++) {
        int currentChar = S[index] - 'a';

        for (int mask = (1 << M) - 1; mask >= 0; mask--) {
            if ((mask >> currentChar) & 1) {
                DP[mask].values[currentChar].count++;

                if (DP[mask].values[DP[mask].maxIndex].count < DP[mask].values[currentChar].count) {
                    DP[mask].maxIndex = currentChar;
                }

                if (DP[mask].values[currentChar].length == 0) {
                    DP[mask].values[currentChar].bitMask = createConcatenation(0, 0, S[index]);
                    DP[mask].values[currentChar].length = 1;
                }
                continue;
            }

            auto &nextState = DP[mask | (1 << currentChar)];

            if (nextState.values[currentChar].count < DP[mask].values[DP[mask].maxIndex].count + 1) {
                nextState.values[currentChar].count = DP[mask].values[DP[mask].maxIndex].count + 1;

                if (nextState.values[currentChar].count > nextState.values[nextState.maxIndex].count)
                    nextState.maxIndex = currentChar;

                nextState.values[currentChar].bitMask = createConcatenation(
                    DP[mask].values[DP[mask].maxIndex].bitMask,
                    DP[mask].values[DP[mask].maxIndex].length,
                    S[index]
                );
                nextState.values[currentChar].length = DP[mask].values[DP[mask].maxIndex].length + 1;
            }
        }
    }

    int maxCount = -1, bestLength = -1;
    ll bestBitmask = -1;

    for (const auto &state : DP) {
        if (maxCount < state.values[state.maxIndex].count) {
            maxCount = state.values[state.maxIndex].count;
            bestBitmask = state.values[state.maxIndex].bitMask;
            bestLength = state.values[state.maxIndex].length;
        }
    }

    string optimalOrder;
    vector<bool> used(M, false);

    for (int i = 0; i < bestLength; i++) {
        char c = getChar(bestBitmask, i);
        optimalOrder.push_back(c);
        used[c - 'a'] = true;
    }

    for (int i = 0; i < M; i++) {
        if (!used[i])
            optimalOrder.push_back((char)('a' + i));
    }

    cout << maxCount << endl << optimalOrder << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solveTestCase();
    }
    return 0;
}

// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    int B = max(1, (int)sqrt(N));
    int blocksNumber = (N + B - 1) / B;
    vector<ll> addArray(blocksNumber, 0);
    vector<unordered_map<ll, int>> frequencyArray(blocksNumber);

    for (int i = 0; i < N; ++i) {
        int b = i / B;
        ++frequencyArray[b][A[i]];
    }

    while (Q--) {
        int C; cin >> C;
        int L, R; ll V;
        cin >> L >> R >> V;
        --L; --R;
        int blockLeft = L / B, blockRight = R / B;
        if (C == 1) {
            ll X = V;
            ll finalAnswer = 0;
            if (blockLeft == blockRight) {
                for (int i = L; i <= R; ++i)
                    if (A[i] + addArray[blockLeft] == X) ++finalAnswer;
            } else {
                int endLeftBlock = (blockLeft + 1) * B - 1;
                for (int i = L; i <= min(endLeftBlock, N - 1); ++i)
                    if (A[i] + addArray[blockLeft] == X) ++finalAnswer;
                int startBlockRight = blockRight * B;
                for (int i = startBlockRight; i <= R; ++i)
                    if (A[i] + addArray[blockRight] == X) ++finalAnswer;
                for (int b = blockLeft + 1; b <= blockRight - 1; ++b) {
                    ll needValue = X - addArray[b];
                    auto it = frequencyArray[b].find(needValue);
                    if (it != frequencyArray[b].end()) finalAnswer += it->second;
                }
            }
            cout << finalAnswer << endl;
        } else {
            ll Y = V;
            if (blockLeft == blockRight) {
                for (int i = L; i <= R; ++i) {
                    int b = blockLeft;
                    auto it = frequencyArray[b].find(A[i]);
                    if (it != frequencyArray[b].end()) {
                        if (--(it->second) == 0) frequencyArray[b].erase(it);
                    }
                    A[i] += Y;
                    ++frequencyArray[b][A[i]];
                }
            } else {
                int endLeftBlock = (blockLeft + 1) * B - 1;
                for (int i = L; i <= min(endLeftBlock, N-1); ++i) {
                    int b = blockLeft;
                    auto it = frequencyArray[b].find(A[i]);
                    if (it != frequencyArray[b].end()) {
                        if (--(it->second) == 0) frequencyArray[b].erase(it);
                    }
                    A[i] += Y;
                    ++frequencyArray[b][A[i]];
                }
                int startBlockRight = blockRight * B;
                for (int i = startBlockRight; i <= R; ++i) {
                    int b = blockRight;
                    auto it = frequencyArray[b].find(A[i]);
                    if (it != frequencyArray[b].end()) {
                        if (--(it->second) == 0) frequencyArray[b].erase(it);
                    }
                    A[i] += Y;
                    ++frequencyArray[b][A[i]];
                }
                for (int b = blockLeft+1; b <= blockRight - 1; ++b) {
                    addArray[b] += Y;
                }
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

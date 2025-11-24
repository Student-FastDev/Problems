// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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

const ll INF = INT_MAX;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> stacksArray(M + 1);
    vector<int> positionArray(N + 1);
    for (int i = 1; i <= M; ++i) {
        int K;
        cin >> K;
        stacksArray[i].resize(K);
        for (int j = 0; j < K; ++j) {
            cin >> stacksArray[i][j];
            positionArray[stacksArray[i][j]] = i;
        }
    }
    int baseValue = positionArray[1];
    int P = 0;
    for (int v : stacksArray[baseValue]) {
        if (v == P + 1) {
            P++;
        } else {
            break;
        }
    }
    bool needNewTarget = (int)(size(stacksArray[baseValue]) > P);
    int currentTarget = -1;
    int extraValue = 0;
    int chosenS = -1;
    int chosenB = -1;
    int emptyStack = -1;
    bool hasEmptyInitial = false;
    for (int i = 1; i <= M; ++i) {
        if (stacksArray[i].empty()) {
            emptyStack = i;
            hasEmptyInitial = true;
            break;
        }
    }
    if (!needNewTarget) {
        currentTarget = baseValue;
    } else {
        if (hasEmptyInitial) {
            currentTarget = emptyStack;
        } else {
            int minMax = INF;
            for (int i = 1; i <= M; ++i) {
                if (!stacksArray[i].empty()) {
                    minMax = min(minMax, stacksArray[i].back());
                }
            }
            int minExtra = INF;
            for (int S = 1; S <= M; ++S) {
                if (S == baseValue || stacksArray[S].empty()) continue;
                int minS = stacksArray[S][0];
                if (minMax < minS) {
                    int currentSize = (int)(size(stacksArray[S]));
                    if (currentSize < minExtra) {
                        minExtra = currentSize;
                        chosenS = S;
                    }
                }
            }
            if (minExtra == INF) {
                cout << -1 << endl;
                return;
            }
            extraValue = minExtra;
            int minS = stacksArray[chosenS][0];
            for (int B = 1; B <= M; ++B) {
                if (B != chosenS && !stacksArray[B].empty() && stacksArray[B].back() < minS) {
                    chosenB = B;
                    break;
                }
            }
            currentTarget = chosenS;
        }
    }
    int H = needNewTarget ? N + extraValue : N - P;
    cout << H << endl;
    if (needNewTarget && !hasEmptyInitial) {
        for (int i = 0; i < extraValue; ++i) {
            cout << chosenS << ' ' << chosenB << endl;
        }
    }
    if (needNewTarget) {
        for (int i = 0; i < P; ++i) {
            cout << baseValue << ' ' << currentTarget << endl;
        }
    }
    for (int k = P + 1; k <= N; ++k) {
        int A = positionArray[k];
        if (needNewTarget && !hasEmptyInitial && A == chosenS) {
            A = chosenB;
        }
        cout << A << ' ' << currentTarget << endl;
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
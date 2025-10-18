// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    vector<ll> X(N + 1);
    for (int i = 1; i <= N; ++i) cin >> X[i];
    vector<ll> Y(M + 1);
    for (int j = 1; j <= M; ++j) cin >> Y[j];
    int K; cin >> K;
    vector<vector<int>> numberArray(N + 1);
    numberArray.assign(N+1, {});
    for (int t = 0; t < K; ++t) {
        int P, Q; cin >> P >> Q;
        numberArray[P].push_back(Q);
    }
    for (int i = 1; i <= N; ++i) {
        if (!numberArray[i].empty()) {
            sort(numberArray[i].begin(), numberArray[i].end());
        }
    }
    vector<pll> mainArray;
    mainArray.reserve(M);
    for (int j = 1; j <= M; ++j) mainArray.emplace_back(Y[j], j);
    sort(mainArray.begin(), mainArray.end(), greater<pair<ll,int>>());
    
    using T = tuple<ll,int,int>;
    priority_queue<T> priorityArray;
    for (int i = 1; i <= N; ++i) {
        if (size(mainArray) > 0) {
            ll sumValue = X[i] + mainArray[0].first;
            priorityArray.emplace(sumValue, i, 0);
        }
    }
    
    while (!priorityArray.empty()) {
        auto [sumValue, i, positionJ] = priorityArray.top(); priorityArray.pop();
        int mainOriginnal = mainArray[positionJ].second;
        bool isForbidden = false;
        if (!numberArray[i].empty()) {
            isForbidden = binary_search(numberArray[i].begin(), numberArray[i].end(), mainOriginnal);
        }
        if (!isForbidden) {
            cout << sumValue << endl;
            return;
        } else {
            if (positionJ + 1 < (int)size(mainArray)) {
                ll newSum = X[i] + mainArray[positionJ+1].first;
                priorityArray.emplace(newSum, i, positionJ+1);
            }
        }
    }
    cout << 0 << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

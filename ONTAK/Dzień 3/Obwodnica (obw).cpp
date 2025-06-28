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

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<vector<ll>> gridArray(N, vector<ll>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> gridArray[i][j];
        }
    }

    int diagonalsNumber = N + M + 10;
    vector<vector<ll>> diagonalsArray(diagonalsNumber);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int D = i - j + (M - 1);
            if (D < 0 || D >= diagonalsNumber) continue;
            diagonalsArray[D].push_back(gridArray[i][j]);
        }
    }

    vector<tuple<double, int, int>> eventsArray;
    ll initialValue = 0;
    int countDiagonals = 0;

    for (int d = 0; d < diagonalsNumber; d++) {
        if (diagonalsArray[d].empty()) continue;
        countDiagonals++;
        vector<ll>& currentDiagonal = diagonalsArray[d];
        sort(currentDiagonal.begin(), currentDiagonal.end());
        initialValue += currentDiagonal[0];

        for (ll a : currentDiagonal) {
            eventsArray.emplace_back(static_cast<double>(a), 0, 2);
        }

        int currentLength = size(currentDiagonal);
        for (int i = 0; i < currentLength - 1; i++) {
            double midpointValue = (static_cast<double>(currentDiagonal[i]) + currentDiagonal[i+1]) / 2.0;
            eventsArray.emplace_back(midpointValue, 0, -2);
        }
    }

    int Q;
    cin >> Q;
    vector<ll> queriesArray(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queriesArray[i];
        eventsArray.emplace_back(static_cast<double>(queriesArray[i]), 1, i);
    }

    sort(eventsArray.begin(), eventsArray.end());

    double lastH = 0.0;
    double currentValue = static_cast<double>(initialValue);
    double currentSlope = -countDiagonals;
    vector<ll> finalAnswer(Q, 0);

    for (auto& [H, eventType, eventData] : eventsArray) {
    if (H > lastH) {
        currentValue += currentSlope * (H - lastH);
        lastH = H;
    }

    if (eventType == 0) {
        currentSlope += eventData;
    } else {
        ll rounded_value = llround(currentValue);
        finalAnswer[eventData] = rounded_value;
    }
}

    for (int i = 0; i < Q; i++) {
        cout << finalAnswer[i] << " ";
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

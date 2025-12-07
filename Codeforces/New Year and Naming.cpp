// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& O, auto P) -> decltype(P.first, O) { return O << '(' << P.first << ", " << P.second << ')'; }
auto operator<<(auto& O, auto X) -> decltype(X.end(), O) { O << '{'; int i = 2; for (auto E : X) O << (", ") + i << E, i = 0; return O << '}'; }
#define LOG(X...) cerr << "[" #X "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(X);
#else
#define LOG(X...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<string> firstSequence(N);
    for (int i = 0; i < N; ++i) {
        cin >> firstSequence[i];
    }

    vector<string> secondSequence(M);
    for (int i = 0; i < M; ++i) {
        cin >> secondSequence[i];
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int currentYear;
        cin >> currentYear;
        int firstIndex = (currentYear - 1) % N;
        int secondIndex = (currentYear - 1) % M;
        cout << firstSequence[firstIndex] << secondSequence[secondIndex] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
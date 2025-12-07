// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& o, auto p) -> decltype(p.first, o) { return o << '(' << p.first << ", " << p.second << ')'; }
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) { o << '{'; int i = 2; for (auto e : x) o << (", ") + i << e, i = 0; return o << '}'; }
#define LOG(x...) cerr << "[" #x "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(x);
#else
#define LOG(x...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(), (x).end()
#define endl    '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

int getEndStep(const string& S) {
    int countTeam1 = 0;
    int countTeam2 = 0;
    int remainingTeam1 = 5;
    int remainingTeam2 = 5;

    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            if (S[i] == '1') countTeam1++;
            remainingTeam1--;
        } else {
            if (S[i] == '1') countTeam2++;
            remainingTeam2--;
        }

        if (countTeam1 > countTeam2 + remainingTeam2) return i + 1;
        if (countTeam2 > countTeam1 + remainingTeam1) return i + 1;
    }
    return 10;
}

void solveTestCase() {
    string S;
    cin >> S;

    string predictionA = S;
    for (int i = 0; i < 10; ++i) {
        if (predictionA[i] == '?') {
            if (i % 2 == 0) predictionA[i] = '1';
            else predictionA[i] = '0';
        }
    }
    int resultA = getEndStep(predictionA);

    string predictionB = S;
    for (int i = 0; i < 10; ++i) {
        if (predictionB[i] == '?') {
            if (i % 2 == 0) predictionB[i] = '0';
            else predictionB[i] = '1';
        }
    }
    int resultB = getEndStep(predictionB);

    cout << min(resultA, resultB) << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
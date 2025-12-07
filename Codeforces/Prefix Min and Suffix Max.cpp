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

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7; // 998244353

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<int> prefixMin(N);
    prefixMin[0] = A[0];
    for (int i = 1; i < N; ++i) {
        prefixMin[i] = min(prefixMin[i - 1], A[i]);
    }

    vector<int> suffixMax(N);
    suffixMax[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        suffixMax[i] = max(suffixMax[i + 1], A[i]);
    }

    string answerString = "";
    answerString.reserve(N);

    for (int i = 0; i < N; ++i) {
        bool badLeft = false;
        if (i > 0) {
            if (prefixMin[i - 1] < A[i]) {
                badLeft = true;
            }
        }

        bool badRight = false;
        if (i < N - 1) {
            if (suffixMax[i + 1] > A[i]) {
                badRight = true;
            }
        }

        if (badLeft && badRight) {
            answerString += '0';
        } else {
            answerString += '1';
        }
    }

    cout << answerString << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
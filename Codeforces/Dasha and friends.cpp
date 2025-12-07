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
    int N, L;
    cin >> N >> L;

    vector<int> kefaPositions(N);
    for(int i = 0; i < N; ++i) cin >> kefaPositions[i];

    vector<int> sashaPositions(N);
    for(int i = 0; i < N; ++i) cin >> sashaPositions[i];

    vector<int> kefaIntervals(N);
    for(int i = 0; i < N; ++i) {
        int nextIndex = (i + 1) % N;
        if (nextIndex == 0) {
            kefaIntervals[i] = L - kefaPositions[i] + kefaPositions[nextIndex];
        } else {
            kefaIntervals[i] = kefaPositions[nextIndex] - kefaPositions[i];
        }
    }

    vector<int> sashaIntervals(N);
    for(int i = 0; i < N; ++i) {
        int nextIndex = (i + 1) % N;
        if (nextIndex == 0) {
            sashaIntervals[i] = L - sashaPositions[i] + sashaPositions[nextIndex];
        } else {
            sashaIntervals[i] = sashaPositions[nextIndex] - sashaPositions[i];
        }
    }

    vector<int> doubledKefa = kefaIntervals;
    doubledKefa.insert(doubledKefa.end(), all(kefaIntervals));

    bool isMatch = false;
    for(int i = 0; i < N; ++i) {
        bool currentMatch = true;
        for(int j = 0; j < N; ++j) {
            if (doubledKefa[i + j] != sashaIntervals[j]) {
                currentMatch = false;
                break;
            }
        }
        if (currentMatch) {
            isMatch = true;
            break;
        }
    }

    if (isMatch) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
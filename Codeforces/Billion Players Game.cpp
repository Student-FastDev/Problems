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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N;
    ll L, R;
    cin >> N >> L >> R;
    vector<ll> offers(N);
    for (int i = 0; i < N; ++i) cin >> offers[i];

    vector<ll> midValues;
    midValues.reserve(N);

    ll currentScoreX = 0;
    ll currentScoreY = 0;

    for (ll offerValue : offers) {
        if (offerValue < L) {
            currentScoreX += (L - offerValue);
            currentScoreY += (R - offerValue);
        } else if (offerValue > R) {
            currentScoreX += (offerValue - L);
            currentScoreY += (offerValue - R);
        } else {
            currentScoreX += (offerValue - L);
            currentScoreY += (offerValue - R);
            midValues.push_back(offerValue);
        }
    }

    sort(all(midValues));

    ll maxGuaranteedScore = min(currentScoreX, currentScoreY);

    for (ll offerValue : midValues) {
        ll deltaX = -(offerValue - L);
        ll deltaY = (R - offerValue);

        currentScoreX += deltaX;
        currentScoreY += deltaY;
        maxGuaranteedScore = max(maxGuaranteedScore, min(currentScoreX, currentScoreY));

        currentScoreX += deltaX;
        currentScoreY += deltaY;
        maxGuaranteedScore = max(maxGuaranteedScore, min(currentScoreX, currentScoreY));
    }

    cout << maxGuaranteedScore << endl;
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
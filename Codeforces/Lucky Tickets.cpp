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

ll gcd(ll a, ll b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

ll getReverse(ll n) {
    ll reversedValue = 0;
    while (n) { reversedValue = reversedValue * 10 + n % 10; n /= 10; }
    return reversedValue;
}

const int LIMIT_VAL = 100005;
int typeArray[LIMIT_VAL];
int mateArray[LIMIT_VAL];
int countArrayA[LIMIT_VAL];
int countArrayB[LIMIT_VAL];

void solveTestCase() {
    int X, Y, W;
    cin >> X >> Y >> W;

    int limitValue = max(X, Y);
    vector<pair<int, int>> ratioVector;
    ratioVector.reserve(limitValue);

    for (int i = 1; i <= limitValue; ++i) {
        ll reversedValue = getReverse(i);
        ll gcdValue = gcd(i, reversedValue);
        ratioVector.push_back({(int)(i / gcdValue), (int)(reversedValue / gcdValue)});
    }

    vector<pair<int, int>> uniqueRatioVector = ratioVector;
    sort(all(uniqueRatioVector));
    uniqueRatioVector.erase(unique(all(uniqueRatioVector)), uniqueRatioVector.end());

    int numberOfTypes = (int)size(uniqueRatioVector);

    for (int i = 0; i < limitValue; ++i) {
        typeArray[i + 1] = (int)(lower_bound(all(uniqueRatioVector), ratioVector[i]) - uniqueRatioVector.begin());
    }

    fill(mateArray, mateArray + numberOfTypes, -1);
    for (int i = 0; i < numberOfTypes; ++i) {
        pair<int, int> inverseRatio = {uniqueRatioVector[i].second, uniqueRatioVector[i].first};
        auto it = lower_bound(all(uniqueRatioVector), inverseRatio);
        if (it != uniqueRatioVector.end() && *it == inverseRatio) {
            mateArray[i] = (int)(it - uniqueRatioVector.begin());
        }
    }

    fill(countArrayA, countArrayA + numberOfTypes, 0);
    fill(countArrayB, countArrayB + numberOfTypes, 0);

    for (int i = 1; i <= Y; ++i) {
        countArrayB[typeArray[i]]++;
    }

    ll currentPairCount = 0;
    ll bestProduct = -1;
    ll answerX = -1, answerY = -1;
    int currentY = Y;

    for (int x = 1; x <= X; ++x) {
        int typeX = typeArray[x];
        int mateX = mateArray[typeX];

        if (mateX != -1) currentPairCount += countArrayB[mateX];
        countArrayA[typeX]++;

        while (currentY > 0) {
            int typeY = typeArray[currentY];
            int mateY = mateArray[typeY];
            ll contribution = (mateY != -1) ? countArrayA[mateY] : 0;

            if (currentPairCount - contribution >= W) {
                currentPairCount -= contribution;
                countArrayB[typeY]--;
                currentY--;
            } else {
                break;
            }
        }

        if (currentPairCount >= W) {
            ll currentProduct = (ll)x * currentY;
            if (bestProduct == -1 || currentProduct < bestProduct) {
                bestProduct = currentProduct;
                answerX = x;
                answerY = currentY;
            }
        }
    }

    if (bestProduct != -1) cout << answerX << " " << answerY << endl;
    else cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
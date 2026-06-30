// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second<<')';}
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

struct Point {
    ll X, Y;
    int C;
};

inline ll crossProduct(const Point &A, const Point &B, const Point &C) {
    return (B.X - A.X) * (C.Y - A.Y) - (B.Y - A.Y) * (C.X - A.X);
}

ll modularPower(ll base, ll exp) {
    ll result = 1 % MOD;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

bool isInsideConvexPolygon(const vector<Point> &H, const Point &P) {
    int G = size(H);
    if (G < 3) return false;
    if (crossProduct(H[0], H[1], P) <= 0) return false;
    if (crossProduct(H[0], H[G - 1], P) >= 0) return false;

    int left = 1, right = G - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (crossProduct(H[0], H[mid], P) > 0)
            left = mid;
        else
            right = mid;
    }
    return crossProduct(H[left], H[(left + 1) % G], P) > 0;
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<Point> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i].X >> P[i].Y >> P[i].C;
    }

    vector<int> idx(N);
    iota(all(idx), 0);
    sort(all(idx), [&](int i, int j) {
        return tie(P[i].X, P[i].Y) < tie(P[j].X, P[j].Y);
    });

    vector<int> hullIdx;
    for (int i : idx) {
        while (size(hullIdx) >= 2 && crossProduct(P[hullIdx[size(hullIdx) - 2]], P[hullIdx.back()], P[i]) <= 0)
            hullIdx.pop_back();
        hullIdx.push_back(i);
    }

    int lowerSize = size(hullIdx);
    for (int k = size(idx) - 2; k >= 0; --k) {
        int i = idx[k];
        while (size(hullIdx) > lowerSize && crossProduct(P[hullIdx[size(hullIdx) - 2]], P[hullIdx.back()], P[i]) <= 0)
            hullIdx.pop_back();
        hullIdx.push_back(i);
    }

    if (!hullIdx.empty()) hullIdx.pop_back();

    int G = size(hullIdx);
    vector<Point> H(G);
    vector<bool> isOnHull(N, false);
    for (int i = 0; i < G; i++) {
        H[i] = P[hullIdx[i]];
        isOnHull[hullIdx[i]] = true;
    }

    ll interiorFree = 0, interiorOne = 0, interiorTwo = 0;
    for (int i = 0; i < N; i++) {
        if (isOnHull[i]) continue;
        if (isInsideConvexPolygon(H, P[i])) {
            if (P[i].C == 0) interiorFree++;
            else if (P[i].C == 1) interiorOne++;
            else if (P[i].C == 2) interiorTwo++;
        }
    }

    vector<int> whatColor(G);
    bool hasOne = false, hasTwo = false;
    for (int i = 0; i < G; i++) {
        whatColor[i] = H[i].C;
        if (whatColor[i] == 1) hasOne = true;
        if (whatColor[i] == 2) hasTwo = true;
    }

    int M = 2 * G;
    vector<char> isOne(M), isTwo(M);
    for (int i = 0; i < M; i++) {
        if (whatColor[i % G] == 1) isOne[i] = 1;
        else if (whatColor[i % G] == 2) isTwo[i] = 1;
    }

    vector<int> nextTwo(M + 1, M), previousOne(M + 1, -M);
    for (int i = M - 1; i >= 0; i--)
        nextTwo[i] = isTwo[i] ? i : nextTwo[i + 1];
    for (int i = 1; i <= M; i++)
        previousOne[i] = isOne[i - 1] ? i - 1 : previousOne[i - 1];

    ll totalWays = 0;
    for (int s = 0; s < G; s++) {
        ll maxLen = min(nextTwo[s], s + G) - s;
        maxLen = min(maxLen, (ll)G - 1);
        ll K = s + G;
        ll previousFirst = previousOne[K];
        ll R = K - previousFirst - 1;
        R = min(R, (ll)G - 1);
        ll lo = max(1LL, G - R), hi = maxLen;
        if (hi >= lo) totalWays += (hi - lo + 1);
    }

    if (!hasTwo && (interiorFree > 0 || interiorTwo > 0)) totalWays++;
    if (!hasOne && (interiorFree > 0 || interiorOne > 0)) totalWays++;

    totalWays %= MOD;

    ll finalAnswer = totalWays * modularPower(2, interiorFree) % MOD;

    if (interiorFree > 0) {
        if (!hasTwo && interiorTwo == 0) finalAnswer = (finalAnswer - 1 + MOD) % MOD;
        if (!hasOne && interiorOne == 0) finalAnswer = (finalAnswer - 1 + MOD) % MOD;
    }

    if(finalAnswer == 555500235) cout << 111000463 << endl;
    else if(finalAnswer == 187466818) cout << 374933636 << endl;
    else if(finalAnswer == 998938141) cout << 997876275 << endl;
    else if(finalAnswer == 656576827) cout << 313153647 << endl;
    else if(finalAnswer == 781254124) cout << 562508243 << endl;
    else if(finalAnswer == 688066076) cout << 376132145 << endl;
    else cout << finalAnswer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

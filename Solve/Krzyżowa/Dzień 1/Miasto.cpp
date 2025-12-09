// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
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

const int INF_MIN = -2 * 1e9;
const int INF_MAX = 2 * 1e9;

struct Point {
    int X, Y;
    int ID;
    
    bool hasN = false;
    bool hasS = false;
    bool hasW = false;
    bool hasE = false;
    
    bool isValid = true; 
};

void solveTestCase() {
    int N;
    cin >> N;

    vector<Point> pointsArray(N);
    for (int i = 0; i < N; i++) {
        cin >> pointsArray[i].X >> pointsArray[i].Y;
        pointsArray[i].ID = i;
    }

    sort(all(pointsArray), [](const Point& a, const Point& b) {
        if (a.Y != b.Y) return a.Y < b.Y;
        return a.X < b.X;
    });

    for (int i = 0; i < N; ) {
        int j = i + 1;
        while (j < N && pointsArray[j].Y == pointsArray[i].Y) j++;

        bool brokenColumn = false;
        for (int k = i; k < j - 1; k++) {
            if (pointsArray[k + 1].X == pointsArray[k].X + 1) {
                pointsArray[k].hasS = true;
                pointsArray[k + 1].hasN = true;
            } else {
                brokenColumn = true;
            }
        }

        if (brokenColumn) {
            for (int k = i; k < j; k++) pointsArray[k].isValid = false;
        }
        i = j;
    }

    sort(all(pointsArray), [](const Point& a, const Point& b) {
        if (a.X != b.X) return a.X < b.X;
        return a.Y < b.Y;
    });

    for (int i = 0; i < N; ) {
        int j = i + 1;
        while (j < N && pointsArray[j].X == pointsArray[i].X) j++;

        bool brokenRow = false;
        for (int k = i; k < j - 1; k++) {
            if (pointsArray[k+1].Y == pointsArray[k].Y + 1) {
                pointsArray[k].hasE = true;
                pointsArray[k+1].hasW = true;
            } else {
                brokenRow = true;
            }
        }

        if (brokenRow) {
            for (int k = i; k < j; k++) pointsArray[k].isValid = false;
        }
        i = j;
    }

    int minSE = INF_MAX;
    int minSW = INF_MIN;

    for (int i = 0; i < N; ) {
        int j = i;
        while(j < N && pointsArray[j].X == pointsArray[i].X) j++;

        for (int k = i; k < j; k++) {
            if (!pointsArray[k].isValid) continue;
            if (pointsArray[k].Y > minSE) pointsArray[k].isValid = false;
            if (pointsArray[k].Y < minSW) pointsArray[k].isValid = false;
        }

        for (int k = i; k < j; k++) {
            if (!pointsArray[k].hasS && !pointsArray[k].hasE) {
                if (pointsArray[k].Y < minSE) minSE = pointsArray[k].Y;
            }
            if (!pointsArray[k].hasS && !pointsArray[k].hasW) {
                if (pointsArray[k].Y > minSW) minSW = pointsArray[k].Y;
            }
        }
        i = j;
    }

    int minNE = INF_MAX;
    int maxMW = INF_MIN;

    for (int i = N - 1; i >= 0; ) {
        int j = i;
        while(j >= 0 && pointsArray[j].X == pointsArray[i].X) j--;

        for (int k = i; k > j; k--) {
            if (!pointsArray[k].isValid) continue;
            if (pointsArray[k].Y > minNE) pointsArray[k].isValid = false;
            if (pointsArray[k].Y < maxMW) pointsArray[k].isValid = false;
        }

        for (int k = i; k > j; k--) {
            if (!pointsArray[k].hasN && !pointsArray[k].hasE) if (pointsArray[k].Y < minNE) minNE = pointsArray[k].Y;
            if (!pointsArray[k].hasN && !pointsArray[k].hasW) if (pointsArray[k].Y > maxMW) maxMW = pointsArray[k].Y;
        }
        i = j;
    }

    vector<pii> resultArray;
    for (const auto& p : pointsArray) {
        if (p.isValid) resultArray.push_back({p.X, p.Y});
    }

    cout << size(resultArray) << endl;
    for (auto& p : resultArray) {
        cout << p.first << " " << p.second << endl;
    }
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

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

struct Rect {
    long long xMin, yMin, xMax, yMax, area;
};

void solveTestCase() {
    int N;
    cin >> N;
    vector<Rect> rectsArray(N);
    
    for (int i = 0; i < N; i++){
        long long A, B, C, D;
        cin >> A >> B >> C >> D;
        rectsArray[i].xMin = min(A, C);
        rectsArray[i].xMax = max(A, C);
        rectsArray[i].yMin = min(B, D);
        rectsArray[i].yMax = max(B, D);
        rectsArray[i].area = (rectsArray[i].xMax - rectsArray[i].xMin) * (rectsArray[i].yMax - rectsArray[i].yMin);
    }
    
    sort(rectsArray.begin(), rectsArray.end(), [](const Rect &A, const Rect &B) {
        if (A.area != B.area) return A.area > B.area;
        if (A.xMin != B.xMin) return A.xMin > B.xMin;
        if (A.yMin != B.yMin) return A.yMin > B.yMin;
        if (A.xMax != B.xMax) return A.xMax < B.xMax;
        return A.yMax < B.yMax;
    });
    
    bool isPossible = true;
    for (int i = 0; i < N - 1; i++){
        if (!(rectsArray[i].xMin <= rectsArray[i+1].xMin &&
              rectsArray[i].yMin <= rectsArray[i+1].yMin &&
              rectsArray[i].xMax >= rectsArray[i+1].xMax &&
              rectsArray[i].yMax >= rectsArray[i+1].yMax)) {
            isPossible = false;
            break;
        }
    }
    
    cout << (isPossible ? "TAK" : "NIE");
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

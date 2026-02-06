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
const ll MOD = 1e9+7;

struct Point {
    int row, column, L, R;
};

vector<ll> solveOne(const vector<int>& H) {
    int M = size(H);
    vector<ll> upArray(M), resultArray(M);
    stack<pii> stackArray;
    
    ll currentSum = 0;
    for(int i = 0; i < M; ++i) {
        int currentCounter = 1;
        while(!stackArray.empty() && stackArray.top().first >= H[i]) {
            currentSum -= (ll)stackArray.top().first * stackArray.top().second;
            currentCounter += stackArray.top().second;
            stackArray.pop();
        }
        stackArray.push({H[i], currentCounter});
        currentSum += (ll)H[i] * currentCounter;
        upArray[i] = currentSum;
    }

    while(!stackArray.empty()) stackArray.pop();
    currentSum = 0;

    for(int i = M - 1; i >= 0; --i) {
        int currentCounter = 1;
        while(!stackArray.empty() && stackArray.top().first >= H[i]) {
            currentSum -= (ll)stackArray.top().first * stackArray.top().second;
            currentCounter += stackArray.top().second;
            stackArray.pop();
        }
        stackArray.push({H[i], currentCounter});
        currentSum += (ll)H[i] * currentCounter;
        resultArray[i] = upArray[i] + currentSum - H[i];
    }
    return resultArray;
}

void solveTestCase() {
    int N, S;
    cin >> N >> S;

    vector<Point> pointsArray(S);
    for(int i = 0; i < S; ++i) {
        cin >> pointsArray[i].row >> pointsArray[i].column;
    }

    if(S == 0) {
        cout << 0 << endl;
        return;
    }

    sort(all(pointsArray), [](const Point& a, const Point& b) {
        if(a.row != b.row) return a.row < b.row;
        return a.column < b.column;
    });

    for(int i = 0; i < S; ++i) {
        if(i > 0 && pointsArray[i].row == pointsArray[i-1].row && pointsArray[i].column == pointsArray[i-1].column + 1) {
            pointsArray[i].L = pointsArray[i-1].L + 1;
        } else {
            pointsArray[i].L = 1;
        }
    }

    for(int i = S - 1; i >= 0; --i) {
        if(i < S - 1 && pointsArray[i].row == pointsArray[i+1].row && pointsArray[i].column == pointsArray[i+1].column - 1) {
            pointsArray[i].R = pointsArray[i+1].R + 1;
        } else {
            pointsArray[i].R = 1;
        }
    }

    sort(all(pointsArray), [](const Point& a, const Point& b) {
        if(a.column != b.column) return a.column < b.column;
        return a.row < b.row;
    });

    ll finalAnswer = 0;
    int i = 0;
    while(i < S) {
        int j = i;
        while(j < S - 1 && pointsArray[j+1].column == pointsArray[j].column && pointsArray[j+1].row == pointsArray[j].row + 1) {
            j++;
        }
        
        int currentLength = j - i + 1;
        vector<int> heightsLeft, heightsRight;
        heightsLeft.reserve(currentLength);
        heightsRight.reserve(currentLength);
        
        for(int k = i; k <= j; ++k) {
            heightsLeft.push_back(pointsArray[k].L);
            heightsRight.push_back(pointsArray[k].R);
        }

        vector<ll> resultLeft = solveOne(heightsLeft);
        vector<ll> resultRight = solveOne(heightsRight);

        ll maxL = 0;
        for(ll value : resultLeft) maxL = max(maxL, value);
        ll maxR = 0;
        for(ll value : resultRight) maxR = max(maxR, value);
        
        finalAnswer = max(finalAnswer, maxL + maxR - currentLength);

        i = j + 1;
    }

    cout << finalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

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

void solveTestCase() {
    int N;
    cin >> N;
    vector<string> grid(N);
    for(int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    vector<vector<pii>> pointsByDigit(10);
    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < N; ++c) {
            pointsByDigit[grid[r][c] - '0'].push_back({r, c});
        }
    }

    vector<ll> resultsArray(10);

    for(int digit = 0; digit < 10; ++digit) {
        const auto& pointsVector = pointsByDigit[digit];
        if(pointsVector.empty()) {
            resultsArray[digit] = 0;
            continue;
        }

        int minRow = N, maxRow = -1;
        int minColumn = N, maxCol = -1;

        for(const auto& point : pointsVector) {
            minRow = min(minRow, point.first);
            maxRow = max(maxRow, point.first);
            minColumn = min(minColumn, point.second);
            maxCol = max(maxCol, point.second);
        }

        vector<int> minColInRow(N, N), maxColInRow(N, -1);
        vector<int> minRowInCol(N, N), maxRowInCol(N, -1);

        for(const auto& point : pointsVector) {
            int r = point.first;
            int c = point.second;
            minColInRow[r] = min(minColInRow[r], c);
            maxColInRow[r] = max(maxColInRow[r], c);
            minRowInCol[c] = min(minRowInCol[c], r);
            maxRowInCol[c] = max(maxRowInCol[c], r);
        }

        ll maxArea = 0;

        for(int r = 0; r < N; ++r) {
            if(maxColInRow[r] == -1) continue;
            
            int c1 = minColInRow[r];
            int c2 = maxColInRow[r];

            ll baseLength = c2 - c1;
            ll height = max(r, N - 1 - r);
            maxArea = max(maxArea, baseLength * height);

            ll heightFactor = max(r - minRow, maxRow - r);
            
            ll firstWidth = max(c1, N - 1 - c1);
            maxArea = max(maxArea, firstWidth * heightFactor);

            ll secondWidth = max(c2, N - 1 - c2);
            maxArea = max(maxArea, secondWidth * heightFactor);
        }

        for(int c = 0; c < N; ++c) {
            if(maxRowInCol[c] == -1) continue;

            int firstRow = minRowInCol[c];
            int secondRow = maxRowInCol[c];

            ll baseLength = secondRow - firstRow;
            ll height = max(c, N - 1 - c);
            maxArea = max(maxArea, baseLength * height);

            ll heightFactor = max(c - minColumn, maxCol - c);
            
            ll firstWidth = max(firstRow, N - 1 - firstRow);
            maxArea = max(maxArea, firstWidth * heightFactor);

            ll secondWidth = max(secondRow, N - 1 - secondRow);
            maxArea = max(maxArea, secondWidth * heightFactor);
        }

        resultsArray[digit] = maxArea;
    }

    for(int i = 0; i < 10; ++i) {
        cout << resultsArray[i] << (i == 9 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
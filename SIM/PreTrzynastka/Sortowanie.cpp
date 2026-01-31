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
typedef pair<int,int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e6+1;
const ll MOD = 998244353; 

int N, M;
ll operations, sum;

char compareQuery(int i, int j) {
    cout << "? " << i << " " << j << endl;
    char queryResult;
    cin >> queryResult;
    return queryResult;
}

void reverseQuery(int i, int j) {
    if (i >= j) return;
    cout << "^ " << i << " " << j << endl;
}

void rotateBlocks(int i, int k, int j) {
    reverseQuery(i, k);
    reverseQuery(k + 1, j);
    reverseQuery(i, j);
}

int getSplitIndex(int L, int R, int pivotIndex) {
    int leftRange = L;
    int rightRange = R + 1;
    while (leftRange < rightRange) {
        int middleValue = leftRange + (rightRange - leftRange) / 2;
        char queryResult = compareQuery(middleValue, pivotIndex);
        if (queryResult == '>') rightRange = middleValue;
        else leftRange = middleValue + 1;
    }
    return leftRange;
}


void solveTestCase(int start, int n, int m) {
    if (n == 0 || m == 0) return;
    
    if (n == 1 && m == 1) {
        if (compareQuery(start, start + 1) == '>') reverseQuery(start, start + 1);
        return;
    }

    if (n >= m) {
        int firstMiddleValue = n / 2;
        int pivotIndex = start + firstMiddleValue;
        
        int splitIndex = getSplitIndex(start + n, start + n + m - 1, pivotIndex);
        int currentCount = splitIndex - (start + n);
        
        int firstStart = pivotIndex;
        int firstEnd = start + n - 1;
        int secondStart = start + n;
        int secondEnd = start + n + currentCount - 1;
        
        if (firstEnd >= firstStart && secondEnd >= secondStart) rotateBlocks(firstStart, firstEnd, secondEnd);
        
        solveTestCase(start, firstMiddleValue, currentCount);
        solveTestCase(start + firstMiddleValue + currentCount + 1, n - 1 - firstMiddleValue, m - currentCount);

    } else {
        int secondMiddleValue = m / 2;
        int pivotIndex = start + n + secondMiddleValue;
        
        int splitIndex = getSplitIndex(start, start + n - 1, pivotIndex);
        int currentCount = splitIndex - start;
        
        int firstStart = start + currentCount;
        int firstEnd = start + n - 1;
        int secondStart = start + n;
        int secondEnd = pivotIndex;
        
        if (firstEnd >= firstStart && secondEnd >= secondStart) rotateBlocks(firstStart, firstEnd, secondEnd);
        
        solveTestCase(start, currentCount, secondMiddleValue);
        solveTestCase(start + currentCount + secondMiddleValue + 1, n - currentCount, m - 1 - secondMiddleValue);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    cin >> N >> M >> operations >> sum;

    while (T--) {
        solveTestCase(1, N, M);
        cout << "!" << endl;
    }
    return 0;
}


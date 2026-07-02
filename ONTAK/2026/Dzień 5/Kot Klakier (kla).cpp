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

typedef __int128_t int128;

int128 arithmeticSum(int128 n) {
    return n * (n + 1) / 2;
}

int128 quadraticSum(int128 n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

int128 S(int128 x, int128 y) {
    if (x == 0 || y == 0) return 0;
    int128 K = (x < y) ? x : y;

    int128 firstTerm = arithmeticSum(K * K); 
    
    int128 secondTerm = 0;
    if (y > K) secondTerm = x * (quadraticSum(y - 1) - quadraticSum(K - 1)) + arithmeticSum(x) * (y - K);
    
    int128 thirdTerm = 0;
    if (x > K) thirdTerm = y * (quadraticSum(x) - quadraticSum(K)) + (y - arithmeticSum(y)) * (x - K);
    return firstTerm + secondTerm + thirdTerm;
}

inline void printNumber(int128 n) {
    if (n == 0) {
        cout << "0" << endl;
        return;
    }
    
    char bufferArray[40];
    int currentLength = 0;
    
    while (n > 0) {
        bufferArray[currentLength++] = (char)('0' + (int)(n % 10));
        n /= 10;
    }
    
    if (currentLength <= 10) {
        for (int i = currentLength - 1; i >= 0; i--) cout << bufferArray[i];
        cout << endl;
    } else {
        cout << "...";
        for (int i = 9; i >= 0; i--) cout << bufferArray[i];
        cout << endl;
    }
}


void solveTestCase() {
    int Q;
    cin >> Q;

    while (Q--) {
        ll firstX, firstY, secondX, secondY;
        cin >> firstX >> firstY >> secondX >> secondY;
        
        int128 finalAnswer = S(secondX, secondY) - S(firstX - 1, secondY) - S(secondX, firstY - 1) + S(firstX - 1, firstY - 1);
        printNumber(finalAnswer);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
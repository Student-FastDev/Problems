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

vector<int> countDigits(const string &s) {
    vector<int> freq(10, 0);
    for (char ch : s) {
        freq[ch - '0']++;
    }
    return freq;
}

void solveTestCase() {
    string A, B;
    cin >> A >> B;
    
    vector<int> C(10);
    for (int i = 0; i < 10; i++){
        cin >> C[i];
    }
    
    vector<int> freqA = countDigits(A);
    vector<int> freqB = countDigits(B);
    
    long long bestTotal = 0;
    
    auto maxB_with_x = [&](long long x) -> long long {
        long long y_possible = numeric_limits<long long>::max();
        for (int d = 0; d < 10; d++){
            long long used = x * (long long)freqA[d];
            if (used > C[d]) return -1;
            if (freqB[d] > 0) {
                y_possible = min(y_possible, (long long)(C[d] - used) / freqB[d]);
            }
        }
        if(y_possible == numeric_limits<long long>::max()) y_possible = 0;
        return y_possible;
    };
    
    auto maxA_with_y = [&](long long y) -> long long {
        long long x_possible = numeric_limits<long long>::max();
        for (int d = 0; d < 10; d++){
            long long used = y * (long long)freqB[d];
            if (used > C[d]) return -1;
            if (freqA[d] > 0) {
                x_possible = min(x_possible, (long long)(C[d] - used) / freqA[d]);
            }
        }
        if(x_possible == numeric_limits<long long>::max()) x_possible = 0;
        return x_possible;
    };
    
    long long maxA_possible = numeric_limits<long long>::max();
    for (int d = 0; d < 10; d++){
        if (freqA[d] > 0)
            maxA_possible = min(maxA_possible, (long long)C[d] / freqA[d]);
    }
    if (maxA_possible == numeric_limits<long long>::max())
        maxA_possible = 0;
    
    for (long long x = 0; x <= maxA_possible; x++){
        long long y = maxB_with_x(x);
        if (y < 0) continue;
        bestTotal = max(bestTotal, x + y);
    }
    
    long long maxB_possible = numeric_limits<long long>::max();
    for (int d = 0; d < 10; d++){
        if (freqB[d] > 0)
            maxB_possible = min(maxB_possible, (long long)C[d] / freqB[d]);
    }
    if (maxB_possible == numeric_limits<long long>::max())
        maxB_possible = 0;
    
    for (long long y = 0; y <= maxB_possible; y++){
        long long x = maxA_with_y(y);
        if (x < 0) continue;
        bestTotal = max(bestTotal, x + y);
    }
    
    cout << bestTotal << endl;
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

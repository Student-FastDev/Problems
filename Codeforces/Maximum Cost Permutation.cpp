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
    vector<int> P(N);
    int zerosCount = 0;
    vector<bool> isPresent(N + 1, false);
    
    for(int i = 0; i < N; ++i) {
        cin >> P[i];
        if (P[i] == 0) {
            zerosCount++;
        } else {
            isPresent[P[i]] = true;
        }
    }

    int missingNumber = -1;
    if (zerosCount == 1) {
        for(int i = 1; i <= N; ++i) {
            if (!isPresent[i]) {
                missingNumber = i;
                break;
            }
        }
    }

    int minPrefixLen = N;
    for(int i = 0; i < N; ++i) {
        int targetValue = i + 1;
        int currentValue = P[i];
        bool canBreak = false;

        if (currentValue != 0) {
            if (currentValue != targetValue) {
                canBreak = true;
            } else {
                canBreak = false;
            }
        } else {
            if (zerosCount > 1) {
                canBreak = true;
            } else {
                if (missingNumber != targetValue) {
                    canBreak = true;
                } else {
                    canBreak = false;
                }
            }
        }

        if (canBreak) {
            minPrefixLen = i;
            break;
        }
    }

    int minSuffixLen = N;
    for(int i = 0; i < N; ++i) {
        int indexToCheck = N - 1 - i;
        int targetValue = N - i;
        int currentValue = P[indexToCheck];
        
        bool canBreak = false;
        if (currentValue != 0) {
            if (currentValue != targetValue) {
                canBreak = true;
            } else {
                canBreak = false;
            }
        } else {
            if (zerosCount > 1) {
                canBreak = true;
            } else {
                if (missingNumber != targetValue) {
                    canBreak = true;
                } else {
                    canBreak = false;
                }
            }
        }

        if (canBreak) {
            minSuffixLen = i;
            break;
        }
    }

    cout << max(0, N - minPrefixLen - minSuffixLen) << endl;
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
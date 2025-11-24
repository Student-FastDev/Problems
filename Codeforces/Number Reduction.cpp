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

ll N;
vector<ll> goodArray;
vector<int> goodPrimes = {2, 3, 5, 7};

void DFS(ll current, int startIndex) {
    goodArray.push_back(current);
    for (int i = startIndex; i < 4; ++i) {
        if (current <= N / goodPrimes[i]) {
            DFS(current * goodPrimes[i], i);
        }
    }
}

void solveTestCase() {
    cin >> N;
    DFS(1, 0);
    
    sort(all(goodArray));
    int M = size(goodArray);
    vector<bool> isValid(M, false);

    if (M > 0 && goodArray[0] == 1) isValid[0] = true;

    int validCount = 0;
    if (M > 0 && isValid[0]) validCount++;

    for (int i = 1; i < M; ++i) {
        ll value = goodArray[i];
        ll temporary = value;
        bool canReduce = false;
        int seenDigitsMask = 0;

        while (temporary > 0) {
            int d = temporary % 10;
            temporary /= 10;

            if (d <= 1) continue;
            if ((seenDigitsMask >> d) & 1) continue;
            seenDigitsMask |= (1 << d);

            if (value % d == 0) {
                ll nextValue = value / d;
                
                auto iterator = lower_bound(goodArray.begin(), goodArray.begin() + i, nextValue);
                if (iterator != goodArray.begin() + i && *iterator == nextValue) {
                    int idx = (int)(iterator - goodArray.begin());
                    if (isValid[idx]) {
                        canReduce = true;
                        break;
                    }
                }
            }
        }

        if (canReduce) {
            isValid[i] = true;
            validCount++;
        }
    }
    cout << validCount << endl;
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

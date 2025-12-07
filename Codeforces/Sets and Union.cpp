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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N;
    cin >> N;

    vector<vector<int>> setsOfIntegers(N);
    set<int> universalSet;

    for (int i = 0; i < N; ++i) {
        int K;
        cin >> K;
        setsOfIntegers[i].resize(K);
        for (int j = 0; j < K; ++j) {
            cin >> setsOfIntegers[i][j];
            universalSet.insert(setsOfIntegers[i][j]);
        }
    }

    int maximumSize = 0;

    for (int excludedElement : universalSet) {
        set<int> currentUnionSet;
        for (int i = 0; i < N; ++i) {
            bool hasExcludedElement = false;
            for (int element : setsOfIntegers[i]) {
                if (element == excludedElement) {
                    hasExcludedElement = true;
                    break;
                }
            }

            if (!hasExcludedElement) {
                for (int element : setsOfIntegers[i]) {
                    currentUnionSet.insert(element);
                }
            }
        }

        if ((int)size(currentUnionSet) > maximumSize) {
            maximumSize = (int)size(currentUnionSet);
        }
    }

    cout << maximumSize << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
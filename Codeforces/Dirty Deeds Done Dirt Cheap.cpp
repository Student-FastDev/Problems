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

struct Element {
    int valueA;
    int valueB;
    int originalIndex;
};

void solveTestCase() {
    int N;
    cin >> N;

    vector<Element> increasingPairs;
    vector<Element> decreasingPairs;

    for(int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        if (a < b) {
            increasingPairs.push_back({a, b, i + 1});
        } else {
            decreasingPairs.push_back({a, b, i + 1});
        }
    }

    if (size(increasingPairs) > size(decreasingPairs)) {
        sort(all(increasingPairs), [](const Element& p1, const Element& p2) {
            return p1.valueB > p2.valueB;
        });
        cout << size(increasingPairs) << endl;
        for(int i = 0; i < size(increasingPairs); ++i) {
            cout << increasingPairs[i].originalIndex << (i == size(increasingPairs) - 1 ? "" : " ");
        }
        cout << endl;
    } else {
        sort(all(decreasingPairs), [](const Element& p1, const Element& p2) {
            return p1.valueB < p2.valueB;
        });
        cout << size(decreasingPairs) << endl;
        for(int i = 0; i < size(decreasingPairs); ++i) {
            cout << decreasingPairs[i].originalIndex << (i == size(decreasingPairs) - 1 ? "" : " ");
        }
        cout << endl;
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
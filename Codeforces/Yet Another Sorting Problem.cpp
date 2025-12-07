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

class BinaryIndexedTree {
    int maximumIndex;
    vector<int> treeArray;

public:
    BinaryIndexedTree(int N) : maximumIndex(N), treeArray(N + 1, 0) {}

    void addValue(int index, int delta) {
        while (index <= maximumIndex) {
            treeArray[index] += delta;
            index += index & (-index);
        }
    }

    int queryPrefix(int index) {
        int sumValue = 0;
        while (index > 0) {
            sumValue += treeArray[index];
            index -= index & (-index);
        }
        return sumValue;
    }
};

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    vector<int> frequencyArray(N + 1, 0);
    bool hasDuplicates = false;
    for(int value : A) {
        frequencyArray[value]++;
        if(frequencyArray[value] > 1) {
            hasDuplicates = true;
        }
    }

    if(hasDuplicates) {
        cout << "YES" << endl;
        return;
    }

    BinaryIndexedTree bit(N);
    ll inversionCount = 0;

    for(int i = 0; i < N; ++i) {
        int value = A[i];
        int countSmaller = bit.queryPrefix(value);
        int countGreater = i - countSmaller;
        inversionCount += countGreater;
        bit.addValue(value, 1);
    }

    if(inversionCount % 2 == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
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
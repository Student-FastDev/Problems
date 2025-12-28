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

int N;
vector<int> A;

void printRightAssociation(int leftIndex, int rightIndex) {
    for (int i = leftIndex; i < rightIndex; ++i) cout << "(" << A[i] << "->";
    cout << A[rightIndex];
    for (int i = leftIndex; i < rightIndex; ++i) cout << ")";
}

void solveTestCase() {
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    if (A[N - 1] == 1) {
        cout << "NO" << endl;
        return;
    }

    if (N == 1) {
        cout << "YES" << endl << "0" << endl;
        return;
    }

    if (A[N - 2] == 1) {
        cout << "YES" << endl;
        cout << "(";
        printRightAssociation(0, N - 2);
        cout << ")->" << A[N - 1] << endl;
        return;
    }

    int firstZeroIndex = -1;
    for (int i = 0; i < N - 2; ++i) {
        if (A[i] == 0) {
            firstZeroIndex = i;
            break;
        }
    }

    if (firstZeroIndex == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << "((";
        printRightAssociation(0, firstZeroIndex);
        cout << ")->(";
        printRightAssociation(firstZeroIndex + 1, N - 2);
        cout << "))->" << A[N - 1] << endl;
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
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

int getValue(char c) {
    if (c == 'A') return 0;
    if (c == 'G') return 1;
    if (c == 'S') return 2;
    return 0;
}

ll calculateCost(int x, int y, const vector<int>& A, const vector<int>& B) {
    vector<int> firstArray;
    int countX = 0;
    for (int value : A) {
        if (value == x) {
            countX++;
        } else if (value == y) {
            firstArray.push_back(countX);
        }
    }

    vector<int> secondArray;
    countX = 0;
    for (int value : B) {
        if (value == x) {
            countX++;
        } else if (value == y) {
            secondArray.push_back(countX);
        }
    }

    ll finalCost = 0;
    for (size_t i = 0; i < size(firstArray); ++i) {
        finalCost += abs(firstArray[i] - secondArray[i]);
    }
    
    return finalCost;
}

void solveTestCase() {
    int N;
    cin >> N;

    string inputString, targetString;
    cin >> inputString >> targetString;

    vector<int> A(N), B(N);
    vector<int> countA(3, 0), countB(3, 0);

    for(int i = 0; i < N; i++) {
        A[i] = (i + getValue(inputString[i])) % 3;
        countA[A[i]]++;

        B[i] = (i + getValue(targetString[i])) % 3;
        countB[B[i]]++;
    }

    if (countA[0] != countB[0] || countA[1] != countB[1] || countA[2] != countB[2]) {
        cout << "Nie" << endl;
        return;
    }

    cout << "Tak" << endl;

    ll totalOperations = 0;
    
    totalOperations += calculateCost(0, 1, A, B);
    totalOperations += calculateCost(1, 2, A, B);
    totalOperations += calculateCost(2, 0, A, B);

    cout << totalOperations << endl;
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

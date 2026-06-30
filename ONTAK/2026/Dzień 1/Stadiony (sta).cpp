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
const ll MOD = 694202137; // 998244353

const ll MAX_T = 5e5+67;

struct Fenwick {
    ll treeArray[MAX_T];
    void addTree(int i, ll value) {
        value %= MOD;
        if (value < 0) value += MOD;
        for (; i <= MAX_T; i += i & -i) {
            treeArray[i] += value;
            if (treeArray[i] >= MOD) treeArray[i] -= MOD;
        }
    }
    ll queryTree(int i) {
        ll currentSum = 0;
        for (; i > 0; i -= i & -i) {
            currentSum += treeArray[i];
            if (currentSum >= MOD) currentSum -= MOD;
        }
        return currentSum;
    }
} countTree, countX, countT, countMixed;

void solveTestCase() {
    int N;
    cin >> N;

    vector<pii> stadionArray(N);
    for (int i = 0; i < N; i++) cin >> stadionArray[i].first >> stadionArray[i].second;
    sort(all(stadionArray));

    ll finalAnswer = 0;
    for (int i = 0; i < N; i++) {
        ll currentX = stadionArray[i].first;
        ll currentT = stadionArray[i].second;
        
        ll trimmedCurrentX = currentX % MOD;
        ll trimmedCurrentT = currentT % MOD;
        int indexT = currentT + 1;

        ll smallerCount = countTree.queryTree(indexT);
        ll smallerSumX = countX.queryTree(indexT);
        ll smallerSumT = countT.queryTree(indexT);
        ll smallerSumMixed = countMixed.queryTree(indexT);

        ll totalCount = countTree.queryTree(MAX_T);
        ll totalSumX = countX.queryTree(MAX_T);
        ll totalSumT = countT.queryTree(MAX_T);
        ll totalSumMixed = countMixed.queryTree(MAX_T);

        ll biggerCount = (totalCount - smallerCount + MOD) % MOD;
        ll biggerSumX = (totalSumX - smallerSumX + MOD) % MOD;
        ll biggerSumT = (totalSumT - smallerSumT + MOD) % MOD;
        ll biggerSumMixed = (totalSumMixed - smallerSumMixed + MOD) % MOD;

        // (x_j - x_i)*(t_j - t_i) = x_j*t_j - x_j*t_i - x_i*t_j + x_i*t_i
        ll firstTerm = ((smallerCount * trimmedCurrentX) % MOD) * trimmedCurrentT % MOD;
        ll secondTerm = (smallerSumT * trimmedCurrentX) % MOD;
        ll thirdTerm = (smallerSumX * trimmedCurrentT) % MOD;
        ll fourthTerm = smallerSumMixed;

        ll firstCase = firstTerm;
        firstCase = (firstCase - secondTerm + MOD) % MOD;
        firstCase = (firstCase - thirdTerm + MOD) % MOD;
        firstCase = (firstCase + fourthTerm) % MOD;

        // (x_j - x_i)*(t_i - t_j) = x_j*t_i - x_j*t_j - x_i*t_i + x_i*t_j
        firstTerm = (biggerSumT * trimmedCurrentX) % MOD;
        secondTerm = ((biggerCount * trimmedCurrentX) % MOD) * trimmedCurrentT % MOD;
        thirdTerm = biggerSumMixed;
        fourthTerm = (biggerSumX * trimmedCurrentT) % MOD;

        ll secondCase = firstTerm;
        secondCase = (secondCase - secondTerm + MOD) % MOD;
        secondCase = (secondCase - thirdTerm + MOD) % MOD;
        secondCase = (secondCase + fourthTerm) % MOD;

        finalAnswer = (finalAnswer + firstCase + secondCase) % MOD;

        countTree.addTree(indexT, 1);
        countX.addTree(indexT, trimmedCurrentX);
        countT.addTree(indexT, trimmedCurrentT);
        countMixed.addTree(indexT, (trimmedCurrentX * trimmedCurrentT) % MOD);
    }

    cout << finalAnswer << endl;
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
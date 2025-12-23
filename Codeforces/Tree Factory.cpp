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
vector<vector<int>> neighbourList;
vector<int> targetParent;
vector<int> heightArray;
vector<int> bambooSequence;
vector<int> currentParent;

void calculateHeight(int u) {
    heightArray[u] = 1;
    for (int v : neighbourList[u]) {
        calculateHeight(v);
        heightArray[u] = max(heightArray[u], heightArray[v] + 1);
    }
}

void buildBamboo(int u) {
    bambooSequence.push_back(u);
    sort(all(neighbourList[u]), [&](int a, int b) {
        return heightArray[a] < heightArray[b];
    });
    for (int v : neighbourList[u]) {
        buildBamboo(v);
    }
}

void solveTestCase() {
    cin >> N;

    neighbourList.assign(N, vector<int>());
    targetParent.assign(N, 0);
    heightArray.assign(N, 0);
    bambooSequence.clear();

    for (int i = 1; i < N; ++i) {
        int p;
        cin >> p;
        targetParent[i] = p;
        neighbourList[p].push_back(i);
    }

    calculateHeight(0);
    buildBamboo(0);

    for (int i = 0; i < N; ++i) {
        cout << bambooSequence[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    currentParent.assign(N, 0);
    for (int i = 1; i < N; ++i) {
        currentParent[bambooSequence[i]] = bambooSequence[i-1];
    }

    vector<int> operations;
    for (int u : bambooSequence) {
        if (u == 0) continue;
        while (currentParent[u] != targetParent[u]) {
            operations.push_back(u);
            currentParent[u] = currentParent[currentParent[u]];
        }
    }

    cout << size(operations) << endl;
    for (int i = 0; i < size(operations); ++i) {
        cout << operations[i] << (i == size(operations) - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
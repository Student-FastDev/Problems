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

void solveTestCase() {
    int N;
    cin >> N;
    vector<vector<int>> neighbourList(N + 1);
    vector<int> nodeDegree(N + 1, 0);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
        nodeDegree[u]++;
        nodeDegree[v]++;
    }

    string nodeValues;
    cin >> nodeValues;

    int leafZeroCount = 0;
    int leafOneCount = 0;
    int leafQuestionCount = 0;
    int internalQuestionCount = 0;

    for (int i = 2; i <= N; ++i) {
        char currentValue = nodeValues[i - 1];
        if (nodeDegree[i] == 1) {
            if (currentValue == '0') leafZeroCount++;
            else if (currentValue == '1') leafOneCount++;
            else leafQuestionCount++;
        } else {
            if (currentValue == '?') internalQuestionCount++;
        }
    }

    if (nodeValues[0] != '?') {
        int mismatchCount = (nodeValues[0] == '0' ? leafOneCount : leafZeroCount);
        cout << mismatchCount + (leafQuestionCount + 1) / 2 << endl;
    } else {
        if (leafZeroCount == leafOneCount) {
            if (internalQuestionCount % 2 == 1) {
                cout << leafZeroCount + (leafQuestionCount + 1) / 2 << endl;
            } else {
                cout << leafZeroCount + leafQuestionCount / 2 << endl;
            }
        } else {
            cout << max(leafZeroCount, leafOneCount) + leafQuestionCount / 2 << endl;
        }
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
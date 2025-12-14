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

vector<vector<pii>> neighbourList;
vector<ll> edgeWeights;
vector<ll> contribution;
vector<int> subTreeSize;
int numberOfCities;

void dfs(int U, int P) {
    subTreeSize[U] = 1;
    for(auto& edge : neighbourList[U]) {
        int V = edge.first;
        int indexNumber = edge.second;
        if(V != P) {
            dfs(V, U);
            subTreeSize[U] += subTreeSize[V];
            contribution[indexNumber] = (ll)subTreeSize[V] * (numberOfCities - subTreeSize[V]);
        }
    }
}

void solveTestCase() {
    cin >> numberOfCities;

    neighbourList.assign(numberOfCities + 1, vector<pii>());
    edgeWeights.resize(numberOfCities);
    contribution.resize(numberOfCities);
    subTreeSize.resize(numberOfCities + 1);

    for(int i = 1; i < numberOfCities; ++i) {
        int U, V;
        ll W;
        cin >> U >> V >> W;
        neighbourList[U].push_back({V, i});
        neighbourList[V].push_back({U, i});
        edgeWeights[i] = W;
    }

    dfs(1, 0);

    ll currentTotalDistance = 0;
    for(int i = 1; i < numberOfCities; ++i) {
        currentTotalDistance += contribution[i] * edgeWeights[i];
    }

    int Q;
    cin >> Q;

    cout << fixed << setprecision(10);
    double denominator = (double)numberOfCities * (numberOfCities - 1);

    while(Q--) {
        int R;
        ll W;
        cin >> R >> W;

        currentTotalDistance -= contribution[R] * edgeWeights[R];
        edgeWeights[R] = W;
        currentTotalDistance += contribution[R] * edgeWeights[R];

        double expectedValue = (double)currentTotalDistance * 6.0 / denominator;
        cout << expectedValue << endl;
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
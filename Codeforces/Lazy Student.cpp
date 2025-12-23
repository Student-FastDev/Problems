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

struct Edge {
    int weight;
    int isIncludedInMST;
    int originalIndex;

    bool operator<(const Edge& other) const {
        if (weight != other.weight) return weight < other.weight;
        return isIncludedInMST > other.isIncludedInMST;
    }
};

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edgeList(M);
    for (int i = 0; i < M; ++i) {
        cin >> edgeList[i].weight >> edgeList[i].isIncludedInMST;
        edgeList[i].originalIndex = i;
    }

    sort(all(edgeList));

    vector<pii> resultEdges(M);
    int currentMSTEndpoint = 1;
    int nextNonMSTU = 1;
    int nextNonMSTV = 3;

    for (const auto& currentEdge : edgeList) {
        if (currentEdge.isIncludedInMST) {
            resultEdges[currentEdge.originalIndex] = {currentMSTEndpoint, currentMSTEndpoint + 1};
            currentMSTEndpoint++;
        } else {
            if (nextNonMSTV > currentMSTEndpoint) {
                cout << -1 << endl;
                return;
            }
            resultEdges[currentEdge.originalIndex] = {nextNonMSTU, nextNonMSTV};
            nextNonMSTU++;
            if (nextNonMSTU == nextNonMSTV - 1) {
                nextNonMSTU = 1;
                nextNonMSTV++;
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        cout << resultEdges[i].first << " " << resultEdges[i].second << endl;
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
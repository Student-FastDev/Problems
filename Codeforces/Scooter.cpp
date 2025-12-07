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
    int to;
    int id;
    int typeRequirements;
    int typeProvides;
};

vector<Edge> neighbourList[3];
vector<Edge> pathEdges;

int getType(char c) {
    if (c == 'M') return 1;
    if (c == 'C') return 2;
    return 0;
}

void DFS(int u) {
    while (!neighbourList[u].empty()) {
        Edge edge = neighbourList[u].back();
        neighbourList[u].pop_back();
        DFS(edge.to);
        pathEdges.push_back(edge);
    }
}

void solveTestCase() {
    int N;
    cin >> N;
    
    string stringC, stringP;
    cin >> stringC >> stringP;

    vector<Edge> optionalM, optionalC;
    int inDegree[3] = {0}, outDegree[3] = {0};
    bool hasMandatory = false;

    for (int i = 0; i < N; ++i) {
        int need = getType(stringC[i]);
        int have = getType(stringP[i]);
        if (need == have) continue;

        if (need != 0) {
            neighbourList[need].push_back({have, i + 1, need, have});
            outDegree[need]++;
            inDegree[have]++;
            hasMandatory = true;
        } else {
            if (have == 1) optionalM.push_back({have, i + 1, need, have});
            else if (have == 2) optionalC.push_back({have, i + 1, need, have});
        }
    }

    int requiredM = max(0, outDegree[1] - inDegree[1]);
    int requiredC = max(0, outDegree[2] - inDegree[2]);

    if (hasMandatory && requiredM == 0 && requiredC == 0) {
        if (!optionalM.empty()) requiredM++;
        else requiredC++;
    }

    for (int i = 0; i < requiredM; ++i) {
        neighbourList[0].push_back(optionalM.back());
        optionalM.pop_back();
    }
    for (int i = 0; i < requiredC; ++i) {
        neighbourList[0].push_back(optionalC.back());
        optionalC.pop_back();
    }

    DFS(0);
    reverse(pathEdges.begin(), pathEdges.end());

    vector<string> operationArray;
    for (auto& edge : pathEdges) {
        operationArray.push_back("DRIVE " + to_string(edge.id));

        if (edge.typeRequirements != 0) operationArray.push_back("DROPOFF");
        if (edge.typeProvides != 0) operationArray.push_back("PICKUP");
    }

    cout << size(operationArray) << endl;
    for (string& s : operationArray) {
        cout << s << endl;
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
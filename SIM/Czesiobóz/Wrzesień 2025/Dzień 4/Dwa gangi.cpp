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

struct DSU {
    vector<int> parentArray;
    vector<int> bipartiteColor; 
    vector<int> subSize;

    DSU(int N) {
        parentArray.resize(N + 1);
        iota(parentArray.begin(), parentArray.end(), 0);
        bipartiteColor.assign(N + 1, 0);
        subSize.assign(N + 1, 1);
    }

    pii findVertex(int i) {
        if (parentArray[i] == i) {
            return {i, 0};
        }
        auto [root, rootColor] = findVertex(parentArray[i]);
        parentArray[i] = root;

        bipartiteColor[i] ^= rootColor;
        
        return {parentArray[i], bipartiteColor[i]};
    }

    void uniteGroups(int a, int b) {
        auto [rootA, colorA] = findVertex(a);
        auto [rootB, colorB] = findVertex(b);

        if (rootA != rootB) {
            if (subSize[rootA] < subSize[rootB]) {
                swap(rootA, rootB);
            }
            parentArray[rootB] = rootA;
            subSize[rootA] += subSize[rootB];
            bipartiteColor[rootB] = colorA ^ colorB ^ 1;
        }
    }
};

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    DSU dsuStructure(N);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;

        auto [rootU, colorU] = dsuStructure.findVertex(u);
        auto [rootV, colorV] = dsuStructure.findVertex(v);

        if (rootU == rootV) {
            if (colorU == colorV) {
                cout << "NIE" << endl;
            } else {
                cout << "TAK" << endl;
            }
        } else {
            cout << "TAK" << endl;
            dsuStructure.uniteGroups(u, v);
        }
    }

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

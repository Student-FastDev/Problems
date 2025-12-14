// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){{return o<<'('<<p.first<<", "<<p.second <<')';}}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){{o<<'{{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}}';}}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){{((cerr<<$<<"; "),...)<<endl;}}(x);
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
const ll MAX_N = 1e5+5;

map<vector<int>, int> canonicalIds;

int getCanonicalId(vector<int>& vec) {
    if (canonicalIds.find(vec) == canonicalIds.end()) {
        canonicalIds[vec] = size(canonicalIds);
    }
    return canonicalIds[vec];
}

int getTreeHash(int u, int p, const vector<vector<int>>& neighbourList) {
    vector<int> childHashes;
    for (int v : neighbourList[u]) {
        if (v != p) {
            childHashes.push_back(getTreeHash(v, u, neighbourList));
        }
    }
    sort(all(childHashes));
    return getCanonicalId(childHashes);
}

void findCentroids(int u, int p, int n, const vector<vector<int>>& neighbourList, vector<int>& subTreeSize, vector<int>& centroids) {
    subTreeSize[u] = 1;
    bool isCentroid = true;
    for (int v : neighbourList[u]) {
        if (v != p) {
            findCentroids(v, u, n, neighbourList, subTreeSize, centroids);
            subTreeSize[u] += subTreeSize[v];
            if (subTreeSize[v] > n / 2) isCentroid = false;
        }
    }
    if (n - subTreeSize[u] > n / 2) isCentroid = false;
    if (isCentroid) centroids.push_back(u);
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<vector<int>> neighbourList1(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList1[u].push_back(v);
        neighbourList1[v].push_back(u);
    }

    vector<vector<int>> neighbourList2(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList2[u].push_back(v);
        neighbourList2[v].push_back(u);
    }

    vector<int> subTreeSize1(N + 1);
    vector<int> centroids1;
    findCentroids(1, 0, N, neighbourList1, subTreeSize1, centroids1);

    vector<int> subTreeSize2(N + 1);
    vector<int> centroids2;
    findCentroids(1, 0, N, neighbourList2, subTreeSize2, centroids2);

    if (size(centroids1) != size(centroids2)) {
        cout << "NIE" << endl;
        return;
    }

    vector<int> hashes1;
    for (int c : centroids1) {
        hashes1.push_back(getTreeHash(c, 0, neighbourList1));
    }
    sort(all(hashes1));

    vector<int> hashes2;
    for (int c : centroids2) {
        hashes2.push_back(getTreeHash(c, 0, neighbourList2));
    }
    sort(all(hashes2));

    if (hashes1 == hashes2) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
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
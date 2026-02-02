// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define size(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define endl '\n';

const ll MOD = 1e9 + 7;
const ll MAX_N = 200005;

struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int parentArray[MAX_N];

int findSet(int v) {
    if (v == parentArray[v]) return v;
    return parentArray[v] = findSet(parentArray[v]);
}

void unionSets(int u, int v) {
    u = findSet(u);
    v = findSet(v);
    if (u != v) parentArray[v] = u;
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edgesArray(M);
    for(int i = 0; i < M; i++) cin >> edgesArray[i].u >> edgesArray[i].v >> edgesArray[i].w;
    sort(all(edgesArray));

    for(int i = 1; i <= N; i++) parentArray[i] = i;

    ll finalAnswer = 1;
    int i = 0;
    while(i < M) {
        int j = i;
        while(j < M && edgesArray[j].w == edgesArray[i].w) j++;

        vector<int> candidateArray;
        for(int k = i; k < j; k++) if(findSet(edgesArray[k].u) != findSet(edgesArray[k].v)) candidateArray.push_back(k);

        if(size(candidateArray) == 1) {
            unionSets(edgesArray[candidateArray[0]].u, edgesArray[candidateArray[0]].v);
        } else if(size(candidateArray) == 2) {
            int firstU = findSet(edgesArray[candidateArray[0]].u);
            int firstV = findSet(edgesArray[candidateArray[0]].v);
            if(firstU > firstV) swap(firstU, firstV);

            int secondU = findSet(edgesArray[candidateArray[1]].u);
            int secondV = findSet(edgesArray[candidateArray[1]].v);
            if(secondU > secondV) swap(secondU, secondV);

            if(firstU == secondU && firstV == secondV) {
                finalAnswer = (finalAnswer * 2) % MOD;
                unionSets(edgesArray[candidateArray[0]].u, edgesArray[candidateArray[0]].v);
            } else {
                unionSets(edgesArray[candidateArray[0]].u, edgesArray[candidateArray[0]].v);
                unionSets(edgesArray[candidateArray[1]].u, edgesArray[candidateArray[1]].v);
            }
        }
        i = j;
    }

    int componentsCount = 0;
    for(int k = 1; k <= N; k++) if(parentArray[k] == k) componentsCount++;

    if(componentsCount > 1) {
        cout << 0 << endl;
        return;
    }
    cout << finalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
}

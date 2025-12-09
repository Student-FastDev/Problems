// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct Tile {
    int X, Y, currentType, ID;
};

struct Edge {
    int to;
    char direction;
};

vector<Tile> tilesArray;
vector<vector<Edge>> neighbourList;
vector<bool> isVisited;
vector<pii> matchedPairs;

int performDFS(int U, int p, char typeP) {
    isVisited[U] = true;

    vector<int> remainingH; 
    vector<int> remainingV; 

    for (auto& edge : neighbourList[U]) {
        if (edge.to == p) continue;
        if (isVisited[edge.to]) continue; 

        int currentResult = performDFS(edge.to, U, edge.direction);
        if (currentResult != 0) {
            if (edge.direction == 'H') remainingH.push_back(currentResult);
            else remainingV.push_back(currentResult);
        }
    }

    for (int i = 0; i + 1 < size(remainingH); i += 2) matchedPairs.push_back({remainingH[i], remainingH[i+1]});
    for (int i = 0; i + 1 < size(remainingV); i += 2) matchedPairs.push_back({remainingV[i], remainingV[i+1]});

    int nodeH = (size(remainingH) % 2 == 1) ? remainingH.back() : 0;
    int nodeV = (size(remainingV) % 2 == 1) ? remainingV.back() : 0;

    if (nodeH == 0 && nodeV == 0) {
        return U;
    }

    if (nodeH != 0 && nodeV == 0) {
        matchedPairs.push_back({U, nodeH});
        return 0;
    }

    if (nodeH == 0 && nodeV != 0) {
        matchedPairs.push_back({U, nodeV});
        return 0;
    }

    if (typeP == 'H') {
        matchedPairs.push_back({U, nodeV});
        return nodeH;
    } else {
        matchedPairs.push_back({U, nodeH});
        return nodeV;
    }
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    tilesArray.resize(N);
    neighbourList.assign(N + 1, vector<Edge>());
    isVisited.assign(N + 1, false);
    matchedPairs.clear();

    for (int i = 0; i < N; i++) {
        cin >> tilesArray[i].X >> tilesArray[i].Y >> tilesArray[i].currentType;
        tilesArray[i].ID = i + 1;
    }

    sort(all(tilesArray), [](const Tile& a, const Tile& b) {
        if (a.Y != b.Y) return a.Y < b.Y;
        return a.X < b.X;
    });

    for (int i = 0; i < N - 1; i++) {
        if (tilesArray[i].Y == tilesArray[i+1].Y && tilesArray[i].currentType == tilesArray[i+1].currentType) {
            int U = tilesArray[i].ID;
            int V = tilesArray[i+1].ID;
            neighbourList[U].push_back({V, 'H'});
            neighbourList[V].push_back({U, 'H'});
        }
    }

    sort(all(tilesArray), [](const Tile& a, const Tile& b) {
        if (a.X != b.X) return a.X < b.X;
        return a.Y < b.Y;
    });

    for (int i = 0; i < N - 1; i++) {
        if (tilesArray[i].X == tilesArray[i + 1].X && tilesArray[i].currentType == tilesArray[i + 1].currentType) {
            int U = tilesArray[i].ID;
            int V = tilesArray[i+1].ID;
            neighbourList[U].push_back({V, 'V'});
            neighbourList[V].push_back({U, 'V'});
        }
    }

    for (int i = 1; i <= N; i++) {
        if (!isVisited[i]) {
            int remainder = performDFS(i, -1, ' ');
            if (remainder != 0) {
                cout << "NO" << endl;
                return;
            }
        }
    }

    cout << "YES" << endl;
    for (auto& p : matchedPairs) {
        cout << p.first << " " << p.second << endl;
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

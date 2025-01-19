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

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

static const int SWAP_ACTION = 1;
static const int MOVE_ACTION = 2;

vector<array<int, 3>> actions;
vector<int> visited, stIndex;
vector<int> C;
vector<int> dfsStack;

void addSwap(int x, int y) {
    actions.push_back({SWAP_ACTION, x, y});
}

void addMove(int x, int y) {
    actions.push_back({MOVE_ACTION, x, y});
}

void DFS(int u) {
    if (visited[u] == 2) {
        return;
    }
    if (visited[u] == 1) {
        int startPos = stIndex[u];
        int cycleSize = (int)dfsStack.size() - startPos;
        if (cycleSize > 1) {
            int first = dfsStack[startPos];
            for (int i = startPos + 1; i < (int)dfsStack.size(); i++) {
                addSwap(first, dfsStack[i]);
            }
        }
        for (int i = startPos; i < (int)dfsStack.size(); i++) {
            int node = dfsStack[i];
            visited[node] = 2;
        }
        dfsStack.resize(startPos);
        return;
    }
    visited[u] = 1;
    stIndex[u] = (int)dfsStack.size();
    dfsStack.push_back(u);
    int nxt = C[u];
    if (visited[nxt] != 2) {
        DFS(nxt);
        if (visited[u] == 1) {
            if (C[u] != u) {
                addMove(C[u], u);
            }
            visited[u] = 2;
            dfsStack.pop_back();
        }
    } else {
        if (visited[u] == 1) {
            if (C[u] != u) {
                addMove(C[u], u);
            }
            visited[u] = 2;
            dfsStack.pop_back();
        }
    }
}

void solveTestCase() {
    int N;
    cin >> N;
    C.resize(N+1);

    for(int i = 1; i <= N; i++){
        cin >> C[i];
    }

    visited.assign(N+1, 0);
    stIndex.assign(N+1, -1);

    for(int i=1; i<=N; i++){
        if(visited[i] == 0){
            dfsStack.clear();
            DFS(i);
        }
    }

    cout << actions.size() << "\n";
    for(auto &act : actions){
        if(act[0] == SWAP_ACTION){
            cout << "1 " << act[1] << " " << act[2] << "\n";
        } else {
            cout << "2 " << act[1] << " " << act[2] << "\n";
        }
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

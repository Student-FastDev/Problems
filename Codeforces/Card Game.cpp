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

const int MAX_VALUE = 200005;
vector<bool> isPrime(MAX_VALUE, true);

void sieve() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAX_VALUE; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAX_VALUE; j += i)
                isPrime[j] = false;
        }
    }
}

struct Edge {
    int to;
    ll capacity;
    ll flow;
    int reverseEdgeIndex;
};

struct Dinic {
    vector<vector<Edge>> neighbourList;
    vector<int> levelArray;
    vector<int> edgeIndex;
    int n;
    int source, sink;

    Dinic(int nodes, int sourceNode, int sinkNode) : n(nodes), source(sourceNode), sink(sinkNode) {
        neighbourList.resize(n);
        levelArray.resize(n);
        edgeIndex.resize(n);
    }

    void addEdge(int from, int to, ll cap) {
        neighbourList[from].push_back({to, cap, 0, (int)size(neighbourList[to])});
        neighbourList[to].push_back({from, 0, 0, (int)size(neighbourList[from]) - 1});
    }

    bool bfs() {
        fill(all(levelArray), -1);
        levelArray[source] = 0;
        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& edge : neighbourList[v]) {
                if (edge.capacity - edge.flow > 0 && levelArray[edge.to] == -1) {
                    levelArray[edge.to] = levelArray[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return levelArray[sink] != -1;
    }

    ll dfs(int v, ll pushed) {
        if (pushed == 0 || v == sink) return pushed;
        for (int& cid = edgeIndex[v]; cid < size(neighbourList[v]); ++cid) {
            auto& edge = neighbourList[v][cid];
            if (levelArray[v] + 1 != levelArray[edge.to] || edge.capacity - edge.flow == 0) continue;
            ll tr = dfs(edge.to, min(pushed, edge.capacity - edge.flow));
            if (tr == 0) continue;
            edge.flow += tr;
            neighbourList[edge.to][edge.reverseEdgeIndex].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll maxFlow() {
        ll flow = 0;
        while (bfs()) {
            fill(all(edgeIndex), 0);
            while (ll pushed = dfs(source, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

struct Card {
    int power, numberValue, level;
};

void solveTestCase() {
    int N, K;
    cin >> N >> K;

    vector<Card> cardsArray(N);
    vector<int> levels;
    for (int i = 0; i < N; ++i) {
        cin >> cardsArray[i].power >> cardsArray[i].numberValue >> cardsArray[i].level;
        levels.push_back(cardsArray[i].level);
    }
    sort(all(levels));
    levels.erase(unique(all(levels)), levels.end());

    auto check = [&](int maxLevel) -> bool {
        vector<Card> ones, odds, evens;
        for (const auto& card : cardsArray) {
            if (card.level > maxLevel) continue;
            if (card.numberValue == 1) ones.push_back(card);
            else if (card.numberValue % 2 != 0) odds.push_back(card);
            else evens.push_back(card);
        }

        auto calculateMaxIndependentSet = [&](const vector<Card>& oddCards, const vector<Card>& evenCards) -> ll {
            int numOdds = size(oddCards);
            int numEvens = size(evenCards);
            int S = 0;
            int T = numOdds + numEvens + 1;
            Dinic dinicSolver(T + 1, S, T);

            ll totalPower = 0;
            for (int i = 0; i < numOdds; ++i) {
                dinicSolver.addEdge(S, i + 1, oddCards[i].power);
                totalPower += oddCards[i].power;
            }
            for (int i = 0; i < numEvens; ++i) {
                dinicSolver.addEdge(numOdds + i + 1, T, evenCards[i].power);
                totalPower += evenCards[i].power;
            }

            for (int i = 0; i < numOdds; ++i) {
                for (int j = 0; j < numEvens; ++j) {
                    if (isPrime[oddCards[i].numberValue + evenCards[j].numberValue]) {
                        dinicSolver.addEdge(i + 1, numOdds + j + 1, INF);
                    }
                }
            }

            return totalPower - dinicSolver.maxFlow();
        };

        if (calculateMaxIndependentSet(odds, evens) >= K) return true;

        if (!ones.empty()) {
            int maxOnePower = 0;
            for (auto& c : ones) maxOnePower = max(maxOnePower, c.power);

            vector<Card> validEvens;
            for (auto& c : evens) {
                if (!isPrime[c.numberValue + 1]) {
                    validEvens.push_back(c);
                }
            }

            if (maxOnePower + calculateMaxIndependentSet(odds, validEvens) >= K) return true;
        }

        return false;
    };

    int low = 0, high = size(levels) - 1;
    int answer = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(levels[mid])) {
            answer = levels[mid];
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    sieve();

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
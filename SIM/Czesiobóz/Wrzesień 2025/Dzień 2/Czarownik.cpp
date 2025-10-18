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

inline int readInt() {
    int c = getchar_unlocked();
    while (c <= 32) c = getchar_unlocked();
    int sign = 1;
    if (c == '-') { sign = -1; c = getchar_unlocked(); }
    int x = 0;
    while (c > 32) {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x * sign;
}
inline long long readLong() {
    int c = getchar_unlocked();
    while (c <= 32) c = getchar_unlocked();
    int sign = 1;
    if (c == '-') { sign = -1; c = getchar_unlocked(); }
    long long x = 0;
    while (c > 32) {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x * sign;
}
inline void writeLL(long long x) {
    if (x == 0) { putc_unlocked('0', stdout); putc_unlocked('\n', stdout); return; }
    if (x < 0) { putc_unlocked('-', stdout); x = -x; }
    char buf[24]; int p = 0;
    while (x) { buf[p++] = char('0' + x % 10); x /= 10; }
    while (p--) putc_unlocked(buf[p], stdout);
    putc_unlocked('\n', stdout);
}

struct Edge { 
    int edgeDestination; int edgeWeight; 
};

int N, M, Q, T;
vector<vector<Edge>> neighbourList;
vector<int> sizeArray;
vector<char> deadArray;
vector<int> parentCentroid;
vector<vector<pair<int,ll>>> centroidsOf;

void sizeDFS(int u, int p) {
    sizeArray[u] = 1;
    for (auto &e : neighbourList[u]) {
        int v = e.edgeDestination;
        if (v == p || deadArray[v]) continue;
        sizeDFS(v, u);
        sizeArray[u] += sizeArray[v];
    }
}
int findCentroid(int u, int p, int total) {
    for (auto &e : neighbourList[u]) {
        int v = e.edgeDestination;
        if (v == p || deadArray[v]) continue;
        if (sizeArray[v] > total / 2) return findCentroid(v, u, total);
    }
    return u;
}
void centroidDistance(int u, int p, int c, ll dist) {
    centroidsOf[u].push_back({c, dist});
    for (auto &e : neighbourList[u]) {
        int v = e.edgeDestination;
        if (v == p || deadArray[v]) continue;
        centroidDistance(v, u, c, dist + e.edgeWeight);
    }
}
void buildCentroid(int entry, int parent) {
    sizeDFS(entry, -1);
    int c = findCentroid(entry, -1, sizeArray[entry]);
    parentCentroid[c] = parent;
    centroidDistance(c, -1, c, 0LL);
    deadArray[c] = 1;
    for (auto &e : neighbourList[c]) {
        int v = e.edgeDestination;
        if (!deadArray[v]) buildCentroid(v, c);
    }
}

struct LazyMinHeap {
    priority_queue<ll, vector<ll>, greater<ll>> insertQueue;
    priority_queue<ll, vector<ll>, greater<ll>> deleteQueue;
    void push(ll x) { insertQueue.push(x); }
    void erase(ll x) { deleteQueue.push(x); }
    ll top() {
        while (!insertQueue.empty() && !deleteQueue.empty() && insertQueue.top() == deleteQueue.top()) {
            insertQueue.pop(); deleteQueue.pop();
        }
        if (insertQueue.empty()) return INF;
        return insertQueue.top();
    }
    bool empty() {
        while (!insertQueue.empty() && !deleteQueue.empty() && insertQueue.top() == deleteQueue.top()) {
            insertQueue.pop(); deleteQueue.pop();
        }
        return insertQueue.empty();
    }
};

struct Spell { 
    int X;
    int A, D;
    int K;
};

void solveTestCase() {
    N = readInt(); M = readInt(); Q = readInt(); T = readInt();
    vector<int> arrayA(M), arrayB(M), arrayW(M);
    arrayA.resize(N-1); arrayB.resize(N-1); arrayW.resize(N-1);
    vector<int> degreeArray(N+1, 0);
    for (int i = 0; i < N-1; ++i) {
        int a = readInt(), b = readInt(), edgeWeight = readInt();
        arrayA[i] = a; arrayB[i] = b; arrayW[i] = edgeWeight;
        degreeArray[a]++; degreeArray[b]++;
    }
    neighbourList.assign(N+1, {});
    for (int i = 1; i <= N; ++i) if (degreeArray[i]) neighbourList[i].reserve(degreeArray[i]);
    for (int i = 0; i < N-1; ++i) {
        neighbourList[arrayA[i]].push_back({arrayB[i], arrayW[i]});
        neighbourList[arrayB[i]].push_back({arrayA[i], arrayW[i]});
    }

    vector<Spell> spellsArray(M);
    vector<vector<int>> spellsByA(max(0, T) + 1);
    for (int i = 0; i < M; ++i) {
        int X = readInt(), A = readInt(), D = readInt(), K = readInt();
        spellsArray[i] = {X, A, D, K};
        if (A >= 0 && A <= T) spellsByA[A].push_back(i);
    }

    vector<pii> queriesArray(Q);
    vector<vector<int>> queriesS(max(0, T) + 1);
    for (int i = 0; i < Q; ++i) {
        int S = readInt(), P = readInt();
        queriesArray[i] = {S, P};
        if (S >= 0 && S <= T) queriesS[S].push_back(i);
    }

    sizeArray.assign(N+1, 0);
    deadArray.assign(N+1, 0);
    parentCentroid.assign(N+1, -1);
    centroidsOf.assign(N+1, {});
    buildCentroid(1, -1);

    vector<LazyMinHeap> heaps(N+1);

    auto addSource = [&](int node, ll weight) {
        for (auto &pair : centroidsOf[node]) {
            int c = pair.first; ll d = pair.second;
            heaps[c].push(weight + d);
        }
    };
    auto removeSource = [&](int node, ll weight) {
        for (auto &pair : centroidsOf[node]) {
            int c = pair.first; ll d = pair.second;
            heaps[c].erase(weight + d);
        }
    };
    auto queryMinimum = [&](int node)->ll {
        ll answer = INF;
        for (auto &pair : centroidsOf[node]) {
            int c = pair.first; ll d = pair.second;
            ll topc = heaps[c].top();
            if (topc < INF/4) answer = min(answer, topc + d);
        }
        return answer;
    };

    vector<vector<pair<int, ll>>> removeAt(max(0, T) + 1);
    if (T >= 0) {
        addSource(1, 0LL);
        if (T-1 >= 0) removeAt[T-1].push_back({1, 0LL});
    }

    vector<ll> postDP(M, INF);
    vector<ll> answers(Q, -1);

    for (int t = T; t >= 0; --t) {
        for (auto &p : removeAt[t]) {
            int city = p.first; ll dpW = p.second;
            if (dpW >= INF / 4) continue;
            removeSource(city, dpW);
        }
        for (int idx : spellsByA[t]) {
            auto &spell = spellsArray[idx];
            ll best = queryMinimum(spell.X);
            if (best >= INF/4) postDP[idx] = INF;
            else postDP[idx] = best + (ll)spell.K;
            if (postDP[idx] < INF/4) {
                addSource(spell.X, postDP[idx]);
                if (spell.D - 1 >= 0) removeAt[spell.D - 1].push_back({spell.X, postDP[idx]});
            }
        }
        for (int o : queriesS[t]) {
            int city = queriesArray[o].second;
            ll best = queryMinimum(city);
            if (best >= INF/4) answers[o] = -1;
            else answers[o] = best;
        }
    }

    for (int i = 0; i < Q; ++i) {
        writeLL(answers[i]);
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

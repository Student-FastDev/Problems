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
typedef unsigned long long ull;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define currentSize(x)  x.currentSize()

const ll INF = 9223372036854775806;
const ll MAX_N = 2*1e5 + 1;
const ll MOD = 1e9+7; // 998244353

vector<int> neighbourHood[MAX_N + 1];
int N, M;
int inTime[MAX_N + 1], smallestOne[MAX_N + 1], subtreeSize[MAX_N + 1], currentTimer;
ll sequenceSum[MAX_N + 1], subtreeSum[MAX_N + 1];
bool visitedArray[MAX_N + 1];

void DFS(int vertexIndex, int parent) {
    visitedArray[vertexIndex] = true;
    inTime[vertexIndex] = smallestOne[vertexIndex] = ++currentTimer;
    subtreeSize[vertexIndex] = 1;
    ll childSum = 0;
    ll childSequence  = 0;
    int currentChildren = 0;
    
    for(int v : neighbourHood[vertexIndex]) {
        if(v == parent) continue;
        if(!visitedArray[v]){
            currentChildren++;
            DFS(v, vertexIndex);
            subtreeSize[vertexIndex] += subtreeSize[v];
            smallestOne[vertexIndex] = min(smallestOne[vertexIndex], smallestOne[v]);
            if(smallestOne[v] >= inTime[vertexIndex]) {
                childSum += subtreeSize[v];
                childSequence  += 1ll * subtreeSize[v] * subtreeSize[v];
            }
        } else { smallestOne[vertexIndex] = min(smallestOne[vertexIndex], inTime[v]); }
    }
    
    ll restValue = (N - 1) - childSum;
    if(restValue > 0) childSequence += restValue * restValue;
    
    sequenceSum[vertexIndex]  = childSequence;
    subtreeSum[vertexIndex] = childSum;
}

void solveTestCase() {
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        int A, B;
        cin >> A >> B;
        neighbourHood[A].push_back(B);
        neighbourHood[B].push_back(A);
    }

    DFS(1, 0);

    ll totalRoads = 1ll * N * (N - 1);
    for(int x = 1; x <= N; x++){
        ll sumValue = sequenceSum[x] - (N - 1);
        ll totalBlocked = totalRoads - sumValue;
        cout << totalBlocked << endl;
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

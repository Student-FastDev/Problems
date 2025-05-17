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

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> neighbourList(N+1), reversedNeighbourList(N+1);
    vector<int> inDegree(N+1, 0);

    for(int i = 0; i < M; i++){
        int A, B;
        cin >> A >> B;
        neighbourList[A].push_back(B);
        reversedNeighbourList[B].push_back(A);
        inDegree[B]++;
    }

    queue<int> queueArray;
    for(int i = 1; i <= N; i++){
        if(inDegree[i] == 0) 
            queueArray.push(i);
    }
    int hasSeen = 0;
    while(!queueArray.empty()){
        int u = queueArray.front(); queueArray.pop();
        hasSeen++;
        for(int v: neighbourList[u]){
            if(--inDegree[v] == 0)
                queueArray.push(v);
        }
    }
    if(hasSeen < N){
        cout << "NIE" << endl;
        return;
    }

    vector<char> visitedArray(N+1, 0);
    deque<int> dequeArray;
    visitedArray[1] = 1;
    dequeArray.push_back(1);
    int mustBeat = 0;
    while(!dequeArray.empty()){
        int u = dequeArray.front(); dequeArray.pop_front();
        for(int p: reversedNeighbourList[u]){
            if(!visitedArray[p]){
                visitedArray[p] = 1;
                mustBeat++;
                dequeArray.push_back(p);
            }
        }
    }

    fill(all(visitedArray), 0);
    visitedArray[1] = 1;
    dequeArray.push_back(1);
    int mustLose = 0;
    while(!dequeArray.empty()){
        int u = dequeArray.front(); dequeArray.pop_front();
        for(int v: neighbourList[u]){
            if(!visitedArray[v]){
                visitedArray[v] = 1;
                mustLose++;
                dequeArray.push_back(v);
            }
        }
    }

    int best = 1 + mustBeat;
    int worst = N - mustLose;

    cout << best << " " << worst << endl;
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

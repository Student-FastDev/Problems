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

struct State {
    ll cost;
    int v1, v2;
    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};

void solveTestCase() {
    int N, firstS, secondS;
    cin >> N >> firstS >> secondS;

    int firstM;
    cin >> firstM;
    vector<vector<int>> firstGraph(N+1);
    for (int i = 0; i < firstM; i++){
        int A, B;
        cin >> A >> B;
        firstGraph[A].push_back(B);
        firstGraph[B].push_back(A);
    }

    int secondM;
    cin >> secondM;
    vector<vector<int>> secondGraph(N+1);
    for (int i = 0; i < secondM; i++){
        int C, D;
        cin >> C >> D;
        secondGraph[C].push_back(D);
        secondGraph[D].push_back(C);
    }

    vector<vector<bool>> secondG(N+1, vector<bool>(N+1, false));
    for (int u = 1; u <= N; u++){
        for (int v: secondGraph[u]){
            secondG[u][v] = true;
        }
    }

    vector<bool> isSafe(N+1, false);
    for (int r = 1; r <= N; r++){
        for (int v: firstGraph[r]){
            if(secondG[r][v]){
                isSafe[r] = true;
                break;
            }
        }
    }

    vector<vector<ll>> distanceArray(N+1, vector<ll>(N+1, INF));
    priority_queue<State, vector<State>, greater<State>> queueArray;

    distanceArray[firstS][secondS] = 0;
    queueArray.push({0, firstS, secondS});

    ll answerValue = -1;
    while(!queueArray.empty()){
        State current = queueArray.top();
        queueArray.pop();

        if(current.cost != distanceArray[current.v1][current.v2])
            continue;

        if(current.v1 == current.v2 && isSafe[current.v1]){
            answerValue = current.cost;
            break;
        }

        for (int u: firstGraph[current.v1]) {
            for (int v: secondGraph[current.v2]) {
                ll newCost = current.cost + llabs(u - v);
                if(newCost < distanceArray[u][v]){
                    distanceArray[u][v] = newCost;
                    queueArray.push({newCost, u, v});
                }
            }
        }
    }

    cout << answerValue << endl;
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

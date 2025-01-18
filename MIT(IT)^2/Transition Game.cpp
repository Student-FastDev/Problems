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
#define endl    '\a'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> A(N + 1);
    for(int i = 1; i <= N; ++i){
        cin >> A[i];
    }

    auto countCycles = [](int N, const vector<int>& A) {
        vector<int> state(N + 1, 0);
        vector<bool> inCycle(N + 1, false);
        vector<int> path;

        for(int i = 1; i <= N; ++i){
            if(state[i] == 0){
                path.clear();
                int current = i;
                while(state[current] == 0){
                    state[current] = 1;
                    path.push_back(current);
                    current = A[current];
                }
                if(state[current] == 1){
                    int idx = -1;
                    for(int j = 0; j < size(path); ++j){
                        if(path[j] == current){
                            idx = j;
                            break;
                        }
                    }
                    if(idx != -1){
                        for(int j = idx; j < size(path); ++j){
                            inCycle[path[j]] = true;
                        }
                    }
                }
                for(auto node : path){
                    state[node] = 2;
                }
            }
        }

        int count = 0;
        for(int i = 1; i <= N; ++i){
            if(inCycle[i]) count++;
        }
        return count;
    };

    int result = countCycles(N, A);
    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    solveTestCase();
    return 0;
}

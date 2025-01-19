#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
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
    
    vector<vector<int>> cowsArray(N, vector<int>(M));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> cowsArray[i][j];
        }
        sort(cowsArray[i].begin(), cowsArray[i].end());
    }

    vector<int> allCards;
    allCards.reserve(N * M);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            allCards.push_back(cowsArray[i][j]);
        }
    }
    sort(all(allCards));

    if((int)size(allCards) != N * M) {
        cout << "-1" << endl;
        return;
    }

    vector<vector<int>> groupsArray(M, vector<int>(N));
    for(int k = 0; k < M; k++) {
        for(int i = 0; i < N; i++) {
            groupsArray[k][i] = allCards[k * N + i];
        }
    }

    unordered_map<int, int> firstCardToCow;
    for(int i = 0; i < N; i++) {
        firstCardToCow[cowsArray[i][0]] = i + 1;
    }

    vector<int> P(N, -1);
    vector<bool> cowAssigned(N + 1, false);
    bool valid = true;
    for(int i = 0; i < N; i++) {
        int card = groupsArray[0][i];
        if(firstCardToCow.find(card) == firstCardToCow.end()) {
            valid = false;
            break;
        }
        int cow = firstCardToCow[card];
        if(cowAssigned[cow]) {
            valid = false;
            break;
        }
        P[i] = cow;
        cowAssigned[cow] = true;
    }
    if(!valid) {
        cout << "-1" << endl;
        return;
    }

    for(int k = 1; k < M; k++) {
        for(int i = 0; i < N; i++) {
            int cow = P[i];
            if(cowsArray[cow - 1][k] != groupsArray[k][i]) {
                valid = false;
                break;
            }
        }
        if(!valid) {
            break;
        }
    }
    if(valid) {
        for(int i = 0; i < N; i++) {
            if(i > 0) cout << ' ';
            cout << P[i];
        }
        cout << endl;
    } else {
        cout << "-1" << endl;
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

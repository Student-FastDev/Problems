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
#define pileSize(x)  x.pileSize()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct Pile {
    int pileID;
    int pileSize;
};

bool comparePiles(const Pile& A, const Pile& b) {
    return A.pileSize > b.pileSize;
}

void solveTestCase() {
    int N;
    ll K;
    cin >> N >> K;
    
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<int> stacksArray;
    vector<vector<int>> pilesArray;
    
    for (int i = 0; i < N; ++i) {
        int value = A[i];
        auto iterator = lower_bound(stacksArray.begin(), stacksArray.end(), value);
        
        if (iterator == stacksArray.end()) {
            stacksArray.push_back(value);
            pilesArray.push_back({i + 1});
        } else {
            *iterator = value;
            int pile_idx = distance(stacksArray.begin(), iterator);
            pilesArray[pile_idx].push_back(i + 1);
        }
    }

    ll L = (K + 1) / 2;
    
    vector<Pile> pileInformations;
    for (int i = 0; i < size(pilesArray); ++i) pileInformations.push_back({i, (int)size(pilesArray[i])});
    
    sort(all(pileInformations), comparePiles);
    
    ll currentLength = 0;
    vector<int> chosenIndices;
    
    for (int i = 0; i < size(pileInformations) && i < L; ++i) {
        currentLength += pileInformations[i].pileSize;
        int ID = pileInformations[i].pileID;
        for (int j : pilesArray[ID]) chosenIndices.push_back(j);
    }
    
    if (currentLength >= K) {
        cout << "YES" << endl;
        sort(all(chosenIndices));
        for (int i = 0; i < K; ++i) cout << chosenIndices[i] << (i == K - 1 ? "" : " ");
        cout << endl;
    } else {
        cout << "NO" << endl;
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

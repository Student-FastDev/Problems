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

int addMod(int A, int B) {
    A += B;
    if (A >= MOD) A -= MOD;
    return A;
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    vector<int> S(N + 1, 0);
    for (int i = 2; i <= N; i++) {
        if (!S[i]) {
            for (int j = i; j <= N; j += i) {
                if (!S[j]) S[j] = i;
            }
        }
    }

    vector<int> D(N + 1, 0);
    ll finalAnswer = 0;

    auto getDivs = [&](int X) {
        vector<pair<int,int>> factorArray;
        while (X > 1) {
            int P = S[X], C = 0;
            while (X % P == 0) {
                X /= P;
                C++;
            }
            factorArray.emplace_back(P, C);
        }
        vector<int> divisorArray = {1};
        for (auto &i : factorArray) {
            int P = i.first, C = i.second;
            int sizeValue = size(divisorArray);
            ll PP = 1;
            for (int j = 1; j <= C; j++) {
                PP *= P;
                for (int i = 0; i < sizeValue; i++) {
                    divisorArray.push_back(int(divisorArray[i] * PP));
                }
            }
        }
        if (!divisorArray.empty() && divisorArray[0] == 1) divisorArray.erase(divisorArray.begin());
        return divisorArray;
    };

    for (int v : P) {
        int createWays = 1;
        if (v == 1) {
            createWays = addMod(createWays, int(finalAnswer % MOD));
        } else {
            auto divisorArray = getDivs(v - 1);
            int S = 0;
            for (int d : divisorArray) {
                S = addMod(S, D[d]);
            }
            createWays = addMod(createWays, S);
        }
        D[v] = createWays;
        finalAnswer = (finalAnswer + createWays) % MOD;
    }

    cout << finalAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
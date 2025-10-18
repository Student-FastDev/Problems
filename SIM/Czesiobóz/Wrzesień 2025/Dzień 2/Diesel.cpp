// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N;
    cin >> N;
    vector<pii> intervalsArray;
    for(int i = 0; i < N; ++i) {
        string S;
        cin >> S;
        int position = S.find(':');
        int H = stoi(S.substr(0, position));
        int M = stoi(S.substr(position + 1));
        int T = H*60 + M;
        int L = T;
        int R = min(T + 5, 8*60);
        if(L < R) intervalsArray.emplace_back(L, R);
    }

    int awakeTIme = 0;
    if(!intervalsArray.empty()) {
        int currentL = intervalsArray[0].first;
        int currentR = intervalsArray[0].second;
        for(size_t i = 1; i < size(intervalsArray); ++i) {
            int L = intervalsArray[i].first;
            int R = intervalsArray[i].second;
            if(L > currentR) {
                awakeTIme += currentR - currentL;
                currentL = L; currentR = R;
            } else {
                currentR = max(currentR, R);
            }
        }
        awakeTIme += currentR - currentL;
    }

    int totalSleep = 8*60 - awakeTIme;
    cout << totalSleep << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

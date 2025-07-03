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

const int B = 22;
const ll INF = 9223372036854775806;
const ll MAX_N = 1e6 + 5;
const ll MAX_VAL = 1 << B;
const ll MOD = 1e9+7; // 998244353

pii F[MAX_VAL];
int numberArray[MAX_N];
int N;

void mergeInto(pii& destinationPair, const pii& sourcePair) {
    if (sourcePair.first > destinationPair.first) {
        destinationPair.second = destinationPair.first;
        destinationPair.first = sourcePair.first;
    } else if (sourcePair.first > destinationPair.second && sourcePair.first != destinationPair.first) {
        destinationPair.second = sourcePair.first;
    }

    if (sourcePair.second > destinationPair.second && sourcePair.second != destinationPair.first) {
        destinationPair.second = sourcePair.second;
    }
}

void solveTestCase() {
    cin >> N;
    vector<int> uniqueIndices;
    vector<bool> wasSeen(MAX_VAL, false);

    for (int i = 0; i < N; ++i) {
        cin >> numberArray[i];
        if (!wasSeen[numberArray[i]]) {
            wasSeen[numberArray[i]] = true;
            uniqueIndices.push_back(i);
        }
    }

    for (int i = 0; i < MAX_VAL; ++i) {
        F[i] = {-1, -1};
    }

    for (int i = 0; i < N; ++i) {
        if (i > F[numberArray[i]].first) {
            F[numberArray[i]].second = F[numberArray[i]].first;
            F[numberArray[i]].first = i;
        } else if (i > F[numberArray[i]].second) {
            F[numberArray[i]].second = i;
        }
    }
    
    for (int i = 0; i < B; ++i) {
        for (int mask = 0; mask < MAX_VAL; ++mask) {
            if (mask & (1 << i)) {
                mergeInto(F[mask ^ (1 << i)], F[mask]);
            }
        }
    }
    
    int finalAnswer = 0;
    for (int b = B - 1; b >= 0; --b) {
        int potentialAnswer = finalAnswer | (1 << b);
        bool isPossible = false;

        for (int i : uniqueIndices) {
            int currentValue = numberArray[i];
            int neededValue = potentialAnswer & (~currentValue);
            
            if (F[neededValue].second > i) {
                isPossible = true;
                break;
            }
        }

        if (isPossible) finalAnswer = potentialAnswer;
    }

    cout << finalAnswer << endl;    
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

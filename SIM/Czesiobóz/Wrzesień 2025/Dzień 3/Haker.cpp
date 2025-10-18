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
    string S;
    cin >> S;
    int N = (int)size(S);
    
    vector<int> positionArray;
    positionArray.reserve(N);
    for (int i = 0; i < N; ++i) if (S[i] == '0') positionArray.push_back(i);
    int M = (int)size(positionArray);
    
    int Q;
    cin >> Q;
    if (M == 0) {
        for (int i = 0; i < Q; ++i) {
            long long K; 
            cin >> K;
            cout << 0 << endl;
        }
        return;
    }
    
    vector<int> D(M), B(M);
    for (int i = 0; i < M; ++i) {
        D[i] = positionArray[i] - i;
        B[i] = 2 * i - positionArray[i];
    }
    
    for (int l = 0; l < Q; ++l) {
        long long K; 
        cin >> K;
        int R = 0;
        deque<int> dequeValue;
        long long finalAnswer = 0;
        for (int l = 0; l < M; ++l) {
            while (R < M && (long long)D[R] <= (long long)D[l] + K) {
                while (!dequeValue.empty() && B[dequeValue.back()] <= B[R]) dequeValue.pop_back();
                dequeValue.push_back(R);
                ++R;
            }
            while (!dequeValue.empty() && dequeValue.front() < l) dequeValue.pop_front();
            if (!dequeValue.empty()) {
                int bestR = dequeValue.front();
                long long currentCandidate = K + (long long)B[bestR] - (long long)B[l] + 1LL;
                if (currentCandidate > M) currentCandidate = M;
                if (currentCandidate > finalAnswer) finalAnswer = currentCandidate;
            }
        }
        cout << finalAnswer << endl;
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

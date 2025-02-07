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
const ll MOD = 998244353; // 1e9 + 7;
int N;

vector<vector<int>> neighbourHood;
vector<bool> active, visited;
vector<long long> DP;
vector<int> componentsArray;

inline void putUI(unsigned int n) {
    if(n==0) {
        putc_unlocked(48,stdout);
        return;
    }
    char tab[12];
    int p = 0;
    while(n != 0) {
        tab[p++] = (n % 10) + 48;
        n /= 10;
    }
    while(p--) 
        putc_unlocked(tab[p], stdout);
}

inline void readINT(int *n) {
    register char c = 0, znak_liczby = 1;
    while (c < 33) c = getc_unlocked(stdin);
    if(c == 45) {znak_liczby = -1; c = getc_unlocked(stdin);}
    (*n) = 0;
    while (c > 32) {(*n) = (*n) * 10 + c - 48; c = getc_unlocked(stdin);}
    (*n) *= znak_liczby;
}

long long dfsDP(int u, int parent) {
    visited[u] = true;
    long long resultValue = 1;
    for (auto v : neighbourHood[u]) {
        if (v == parent || !active[v]) continue;
        if (!visited[v]) {
            long long subValue = dfsDP(v, u);
            resultValue = (resultValue * (1 + subValue)) % MOD;
        }
    }
    DP[u] = resultValue;
    componentsArray.push_back(u);
    return resultValue;
}

void solveTestCase() {
    readINT(&N);
    neighbourHood.resize(N + 1);
    for (int i = 1; i < N; i++) {
        int A, B;
        readINT(&A);
        readINT(&B);
        neighbourHood[A].push_back(B);
        neighbourHood[B].push_back(A);
    }

    vector<int> mobiusArray(N + 1, 1);
    vector<int> primesArray;
    vector<bool> isComp(N + 1, false);
    for (int i = 2; i <= N; i++) {
        if (!isComp[i]) {
            primesArray.push_back(i);
            mobiusArray[i] = -1;
        }
        for (int p : primesArray) {
            if ((long long)i * p > N) break;
            isComp[i * p] = true;
            if (i % p == 0) {
                mobiusArray[i * p] = 0;
                break;
            } else {
                mobiusArray[i * p] = -mobiusArray[i];
            }
        }
    }

    vector<vector<int>> multiplicationArray(N + 1);
    for (int d = 1; d <= N; d++) {
        for (int m = d; m <= N; m += d)
            multiplicationArray[d].push_back(m);
    }

    vector<long long> f(N + 1, 0);
    active.assign(N + 1, false);
    visited.assign(N + 1, false);
    DP.assign(N + 1, 0);

    for (int d = 1; d <= N; d++) {
        for (int v : multiplicationArray[d]) {
            active[v] = true;
            visited[v] = false;
        }
        for (int v : multiplicationArray[d]) {
            if (!visited[v]) {
                componentsArray.clear();
                dfsDP(v, 0);
                long long compSum = 0;
                for (int u : componentsArray)
                    compSum = (compSum + DP[u]) % MOD;
                f[d] = (f[d] + compSum) % MOD;
            }
        }
        for (int v : multiplicationArray[d]) {
            active[v] = false;
        }
    }

    vector<long long> answerArray(N + 1, 0);
    for (int k = 1; k <= N; k++) {
        long long sum = 0;
        for (int j = 1; k * j <= N; j++) {
            sum = (sum + (long long)mobiusArray[j] * f[k * j]) % MOD;
        }
        if (sum < 0) sum += MOD;
        answerArray[k] = sum;
    }

    for (int k = 1; k <= N; k++) {
        putUI(answerArray[k] % MOD);
        putc_unlocked(' ', stdout);
    }
    putc_unlocked('\n', stdout);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    while(T--) {
        solveTestCase();
    }
}

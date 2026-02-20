// Catling
#include <bits/stdc++.h>
using namespace std;

#define size(x) x.size()
#define all(x) x.begin(),x.end()
#define endl '\n'

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const ll MAX_N = 1e6 + 67;
const ll MOD = 1e9 + 9;
const ll INF = LLONG_MAX / 4; 

vector<ll> neighbourList[MAX_N];
ll Q[MAX_N], P[MAX_N], S[MAX_N];
char C[MAX_N];

void solveTestCase() {
    ll N, H = 0, T = 0, u;
    cin >> N;
    for(ll i = 1, v; i < N; ++i) {
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }
    Q[T++] = 1;
    while(H < T) {
        u = Q[H++];
        for(ll x : neighbourList[u]) {
            if(x != P[u]) {
                P[x] = u;
                Q[T++] = x;
            }
        }
    }
    ll M = 0;
    for(ll i = N - 1; i; --i) {
        u = Q[i];
        ll x = ++S[u];
        S[P[u]] += x;
        M += x * (N - x) - (x & 1);
    }
    C[1] = '0';
    for(ll i = 0; i < N; ++i) {
        ll w = 0;
        u = Q[i];
        for(ll x : neighbourList[u]) {
            if(x != P[u]) C[x] = C[u] ^ ((S[x] & 1) && (w ^= 1));
        }
    }
    cout << M / 2 << endl << C + 1 << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
}

// Catling
#include <bits/stdc++.h>
using namespace std;

#define size(x) x.size()
#define all(x) x.begin(),x.end()
#define endl '\n'

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int MAX_N = 1505;
const ll MOD = 1e9 + 9;
const ll INF = LLONG_MAX / 4;

vector<int> neighbourList[MAX_N], reversedList[MAX_N], O, C[MAX_N];
bool visitedArray[MAX_N];
int checkArray[MAX_N], K;
bitset<MAX_N> bitsetArray[MAX_N];

void firstDFS(int u) {
    visitedArray[u] = 1;
    for(int x : neighbourList[u]) {
        if(!visitedArray[x]) {
            firstDFS(x);
        }
    }
    O.push_back(u);
}

void secondDFS(int u) {
    visitedArray[u] = 1; checkArray[u] = K;
    C[K].push_back(u);
    for(int x : reversedList[u]) {
        if(!visitedArray[x]) {
            secondDFS(x);
        }
    }
}

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    while(M--) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        reversedList[v].push_back(u);
    }

    for(int i = 1; i <= N; i++) {
        if(!visitedArray[i]) {
            firstDFS(i);
        }
    }

    fill(visitedArray, visitedArray + MAX_N, 0);
    for(int i = N - 1; i >= 0; i--) {
        if(!visitedArray[O[i]]) {
            ++K; secondDFS(O[i]);
        }
    }

    for(int i = K; i >= 1; i--) {
        bitsetArray[i].set(i);
        for(int u : C[i]) {
            for(int x : neighbourList[u]) {
                int tempValue = checkArray[x];
                if(!bitsetArray[i].test(tempValue)) {
                    bitsetArray[i] |= bitsetArray[tempValue];
                }
            }
        }
    }
    int finalAnswer = K - 1;
    for(int d = K - 1; d >= 1; d--) {
        for(int i = 1; i <= K - d; i++) {
            if(!bitsetArray[i].test(i + d)) {
                finalAnswer++;
            }
        }
    }
    cout << finalAnswer << endl;
    for(int d = K - 1; d >= 1; d--) {
        for(int i = 1; i <= K - d; i++) {
            if(!bitsetArray[i].test(i + d)) {
                cout << C[i][0] << " " << C[i + d][0] << endl;
            }
        }
    }
    for(int i = K; i >= 2; i--) {
        cout << C[i][0] << " " << C[i - 1][0] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
}

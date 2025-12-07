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
const ll MAX_N = 1e6+5;
const ll MOD = 1e9+7; 

int automaton[MAX_N][26];
int piArray[MAX_N];

void solveTestCase() {
    string stringS;
    if(!(cin >> stringS)) return;
    
    int N = size(stringS);
    
    piArray[0] = 0;
    for (int i = 1; i < N; ++i) {
        int j = piArray[i-1];
        while (j > 0 && stringS[i] != stringS[j])
            j = piArray[j-1];
        if (stringS[i] == stringS[j])
            j++;
        piArray[i] = j;
    }
    
    for(int c = 0; c < 26; ++c) {
        if (stringS[0] - 'a' == c)
            automaton[0][c] = 1;
        else
            automaton[0][c] = 0;
    }
    
    for(int i = 1; i < N; ++i) {
        int prevLen = piArray[i-1];
        for(int c = 0; c < 26; ++c) {
            if (stringS[i] - 'a' == c)
                automaton[i][c] = i + 1;
            else
                automaton[i][c] = automaton[prevLen][c];
        }
    }
    
    int numQueries;
    cin >> numQueries;
    
    while(numQueries--) {
        string stringT;
        cin >> stringT;
        int M = size(stringT);
        
        int currentLen = piArray[N-1];
        vector<int> queryResults(M);
        
        for(int k = 0; k < M; ++k) {
            char charC = stringT[k];
            
            bool matchedInExtension = false;
            while(currentLen >= N) {
                if (charC == stringT[currentLen - N]) {
                    currentLen++;
                    matchedInExtension = true;
                    break;
                }
                if (currentLen == N) {
                    currentLen = piArray[N-1];
                } else {
                    currentLen = queryResults[currentLen - N - 1];
                }
            }
            
            if (!matchedInExtension) {
                currentLen = automaton[currentLen][charC - 'a'];
            }
            
            queryResults[k] = currentLen;
            cout << currentLen << (k == M - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto parentNode)->decltype(parentNode.first,o){return o<<'('<<parentNode.first<<", "<<parentNode.second <<')';}
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

const ll INF = 1e9+67;
const ll MAX_N = 1e5+67;
const ll MOD = 1e9+7; // 998244353

const int K = 26;

struct Vertex {
    int nextArray[K];  
    bool isOutput;    
    int parentNode;
    char parentCharacter;
    int linkNode;
    int exitNode;
    int goArray[K];
    
    int patternNumber;   

    Vertex(int parent = -1, char currentCharacter = '$') {
        for (int i = 0; i < K; ++i) {
            nextArray[i] = -1;
            goArray[i] = -1;
        }
        isOutput = false;
        parentNode = parent;
        parentCharacter = currentCharacter;
        linkNode = -1;
        exitNode = -1;
        patternNumber = -1;
    }
};

vector<Vertex> trieArray;
vector<vector<int>> occurrencesArray;

void addString(const string& s, int id) {
    int v = 0;
    for (char currentCharacter : s) {
        int c = currentCharacter - 'a';
        if (trieArray[v].nextArray[c] == -1) {
            trieArray[v].nextArray[c] = size(trieArray);
            trieArray.push_back(Vertex(v, currentCharacter));
        }
        v = trieArray[v].nextArray[c];
    }
    trieArray[v].isOutput = true;
    trieArray[v].patternNumber = id;
}

int goFunction(int v, char currentCharacter);

int getLink(int v) {
    if (trieArray[v].linkNode == -1) {
        if (v == 0 || trieArray[v].parentNode == 0) {
            trieArray[v].linkNode = 0;
        } else {
            int parent_link = getLink(trieArray[v].parentNode);
            trieArray[v].linkNode = goFunction(parent_link, trieArray[v].parentCharacter);
        }
    }
    return trieArray[v].linkNode;
}

int getExitLink(int v) {
    if (trieArray[v].exitNode == -1) {
        int l = getLink(v);
        if (l == 0 || v == 0) {
            trieArray[v].exitNode = 0;
        } else {
            if (trieArray[l].isOutput == true) {
                trieArray[v].exitNode = l;
            } else {
                trieArray[v].exitNode = getExitLink(l);
            }
        }
    }
    return trieArray[v].exitNode;
}

int goFunction(int v, char currentCharacter) {
    int c = currentCharacter - 'a';
    if (trieArray[v].goArray[c] == -1) {
        if (trieArray[v].nextArray[c] != -1) {
            trieArray[v].goArray[c] = trieArray[v].nextArray[c];
        } else {
            if (v == 0) {
                trieArray[v].goArray[c] = 0;
            } else {
                int link_v = getLink(v);
                trieArray[v].goArray[c] = goFunction(link_v, currentCharacter);
            }
        }
    }
    return trieArray[v].goArray[c];
}

void searchText(const string& text) {
    int v = 0;
    for (int i = 0; i < (int)text.length(); i++) {
        v = goFunction(v, text[i]);
        int temporaryText = v;
        while (temporaryText != 0) {
            if (trieArray[temporaryText].isOutput == true) {
                occurrencesArray[trieArray[temporaryText].patternNumber].push_back(i);
            }
            temporaryText = getExitLink(temporaryText);
        }
    }
}

void solveTestCase() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string S;
    cin >> S;
    
    int Q;
    cin >> Q;
    
    trieArray.reserve(MAX_N); 
    trieArray.push_back(Vertex());
    occurrencesArray.resize(Q);
    
    vector<int> valuesArray(Q);
    vector<int> lengthsArray(Q);
    
    for (int i = 0; i < Q; ++i) {
        string w;
        cin >> valuesArray[i] >> w;
        lengthsArray[i] = w.length();
        addString(w, i);
    }
    
    searchText(S);
    
    for (int i = 0; i < Q; ++i) {
        int K = valuesArray[i];
        int patternLength = lengthsArray[i];
        int currentCount = size(occurrencesArray[i]);
        
        if (currentCount < K) {
            cout << -1 << endl;
        } else {
            int minimumSpan = INF;
            for (int j = 0; j <= currentCount - K; ++j) {
                int currentSpan = occurrencesArray[i][j + K - 1] - (occurrencesArray[i][j] - patternLength + 1) + 1;
                if (currentSpan < minimumSpan) minimumSpan = currentSpan;
            }
            cout << minimumSpan << endl;
        }
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
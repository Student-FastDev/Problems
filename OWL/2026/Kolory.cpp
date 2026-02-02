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

const int BLOCK_SIZE = 350;
const int LIMIT = 100005;
const int MAX_Q = 200005;

vector<int> positionArray[LIMIT];
vector<int> doHeavy[LIMIT];
ll finalAnswers[MAX_Q];
ll interactArray[LIMIT];
int colorsArray[LIMIT];
bool isHeavy[LIMIT];
pii queryData[MAX_Q];

ll solveLight(int U, int V) {
    vector<int>& A = positionArray[U];
    vector<int>& B = positionArray[V];
    
    int sizeA = (int)size(A);
    vector<ll> prefixA(sizeA + 1, 0);

    partial_sum(all(A), prefixA.begin() + 1);
    
    ll totalDistance = 0;
    int currentPointer = 0;
    
    for (int y : B) {
        while(currentPointer < sizeA && A[currentPointer] < y) {
            currentPointer++;
        }
        
        ll distanceLeft = (ll)currentPointer * y - prefixA[currentPointer];
        
        ll sumRight = prefixA[sizeA] - prefixA[currentPointer];
        ll distanceRight = sumRight - (ll)(sizeA - currentPointer) * y;
        
        totalDistance += (distanceLeft + distanceRight);
    }
    
    return totalDistance;
}

void solveTestCase() {
    int N, M, Q;
    cin >> N >> M >> Q;

    for(int i = 1; i <= M; ++i) {
        positionArray[i].clear();
        doHeavy[i].clear();
        isHeavy[i] = false;
    }

    for(int i = 1; i <= N; ++i) {
        cin >> colorsArray[i];
        positionArray[colorsArray[i]].push_back(i);
    }

    for(int i = 1; i <= M; ++i) {
        if ((int)size(positionArray[i]) > BLOCK_SIZE) {
            isHeavy[i] = true;
        }
    }

    for(int i = 0; i < Q; ++i) {
        int U, V;
        cin >> U >> V;
        queryData[i] = {U, V};
        
        if (!isHeavy[U] && !isHeavy[V]) {
            finalAnswers[i] = solveLight(U, V);
        } else {
            if (isHeavy[U]) doHeavy[U].push_back(i);
            else doHeavy[V].push_back(i);
        }
    }

    for (int h = 1; h <= M; ++h) {
        if (doHeavy[h].empty()) continue;
        for(int k = 1; k <= M; ++k) interactArray[k] = 0;

        ll countValue = 0;
        ll indexSum = 0;
        for(int i = 1; i <= N; ++i) {
            int c = colorsArray[i];
            if (c == h) {
                countValue++;
                indexSum += i;
            } else {
                interactArray[c] += (countValue * i - indexSum);
            }
        }

        countValue = 0;
        indexSum = 0;
        for(int i = N; i >= 1; --i) {
            int c = colorsArray[i];
            if (c == h) {
                countValue++;
                indexSum += i;
            } else {
                interactArray[c] += (indexSum - countValue * i);
            }
        }

        for (int index : doHeavy[h]) {
            int U = queryData[index].first;
            int V = queryData[index].second;
            int target = (U == h) ? V : U;
            finalAnswers[index] = interactArray[target];
        }
    }

    for(int i = 0; i < Q; ++i) cout << finalAnswers[i] << endl;
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

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

int N, M;
vector<int> friendArray;
vector<int> parentArray;
vector<ll> distanceToParent;
vector<bool> isDeadArray;

pair<int, ll> findRoot(int i) {
    if (parentArray[i] == i) return {i, 0};
    pair<int, ll> rootResult = findRoot(parentArray[i]);
    parentArray[i] = rootResult.first;
    distanceToParent[i] += rootResult.second;
    return {parentArray[i], distanceToParent[i]};
}

void solveTestCase() {
    cin >> N >> M;
    friendArray.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> friendArray[i];
        friendArray[i]--;
    }

    vector<int> startNodeArray(M);
    for (int i = 0; i < M; ++i) cin >> startNodeArray[i];
    vector<int> budgetArray(M);
    for (int i = 0; i < M; ++i) cin >> budgetArray[i];

    parentArray.resize(N);
    iota(all(parentArray), 0);
    distanceToParent.assign(N, 0);
    isDeadArray.assign(N, false);

    int lastResult = 0;
    for (int i = 0; i < M; ++i) {
        ll startNodeIndex = ((ll)startNodeArray[i] + lastResult - 1) % N;
        ll currentBudget = budgetArray[i];
        
        int currentResult = 0;
        int currentNode = (int)startNodeIndex;
        ll remainingBudget = currentBudget;

        while (remainingBudget > 0) {
            pair<int, ll> lookupResult = findRoot(currentNode);
            int rootNode = lookupResult.first;
            ll distanceValue = lookupResult.second;

            if (distanceValue >= remainingBudget) {
                break;
            }

            remainingBudget -= distanceValue;
            currentNode = rootNode;

            if (isDeadArray[currentNode]) {
                break;
            }

            currentResult++;
            remainingBudget--; 
            
            int nextNode = friendArray[currentNode];
            
            pair<int, ll> nextLookupResult = findRoot(nextNode);
            if (nextLookupResult.first == currentNode) {
                isDeadArray[currentNode] = true;
            } else {
                parentArray[currentNode] = nextNode;
                distanceToParent[currentNode] = 1;
            }

            currentNode = nextNode;
        }

        cout << currentResult << endl;
        lastResult = currentResult;
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
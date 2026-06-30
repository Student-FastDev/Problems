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

struct Gate {
    ll gatePosition, keyPosition;
};

void solveTestCase() {
    ll N, S, H;
    cin >> N >> S >> H;
    
    vector<Gate> gatesArray(N);
    for (int i = 0; i < N; i++) cin >> gatesArray[i].keyPosition >> gatesArray[i].gatePosition;
    
    if (S > H) {
        S = -S;
        H = -H;
        for (int i = 0; i < N; i++) {
            gatesArray[i].gatePosition = -gatesArray[i].gatePosition;
            gatesArray[i].keyPosition = -gatesArray[i].keyPosition;
        }
    }
    
    vector<Gate> rightGates, leftGates;
    for (int i = 0; i < N; i++) {
        if (gatesArray[i].gatePosition > S) rightGates.push_back(gatesArray[i]);
        else if (gatesArray[i].gatePosition < S) leftGates.push_back(gatesArray[i]);
    }
    
    sort(rightGates.begin(), rightGates.end(), [](const Gate& a, const Gate& b) { return a.gatePosition < b.gatePosition; });
    sort(leftGates.begin(), leftGates.end(), [](const Gate& a, const Gate& b) { return a.gatePosition > b.gatePosition; });
    
    int rightSize = size(rightGates);
    vector<bool> rightError(rightSize, false);
    vector<ll> rightK(rightSize, S);
    ll currentMinimum = S;
    bool currentError = false;
    for (int i = 0; i < rightSize; i++) {
        if (rightGates[i].keyPosition > rightGates[i].gatePosition) currentError = true;
        rightError[i] = currentError;
        if (rightGates[i].keyPosition < S) currentMinimum = min(currentMinimum, rightGates[i].keyPosition);
        rightK[i] = currentMinimum;
    }
    
    int leftSize = size(leftGates);
    vector<bool> leftError(leftSize, false);
    vector<ll> leftK(leftSize, S);
    ll currentMax = S;
    currentError = false;
    for (int i = 0; i < leftSize; i++) {
        if (leftGates[i].keyPosition < leftGates[i].gatePosition) currentError = true;
        leftError[i] = currentError;
        if (leftGates[i].keyPosition > S) currentMax = max(currentMax, leftGates[i].keyPosition);
        leftK[i] = currentMax;
    }
    
    vector<ll> pathArray;
    pathArray.push_back(H);
    ll currentRight = H;
    ll currentLeft = -INF;
    
    while (true) {
        int leftIndex = 0, rightIndex = rightSize - 1, indexR = -1;
        while (leftIndex <= rightIndex) {
            int middleValue = (leftIndex + rightIndex) / 2;
            if (rightGates[middleValue].gatePosition < currentRight) { indexR = middleValue; leftIndex = middleValue + 1; }
            else { rightIndex = middleValue - 1; }
        }
        
        ll L = S;
        if (indexR >= 0) {
            if (rightError[indexR]) { cout << -1 << endl; return; }
            L = rightK[indexR];
        }
        
        if (L == S) break;
        if (currentLeft != -INF && L <= currentLeft) { cout << -1 << endl; return; }
        
        pathArray.push_back(L);
        currentLeft = L;
        
        leftIndex = 0, rightIndex = leftSize - 1; 
        int indexL = -1;
        while (leftIndex <= rightIndex) {
            int middleValue = (leftIndex + rightIndex) / 2;
            if (leftGates[middleValue].gatePosition > L) { indexL = middleValue; leftIndex = middleValue + 1; } 
            else { rightIndex = middleValue - 1; }
        }
        
        ll nextR = S;
        if (indexL >= 0) {
            if (leftError[indexL]) { cout << -1 << endl; return; }
            nextR = leftK[indexL];
        }
        
        if (nextR >= currentRight) { cout << -1 << endl; return; } 
        if (nextR == S) break;
        pathArray.push_back(nextR);
        currentRight = nextR;
    }
    
    ll totalDistance = 0;
    ll currentPosition = S;
    for (int i = (int)size(pathArray) - 1; i >= 0; i--) {
        totalDistance += abs(pathArray[i] - currentPosition);
        currentPosition = pathArray[i];
    }
    
    cout << totalDistance << endl;
    return;
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
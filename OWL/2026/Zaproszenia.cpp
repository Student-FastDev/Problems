// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll,ll> pll;

#define endl '\n'
#define all(x) x.begin(),x.end()
#define size(x) x.size()

const ll MAX_N = 1e5;
const ll MOD = 1e9 + 9;
const ll INF = 1e18 + 67;

struct Edge {
    ll to, weight;
};

void solveTestCase() {
    ll N;
    cin >> N;

    vector<vector<Edge>> neighbourList(N + 1);
    ll totalW = 0;

    for(ll i = 0; i < N - 1; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        neighbourList[u].push_back({v, w});
        neighbourList[v].push_back({u, w});
        totalW += w;
    }

    ll Q;
    cin >> Q;
    vector<ll> delayArray(Q);
    for(ll i = 0; i < Q; i++) cin >> delayArray[i];

    if(N == 1) {
        for(ll i = 0; i < Q; i++) cout << 0 << endl;
        return;
    }

    vector<ll> parentArray(N + 1, 0);
    vector<ll> orderArray;
    orderArray.reserve(N);

    queue<ll> queueArray;
    queueArray.push(1);
    while(!queueArray.empty()) {
        ll u = queueArray.front();
        queueArray.pop();
        orderArray.push_back(u);

        for(auto edge : neighbourList[u]) {
            if(edge.to != parentArray[u]) {
                parentArray[edge.to] = u;
                queueArray.push(edge.to);
            }
        }
    }

    vector<ll> H(N + 1, 0);
    vector<ll> pathLength;
    pathLength.reserve(N);

    for(ll i = N - 1; i >= 0; i--) {
        ll u = orderArray[i];
        ll maxBranch = 0;
        for(auto edge : neighbourList[u]) {
            if(edge.to == parentArray[u]) continue;
            ll currentBranch = edge.weight + H[edge.to];
            if(currentBranch > maxBranch) {
                if(maxBranch > 0) pathLength.push_back(maxBranch);
                maxBranch = currentBranch;
            } else {
                if(currentBranch > 0); pathLength.push_back(currentBranch);
            }
        }
        H[u] = maxBranch;
    }

    if(H[1] > 0) pathLength.push_back(H[1]);
    sort(all(pathLength), greater<ll>());

    ll firstValue = 0;
    if(!pathLength.empty()) firstValue = pathLength[0];

    ll baseAnswer = 2 * totalW - firstValue;
    vector<ll> restArray;
    if(size(pathLength) > 1) restArray.assign(pathLength.begin() + 1, pathLength.end());
    ll M = size(restArray);
    vector<ll> prefixSums(M + 1, 0);
    partial_sum(all(restArray), prefixSums.begin() + 1);
    
    for(ll i = 0; i < Q; i++) {
        ll P = delayArray[i];
        ll finalAnswer = baseAnswer;

        if(M > 0) {
            auto firstIterator = upper_bound(all(restArray), P, greater<ll>());
            ll currentCount = distance(restArray.begin(), firstIterator);

            if(currentCount > 0) {
                ll sumValues = prefixSums[currentCount];
                ll currentSavings = sumValues - (ll)currentCount * P;
                finalAnswer -= currentSavings;
            }
        }
        cout << finalAnswer << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T;
    cin >> T;
    
    while(T--) {
        solveTestCase();
    }
}

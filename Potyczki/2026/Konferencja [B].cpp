// Catling
#include <bits/stdc++.h>
using namespace std;

#define size(X) X.size()
#define all(X) X.begin(),X.end()
#define endl '\n'

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int MAX_N = 5e5 + 67;
const ll MOD = 1e9 + 9;
const ll INF = LLONG_MAX / 4;

void solveTestCase() {
    int K, N;
    cin >> K >> N;

    vector<int> startArray(K + 1);
    vector<int> currentArray(K + 1);
    
    currentArray[1] = N;
    startArray[1] = 1;
    int totalMeetings = N;
    
    vector<int> parentArray;
    parentArray.reserve(MAX_N);
    parentArray.push_back(0);
    
    for (int j = 0; j < N; ++j) parentArray.push_back(0);
    
    for (int i = 2; i <= K; ++i) {
        int currentElement;
        cin >> currentElement;
        currentArray[i] = currentElement;
        startArray[i] = totalMeetings + 1;
        for (int j = 0; j < currentElement; ++j) {
            int P;
            cin >> P;
            if (P == 0) {
                parentArray.push_back(0);
            } else {
                parentArray.push_back(startArray[i - 1] + P - 1);
            }
        }
        totalMeetings += currentElement;
    }
    
    vector<ll> E(totalMeetings + 1, 0);
    vector<ll> daySum(K + 1, 0);
    
    int currentDay = K;
    for (int u = totalMeetings; u >= 1; --u) {
        while (currentDay > 1 && u < startArray[currentDay]) currentDay--;
        E[u] = max(1LL, E[u]);
        daySum[currentDay] += E[u];
        
        if (parentArray[u] != 0) E[parentArray[u]] += E[u];
    }
    
    ll finalAnswer = 0;
    for (int i = 1; i <= K; ++i) finalAnswer = max(finalAnswer, daySum[i]);
    
    cout << finalAnswer << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
}
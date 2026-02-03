// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll, ll> pll;

#define size(x) x.size
#define endl '\n'
#define all(x) x.begin(),x.end()

const ll MOD = 1e9 + 7;
const ll MAX_N = 1e5;
const ll INF = 1e18 + 1;

void solveTestCase() {
    ll N;
    cin >> N;

    vector<ll> A(N);
    for(ll i = 0; i < N; i++) cin >> A[i];

    vector<ll> leftStack(N);
    vector<ll> rightStack(N);
    stack<ll> S;

    for(ll i = 0; i < N; i++) {
        while(!S.empty() && A[S.top()] >= A[i]) S.pop();
        if(S.empty()) leftStack[i] = -1;
        else leftStack[i] = S.top();
        S.push(i);
    }

    while(!S.empty()) S.pop();

    for(ll i = N - 1; i >= 0; --i) {
        while(!S.empty() && A[S.top()] >= A[i]) S.pop();
        if(S.empty()) rightStack[i] = N;
        else rightStack[i] = S.top();
        S.push(i);
    }

    vector<ll> scoreForLength(N + 1, 0);
    for(ll i = 0; i < N; i++) {
        ll segmentLength = rightStack[i] - leftStack[i] - 1;
        scoreForLength[segmentLength] = max(scoreForLength[segmentLength], A[i]);
    }

    vector<ll> finalAnswer(N + 1);
    finalAnswer[N] = scoreForLength[N];
    for(ll k = N - 1; k >= 1; k--) {
        finalAnswer[k] = max(finalAnswer[k + 1], scoreForLength[k]);
    }

    for(ll i = 1; i <= N; i++) {
        cout << finalAnswer[i] << " ";
    }
    cout << endl;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

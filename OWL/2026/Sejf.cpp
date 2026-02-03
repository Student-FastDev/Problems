// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll, ll> pll;

#define size(x) (ll)x.size()
#define endl '\n'
#define all(x) x.begin(),x.end()

const ll MOD = 1e9 + 7;
const ll MAX_N = 1e5;
const ll INF = 1e18 + 1;

ll fastPower(ll base, ll power) {
    if(power == 0) return 1;
    if(power == 1) return base;

    if(power % 2 == 0) {
        ll helperValue = fastPower(base, power / 2) % MOD;
        return (helperValue * helperValue) % MOD;
    }
    return ((fastPower(base, power - 1) % MOD) * base) % MOD;
}

ll modInverse(ll value) {
    return fastPower(value, MOD - 2);
}

vector<ll> KMP(string& pattern) {
    ll M = size(pattern);
    vector<ll> LPS(M, 0);

    ll currentLength = 0;
    ll i = 1;
    while(i < M) {
        if(pattern[i] == pattern[currentLength]) {
            currentLength++;
            LPS[i] = currentLength;
            i++;
        }
        else {
            if(currentLength != 0) {
                currentLength = LPS[currentLength - 1];
            } else {
                LPS[i] = 0;
                i++;
            }
        }
    }
    return LPS;
}

pll findPattern(string& text, string& pattern) {
    ll N = size(text);
    ll M = size(pattern);

    if(M == 0) return {0, 0};
    if(N == 0 || M > N) return {0, 0};
    vector<ll> LPS = KMP(pattern);

    ll i = 0;
    ll j = 0;
    
    ll matchesAtZero = 0;
    ll matchesAtOther = 0;

    while(i < N) {
        if(pattern[j] == text[i]) {
            i++;
            j++;
        }
        if(j == M) {
            ll startPosition = i - j;
            
            if(startPosition < M) {
                if(startPosition == 0) matchesAtZero++;
                else matchesAtOther++;
            }
            
            j = LPS[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if(j != 0) {
                j = LPS[j - 1];
            } else {
                i++;
            }
        }
    }
    return {matchesAtZero, matchesAtOther};
}

void solveTestCase() {
    ll N, K;
    cin >> N >> K;

    string inputString, finalString;
    cin >> inputString >> finalString;

    if(N == 1) {
        if(K == 0) cout << (inputString[0] == finalString[0] ? 1 : 0) << endl;
        else cout << 0 << endl;
        return;
    }

    string S = inputString + inputString;
    pll matches = findPattern(S, finalString);

    if(matches.first == 0 && matches.second == 0) {
        cout << 0 << endl;
        return;
    }
    
    ll A = N - 1;
    ll B = fastPower(A, K);
    ll C = fastPower(MOD - 1, K);
    ll inverseN = modInverse(N);

    ll termZero = (A % MOD * C) % MOD;
    ll waysZero = (B + termZero) % MOD;
    waysZero = (waysZero * inverseN) % MOD;

    ll waysOther = (B - C + MOD) % MOD;
    waysOther = (waysOther * inverseN) % MOD;

    ll totalWays = (matches.first * waysZero) % MOD;
    ll otherPart = (matches.second * waysOther) % MOD;
    
    ll finalAnswer = (totalWays + otherPart) % MOD;

    cout << finalAnswer << endl;
    return;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}

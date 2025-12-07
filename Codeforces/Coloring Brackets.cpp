// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

int matchArray[705];
ll memoizationTable[705][705][3][3];
string bracketString;

void buildMatchArray() {
    stack<int> indicesStack;
    int N = size(bracketString);
    for (int i = 0; i < N; ++i) {
        if (bracketString[i] == '(') {
            indicesStack.push(i);
        } else {
            int openIndex = indicesStack.top();
            indicesStack.pop();
            matchArray[openIndex] = i;
            matchArray[i] = openIndex;
        }
    }
}

bool areAdjacentsValid(int color1, int color2) {
    if (color1 != 0 && color2 != 0) {
        return color1 != color2;
    }
    return true;
}

bool areMatchesValid(int color1, int color2) {
    if (color1 == 0 && color2 != 0) return true;
    if (color1 != 0 && color2 == 0) return true;
    return false;
}

ll solve(int L, int R, int colorL, int colorR) {
    if (memoizationTable[L][R][colorL][colorR] != -1) {
        return memoizationTable[L][R][colorL][colorR];
    }

    ll answer = 0;

    if (L + 1 == R) {
        if (areMatchesValid(colorL, colorR)) {
            answer = 1;
        } else {
            answer = 0;
        }
    } else if (matchArray[L] == R) {
        if (areMatchesValid(colorL, colorR)) {
            for (int nextColorL = 0; nextColorL < 3; ++nextColorL) {
                for (int nextColorR = 0; nextColorR < 3; ++nextColorR) {
                    if (areAdjacentsValid(colorL, nextColorL) && areAdjacentsValid(nextColorR, colorR)) {
                        answer = (answer + solve(L + 1, R - 1, nextColorL, nextColorR)) % MOD;
                    }
                }
            }
        } else {
            answer = 0;
        }
    } else {
        int matchIndex = matchArray[L];
        for (int colorMatch = 0; colorMatch < 3; ++colorMatch) {
            for (int colorMatchNext = 0; colorMatchNext < 3; ++colorMatchNext) {
                if (areAdjacentsValid(colorMatch, colorMatchNext)) {
                    ll leftPart = solve(L, matchIndex, colorL, colorMatch);
                    ll rightPart = solve(matchIndex + 1, R, colorMatchNext, colorR);
                    answer = (answer + leftPart * rightPart) % MOD;
                }
            }
        }
    }

    return memoizationTable[L][R][colorL][colorR] = answer;
}

void solveTestCase() {
    cin >> bracketString;
    buildMatchArray();

    memset(memoizationTable, -1, sizeof(memoizationTable));

    int N = size(bracketString);
    ll totalWays = 0;

    for (int colorFirst = 0; colorFirst < 3; ++colorFirst) {
        for (int colorLast = 0; colorLast < 3; ++colorLast) {
            totalWays = (totalWays + solve(0, N - 1, colorFirst, colorLast)) % MOD;
        }
    }

    cout << totalWays << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}
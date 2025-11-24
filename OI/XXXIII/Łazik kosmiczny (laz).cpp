// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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

vector<ll> distinctPrimeFactors(ll x) {
    vector<ll> primeFactors;
    if (x <= 1) return primeFactors;
    for (ll d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            primeFactors.push_back(d);
            while (x % d == 0) x /= d;
        }
    }
    if (x > 1) primeFactors.push_back(x);
    return primeFactors;
}

void printCharacters(char c, ll count) {
    for (ll i = 0; i < count; ++i) {
        cout << c;
    }
}

void solveTestCase() {
    ll N, M;
    cin >> N >> M;

    int Q = gcd(N, M);

    if (Q == 1) {
        cout << 2 << endl;
        cout << "DP" << endl;
        return;
    }

    vector<ll> primeFactorsN = distinctPrimeFactors(N);
    vector<ll> primeFactorsM = distinctPrimeFactors(M);

    vector<char> coprimeN(Q+1, 1), coprimeM(Q+1, 1);
    coprimeN[0] = 0;
    coprimeM[0] = 0;
    for (ll P : primeFactorsN) {
        for (ll j = P; j <= Q; j += P) coprimeN[j] = 0;
    }
    for (ll P : primeFactorsM) {
        for (ll j = P; j <= Q; j += P) coprimeM[j] = 0;
    }

    vector<vector<int>> lastM(2, vector<int>(Q+1, -1));
    for (int parity = 0; parity <= 1; ++parity) {
        int last = -1;
        for (ll i = 0; i <= Q; ++i) {
            if (i > 0 && (i % 2 == parity) && coprimeM[i]) last = (int)i;
            lastM[parity][i] = last;
        }
    }

    bool hasFound = false;
    ll A = -1, B = -1, P = -1, K = -1;

    for (ll u = 1; u <= Q && !hasFound; ++u) {
        if (!coprimeN[u]) continue;
        int parityNeeded = (int)((Q - u) & 1);
        ll currentLimit = Q - u;
        if (currentLimit < 1) continue;
        int v = lastM[parityNeeded][currentLimit];
        if (v == -1) continue;
        ll S = Q - (u + v);
        if (S < 0 || (S & 1)) continue;
        P = S / 2; K = 0; A = P + u; B = v + K;
        if (A >= 0 && B >= 0 && P >= 0 && K >= 0 && A + B + P + K == Q && gcd(A - P, N) == 1 && gcd(B - K, M) == 1) { 
            hasFound = true;
            break;
        }
    }

    ll nG = -1, nL = -1;

    for (ll i = 1; i < Q; ++i) {
        ll currentNG = i;
        ll currentNL = Q - i;

        if (gcd(currentNG, N) == 1 && gcd(currentNL, M) == 1) {
            nG = currentNG;
            nL = currentNL;
            break;
        }
    }
    
    if(nG != -1 && nL != -1) {
        A = nG; P = 0; B = nL; K = 0;
    }

    cout << Q << endl;
    if ((A == 0 || P == 0) && (B == 0 || K == 0)) {
        printCharacters('G', A);
        printCharacters('D', P);
        printCharacters('L', B);
        printCharacters('R', K);
        cout << endl;
    }
    else if (A > 0 && P > 0 && (B == 0 || K == 0)) {
        char separationCharacters = (B > 0) ? 'L' : 'R';
        ll& separationCount = (B > 0) ? B : K;

        bool turnG = (A > P);
        while (A > 0 || P > 0) {

            if (turnG) {
                if (A > 0) { cout << 'G'; A--; }
            } else {
                if (P > 0) { cout << 'D'; P--; }
            }
            turnG = !turnG;
            
            if ((A > 0 || P > 0) && separationCount > 0) {
                cout << separationCharacters;
                separationCount--;
            }
        }
        printCharacters(separationCharacters, separationCount);
        cout << endl;
    }
    else if (B > 0 && K > 0 && (A == 0 || P == 0)) {
        char separationCharacters = (A > 0) ? 'G' : 'D';
        ll& separationCount = (A > 0) ? A : P;

        bool turnL = (B > K);
        while (B > 0 || K > 0) {
            if (turnL) {
                if (B > 0) { cout << 'L'; B--; }
            } else {
                if (K > 0) { cout << 'R'; K--; }
            }
            turnL = !turnL;
            
            if ((B > 0 || K > 0) && separationCount > 0) {
                cout << separationCharacters;
                separationCount--;
            }
        }
        printCharacters(separationCharacters, separationCount);
        cout << endl;
    }
    else if (A > 0 && P > 0 && B > 0 && K > 0) {
        ll firstNRemaining = A + P;
        ll secondNRemaining = B + K;

        bool firstGTurn = (firstNRemaining >= secondNRemaining);

        bool nextIsG = (A > P);
        bool nextIsL = (B > K);
        
        while (firstNRemaining > 0 || secondNRemaining > 0) {
            if (firstGTurn) {
                if (nextIsG) {
                    if (A > 0) { cout << 'G'; A--; } else { cout << 'D'; P--; }
                } else {
                    if (P > 0) { cout << 'D'; P--; } else { cout << 'G'; A--; }
                }
                nextIsG = !nextIsG;
                firstNRemaining--;
            } else {
                if (nextIsL) {
                    if (B > 0) { cout << 'L'; B--; } else { cout << 'R'; K--; }
                } else {
                    if (K > 0) { cout << 'R'; K--; } else { cout << 'L'; B--; }
                }
                nextIsL = !nextIsL;
                secondNRemaining--;
            }
            firstGTurn = !firstGTurn;
        }
        cout << endl;
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
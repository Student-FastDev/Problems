// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second<<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
mt19937_64 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count());

ll mulMod(ll A, ll B, ll M) {
    __int128 t = (__int128)A * B;
    return (ll)(t % M);
}
ll powMod(ll A, ll E, ll M) {
    ll result = 1;
    while (E) {
        if (E & 1) result = mulMod(result, A, M);
        A = mulMod(A, A, M);
        E >>= 1;
    }
    return result;
}

bool isPrime(ll N) {
    if (N < 2) return false;
    for (ll p: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (N % p == 0) return N == p;
    ll D = N - 1, S = 0;
    while ((D & 1) == 0) { D >>= 1; ++S; }
    for (ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % N == 0) continue;
        ll X = powMod(a, D, N);
        if (X == 1 || X == N - 1) continue;
        bool isComposite = true;
        for (int r = 1; r < S; ++r) {
            X = mulMod(X, X, N);
            if (X == N - 1) { isComposite = false; break; }
        }
        if (isComposite) return false;
    }
    return true;
}

ll pollardRho(ll N) {
    if (N % 2 == 0) return 2;
    if (N % 3 == 0) return 3;
    ll C = uniform_int_distribution<ll>(1, N-1)(rng);
    ll X = uniform_int_distribution<ll>(0, N-1)(rng);
    ll Y = X, D = 1;
    auto F = [&](ll v){ return (mulMod(v,v,N) + C) % N; };
    while (D == 1) {
        X = F(X);
        Y = F(F(Y));
        D = gcd(llabs(X - Y), N);
        if (D == N) return pollardRho(N);
    }
    return D;
}

void factorRecursively(ll N, vector<ll>& factorsArray) {
    if (N == 1) return;
    if (isPrime(N)) {
        factorsArray.push_back(N);
        return;
    }
    ll D = pollardRho(N);
    factorRecursively(D, factorsArray);
    factorRecursively(N/D, factorsArray);
}

vector<ll> primesArray;
int kPrimes;

ll countBad(ll X, int I = 0, ll currentProduct = 1) {
    if (I == kPrimes || currentProduct > X) return 0;
    ll answerValue = countBad(X, I + 1, currentProduct);
    ll P = primesArray[I];
    if (currentProduct <= X / P) {
        ll nextProduct = currentProduct * P;
        ll countValue = X / nextProduct;
        answerValue += countValue - countBad(X, I + 1, nextProduct);
    }
    return answerValue;
}

void solveTestCase() {
    ll A, B, L, R;
    cin >> A >> B >> L >> R;
    ll G = gcd(A, B);
    ll lowerBound = (L + G - 1) / G;
    ll upperBound = R / G;
    if (lowerBound > upperBound) {
        cout << "NIE" << endl;
        return;
    }

    vector<ll> factorsArray;
    factorRecursively(A / G, factorsArray);
    factorRecursively(B / G, factorsArray);
    sort(factorsArray.begin(), factorsArray.end());
    factorsArray.erase(unique(factorsArray.begin(), factorsArray.end()), factorsArray.end());
    primesArray = factorsArray;
    kPrimes = primesArray.size();
    ll totalRange = upperBound - lowerBound + 1;
    ll badCount = countBad(upperBound) - countBad(lowerBound - 1);
    if (totalRange - badCount > 0) cout << "TAK" << endl;
    else cout << "NIE" << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solveTestCase();
    }
    return 0;
}

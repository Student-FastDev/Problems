#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll MAX_N = 50000 + 69;
const ll MOD = 12345678;
vector<ll> sieveArray(MAX_N);
unordered_map<ll, ll> pFactors;

void prepareSieve() {
    for (ll i = 2; i < MAX_N; i++) {
        sieveArray[i] = i;
    }

    for (ll i = 2; i * i < MAX_N; i++) {
        if (sieveArray[i] == i) {
            for (ll j = i * i; j < MAX_N; j += i) {
                if (sieveArray[j] == j) {
                    sieveArray[j] = i;
                }
            }
        }
    }
}

void getPrimeFactors(ll A) {
    unordered_map<ll, ll> primeFactors;
    while (A != 1) {
        primeFactors[sieveArray[A]]++;
        A /= sieveArray[A];
    }

    for(auto &p : primeFactors) {
        pFactors[p.first] = max(pFactors[p.first], p.second);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    prepareSieve();

    ll N;
    cin >> N;
    if (N <= 0) {
        return 1;
    }

    vector<ll> times(N);
    for (ll i = 0; i < N; ++i) {
        cin >> times[i];
        if (times[i] <= 0) {
            return 1;
        }
        getPrimeFactors(times[i]);
    }

    ll result = 1;
    for (auto &p : pFactors) {
        result = (result * (p.second + 1)) % MOD;
    }

    result -= N;
    cout << result << endl;
    return 0;
}

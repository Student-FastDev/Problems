#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll T;
    cin >> T;

    while(T--) {
        ll N, K;
        cin >> N >> K;

        if(N < K) { cout << "NO\n"; continue; }
        if(N == K) { cout << "YES\n"; cout << 1 << "\n"; cout << 1 << "\n"; continue; }

        if(K < N && 2*K > N + 1) { cout << "NO\n"; continue; }

        cout << "YES\n";
        cout << 2 << "\n";
        cout << N - K + 1 << " ";
        cout << 1 << " ";
        cout << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, k; cin >> n >> k;

    if (n % k != 0) cout << n / k + 1;
    else cout << n / k;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    long long n, x, y; cin >> n >> x >> y;

    if (x % 2 == 0) {
        if (y % 2 == 0) cout << "CZARNE";
        else cout << "BIALE";
    }
    if (x % 2 == 1) {
        if (y % 2 == 0) cout << "BIALE";
        else cout << "CZARNE";
    }
}      
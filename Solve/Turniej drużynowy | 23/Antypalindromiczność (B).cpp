#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int MOD = N % 3;
    int L = N/3;

    for(int i = 0; i < L; i++) {
        cout << "abc";
    }


    for(int i = 0; i < MOD; i++) {
        cout << char('a' + i);
    }

    return 0;
}

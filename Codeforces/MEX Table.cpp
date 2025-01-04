#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int T;
    cin >> T;
    while (T--) {
        ll N, M;
        cin >> N >> M;
        cout << max(N, M) + 1 << '\n';
    }
 
    return 0;
}

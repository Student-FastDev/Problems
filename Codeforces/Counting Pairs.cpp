#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long X, Y;
        cin >> N >> X >> Y;
        
        vector<long long> a(N);
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }
        
        sort(a.begin(), a.end());
        long long S = accumulate(a.begin(), a.end(), 0LL);
        long long l = S - Y, r = S - X;
        
        long long count = 0;
        for (int i = 0; i < N - 1; i++) {
            long long lowVal = l - a[i];
            long long highVal = r - a[i];
            
            int low = lower_bound(a.begin() + i + 1, a.end(), lowVal) - a.begin();
            int high = upper_bound(a.begin() + i + 1, a.end(), highVal) - a.begin() - 1;
            
            if (low <= high) {
                count += (high - low + 1);
            }
        }
        
        cout << count << '\n';
    }
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    
    while (T--) {
        int N, K;
        cin >> N >> K;
        
        vector<int> A(N);
        map<int, int> freq;
        
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            freq[A[i]]++;
        }
        
        int distinctCount = freq.size();
        
        if (K >= N) {
            cout << 1 << "\n";
            continue;
        }
        
        vector<int> freqValues;
        for (auto &[val, count] : freq) {
            freqValues.push_back(count);
        }
        
        sort(freqValues.begin(), freqValues.end());
        
        for (int count : freqValues) {
            if (K >= count) {
                K -= count;
                distinctCount--;
            } else {
                break;
            }
        }
        
        cout << distinctCount << "\n";
    }
}

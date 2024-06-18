#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;
    vector<int> coins(N);
    
    for(int i = 0; i < N; i++) {
        cin >> coins[i];
    }
    
    int initialPairs = 0;
    for(int i = 0; i < N - 1; i++) {
        if(coins[i] == coins[i + 1]) {
            initialPairs++;
        }
    }
    
    int maxGain = -1;
    for(int i = 0; i < N; i++) {
        int gain = 0;
        
        if(i > 0) {
            if(coins[i] != coins[i - 1]) {
                gain++;
            } else {
                gain--;
            }
        }
        if(i < N - 1) {
            if(coins[i] != coins[i + 1]) {
                gain++;
            } else {
                gain--;
            }
        }
        
        maxGain = max(maxGain, gain);
    }
    
    cout << initialPairs + maxGain << endl;
    
    return 0;
}

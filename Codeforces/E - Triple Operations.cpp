#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int howMuch(int A) {
    int O = 0;
    while(A > 0) {
        A /= 3;
        O++;
    }
    return O;
}
 
int main()
{
    int T;
    cin >> T;
    
    const int MAX_N = 200001;
    vector<int> howMuchValues(MAX_N + 1);
    for (int i = 1; i <= MAX_N; i++) {
        howMuchValues[i] = howMuch(i);
    }
 
    vector<int> prefixSum(MAX_N + 1);
    for (int i = 1; i <= MAX_N; i++) {
        prefixSum[i] = prefixSum[i-1] + howMuchValues[i];
    }
 
    for (int t = 0; t < T; t++) {
        int L, R;
        cin >> L >> R;
        
        int scoreValue = prefixSum[R] - prefixSum[L] + 2 * howMuchValues[L];
        
        cout << scoreValue << endl;
    }
 
    return 0;
}

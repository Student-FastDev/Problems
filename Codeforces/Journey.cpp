#include <iostream>
#include <vector>
using namespace std;
 
int main() {
    int T;
    cin >> T;
    vector<int> results(T);
    
    for (int i = 0; i < T; ++i) {
        long long N, A, B, C;
        cin >> N >> A >> B >> C;
        
        long long cycleDistance = A + B + C;
        long long fullCycles = N / cycleDistance;
        long long remainingDistance = N % cycleDistance;
        
        int days = fullCycles * 3;
        
        if (remainingDistance > 0) {
            days++;
            remainingDistance -= A;
        }
        if (remainingDistance > 0) {
            days++;
            remainingDistance -= B;
        }
        if (remainingDistance > 0) {
            days++;
        }
        
        results[i] = days;
    }
    
    for (int result : results) {
        cout << result << endl;
    }
    
    return 0;
}

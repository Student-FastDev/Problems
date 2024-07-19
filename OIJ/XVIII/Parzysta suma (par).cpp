#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    long long totalSum = 0;
    int smallestOdd = 1000001;
    
    for (int i = 0; i < N; i++) {
        totalSum += A[i];
        if (A[i] % 2 != 0) {
            smallestOdd = min(smallestOdd, A[i]);
        }
    }
    
    if (totalSum % 2 != 0) {
        totalSum -= smallestOdd;
    }
    
    cout << totalSum << endl;
    
    return 0;
}

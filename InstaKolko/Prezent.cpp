#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long N;
    cin >> N;
    
    vector<long long> inputArray(N);
    
    for (long long i = 0; i < N; i++) {
        cin >> inputArray[i];
    }
    
    sort(inputArray.begin(), inputArray.end());
    
    long long maxSticks = 0;
    long long left = 0;
    
    for (long long right = 2; right < N; right++) {
        while (inputArray[left] + inputArray[left + 1] <= inputArray[right]) {
            left++;
        }
        maxSticks = max(maxSticks, right - left + 1);
    }
    
    if(maxSticks < 3) {
        cout << 0 << endl;
        return 0;
    }
    cout << maxSticks << endl;
    
    return 0;
}

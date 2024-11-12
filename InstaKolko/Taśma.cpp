#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long maxSubarraySum(const vector<long long>& tape) {
    long long maxSum = 0;
    long long currentSum = 0;

    for (long long num : tape) {
        currentSum = max(num, currentSum + num);
        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    long long n;
    cin >> n;
    vector<long long> tape(n);

    for (long long i = 0; i < n; ++i) {
        cin >> tape[i];
    }

    long long result = maxSubarraySum(tape);

    cout << result << endl;

    return 0;
}

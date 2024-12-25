#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
const long long MAX_N = 1e9+1;
const long long MOD = 1e9+7;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    long long T;
    cin >> T;
 
    while (T--) {
        long long N;
        cin >> N;
        vector<long long> array(N);
        long long xIndex = -1;
        long long x = 0;
 
        for (long long i = 0; i < N; i++) {
            cin >> array[i];
            if (array[i] != -1 && array[i] != 1) {
                xIndex = i;
                x = array[i];
            }
        }
 
        set<long long> sumsSet;
 
        if (xIndex == -1) {
            long long currentSum = 0;
            sumsSet.insert(currentSum);
            for (long long i = 0; i < N; i++) {
                currentSum += array[i];
                sumsSet.insert(currentSum);
            }
        } else {
            long long currentSum = 0;
            set<long long> leftSums;
            leftSums.insert(0);
            for (long long i = xIndex - 1; i >= 0; i--) {
                currentSum += array[i];
                leftSums.insert(currentSum);
            }
 
            currentSum = 0;
            set<long long> rightSums;
            rightSums.insert(0);
            for (long long i = xIndex + 1; i < N; i++) {
                currentSum += array[i];
                rightSums.insert(currentSum);
            }
 
            for (long long l : leftSums) {
                for (long long r : rightSums) {
                    sumsSet.insert(l + r);
                    sumsSet.insert(l + r + x);
                }
            }
 
            sumsSet.insert(x);
 
            currentSum = x;
            for (long long i = xIndex - 1; i >= 0; i--) {
                currentSum += array[i];
                sumsSet.insert(currentSum);
            }
            currentSum = x;
            for (long long i = xIndex + 1; i < N; i++) {
                currentSum += array[i];
                sumsSet.insert(currentSum);
            }
        }
 
        long long maxLeft = LLONG_MIN, minLeft = LLONG_MAX;
        long long maxRight = LLONG_MIN, minRight = LLONG_MAX;
        long long prefixSum = 0;
        long long minPrefix = 0, maxPrefix = 0;
 
        prefixSum = 0;
        minPrefix = 0;
        for (long long i = xIndex - 1; i >= 0; i--) {
            prefixSum += array[i];
            maxLeft = max(maxLeft, prefixSum - minPrefix);
            minLeft = min(minLeft, prefixSum - maxPrefix);
            minPrefix = min(minPrefix, prefixSum);
            maxPrefix = max(maxPrefix, prefixSum);
        }
 
        prefixSum = 0;
        minPrefix = 0;
        maxPrefix = 0;
        for (long long i = xIndex + 1; i < N; i++) {
            prefixSum += array[i];
            maxRight = max(maxRight, prefixSum - minPrefix);
            minRight = min(minRight, prefixSum - maxPrefix);
            minPrefix = min(minPrefix, prefixSum);
            maxPrefix = max(maxPrefix, prefixSum);
        }
 
        for (long long i = minLeft; i <= maxLeft; i++) {
            sumsSet.insert(i);
        }
        for (long long i = minRight; i <= maxRight; i++) {
            sumsSet.insert(i);
        }
 
        vector<long long> resultArray(sumsSet.begin(), sumsSet.end());
        cout << resultArray.size() << "\n";
        for (long long sum : resultArray) {
            cout << sum << " ";
        }
        cout << "\n";
    }
 
    return 0;
}

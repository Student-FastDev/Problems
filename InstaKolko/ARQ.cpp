#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

long long maxDifferenceAfterOperations(int N, long long K, vector<int>& arr) {
    int minElem = *min_element(arr.begin(), arr.end());
    int maxElem = *max_element(arr.begin(), arr.end());

    if (K >= 2) {
        return maxElem - minElem;
    }

    long long total_sum = accumulate(arr.begin(), arr.end(), 0LL);
    vector<long long> transformedArr;
    for (int x : arr) {
        transformedArr.push_back(total_sum - x);
    }

    auto [newMinElem, newMaxElem] = minmax_element(transformedArr.begin(), transformedArr.end());
    return *newMaxElem - *newMinElem;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N;
    long long K;
    cin >> N >> K;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    cout << maxDifferenceAfterOperations(N, K, arr) << endl;
    return 0;
}

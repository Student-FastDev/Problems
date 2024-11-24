#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> generateSums(const vector<long long>& arr, long long M) {
    int N = arr.size();
    vector<long long> sums;

    for (int mask = 0; mask < (1 << N); ++mask) {
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                sum += arr[i];
                sum %= M;
            }
        }
        sums.push_back(sum);
    }

    return sums;
}

int main() {
    int N;
    long long M;
    cin >> N >> M;

    vector<long long> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int mid = N / 2;
    vector<long long> left(arr.begin(), arr.begin() + mid);
    vector<long long> right(arr.begin() + mid, arr.end());

    vector<long long> leftSums = generateSums(left, M);
    vector<long long> rightSums = generateSums(right, M);

    sort(rightSums.begin(), rightSums.end());

    long long result = 0;

    for (long long leftSum : leftSums) {
        long long target = M - leftSum - 1;
        auto it = upper_bound(rightSums.begin(), rightSums.end(), target);
        if (it != rightSums.begin()) {
            --it;
            result = max(result, (leftSum + *it) % M);
        }

        result = max(result, leftSum % M);
    }

    cout << result << endl;

    return 0;
}

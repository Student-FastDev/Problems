#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long minimal_missing_multiple(long long n, long long k, const vector<long long>& S) {
    vector<long long> sortedS = S;
    sort(sortedS.begin(), sortedS.end());

    long long multiple = k;
    while (binary_search(sortedS.begin(), sortedS.end(), multiple)) {
        multiple += k;
    }

    return multiple;
}

int main() {
    long long n, k;
    cin >> n >> k;
    vector<long long> S(n);
    for (long long i = 0; i < n; ++i) {
        cin >> S[i];
    }
    
    long long result = minimal_missing_multiple(n, k, S);
    cout << result << endl;
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int findLargest(int N) {
    int low = 0;
    int high = 2 * static_cast<int>(sqrt(2 * N)) + 2;
    int best = 0;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        int current = mid * (mid + 1) / 2;
        if (current <= N) {
            best = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return best;
}

int main() {
    int N;
    cin >> N;

    vector<char> partsArray;
    int remaining = N;
    bool first = true;

    while (remaining > 0) {
        int M = findLargest(remaining);
        if (M == 0) {
            break;
        }
        if (!first) {
            partsArray.push_back(')');
        } else {
            first = false;
        }
        for (int i = 0; i < M; ++i) {
            partsArray.push_back('(');
            partsArray.push_back(')');
        }
        remaining -= M * (M + 1) / 2;
    }

    for (char c : partsArray) {
        cout << c;
    }
    cout << endl;

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

bool isBetter(const vector<int>& a, const vector<int>& b) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        if (a[i] < b[i]) {
            ++count;
        }
    }
    return count >= 3;
}

int findMultimedalist(const vector<vector<int>>& results) {
    int N = results.size();
    int candidate = 0;
    
    for (int i = 1; i < N; ++i) {
        if (isBetter(results[i], results[candidate])) {
            candidate = i;
        }
    }
    
    for (int i = 0; i < N; ++i) {
        if (i != candidate && !isBetter(results[candidate], results[i])) {
            return -1;
        }
    }
    
    return candidate + 1;
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<vector<int>> results(N, vector<int>(5));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 5; ++j) {
                cin >> results[i][j];
            }
        }
        
        cout << findMultimedalist(results) << endl;
    }
    
    return 0;
}

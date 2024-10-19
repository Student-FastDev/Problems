#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <cctype>

using namespace std;

bool canForm(const string& pattern, const string& cake, const int& repeat) {
    int n = pattern.length();
    int m = cake.length();
    
    if (repeat == 0) {
        return true;
    }
    
    int r = 0;
    int j = 0;
    for (int i = 0; i < m && j < n; i++) {
        if (cake[i] == pattern[j]) {
            r++;
            
            if (r == repeat) {
                j++;
                r = 0;
            }
        }
    }
    
    return j == n;
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    string pattern, cake;
    cin >> pattern >> cake;
    
    for(int i = 0; i < n; i++) {
        if(!isalpha(pattern[i])) {
            cout << "0" << endl;
            return 0;
        }
    }
    
    if (n > m) {
        cout << 0 << endl;
        return 0;
    }

    int low = 0, high = m / n, result = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (canForm(pattern, cake, mid)) {
            result = mid * n;
            low = mid + 1; 
        } else {
            high = mid - 1;
        }
    }
    
    cout << result << endl;
    return 0;
}
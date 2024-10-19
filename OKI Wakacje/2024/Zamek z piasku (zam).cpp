#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<char>> zamek(n, vector<char>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> zamek[i][j];
        }
    }

    bool symetryczny = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            if (zamek[i][j] != zamek[i][n - j - 1]) {
                symetryczny = false;
                break;
            }
        }
        if (!symetryczny) break;
    }

    if (symetryczny) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }

    return 0;
}
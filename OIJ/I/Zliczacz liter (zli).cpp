#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();

    unordered_map<char, int> letterCount;

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);

        for (char ch : line) {
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ') {
                letterCount[ch]++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (letterCount[ch] > 0) {
            cout << ch << " " << letterCount[ch] << "\n";
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (letterCount[ch] > 0) {
            cout << ch << " " << letterCount[ch] << "\n";
        }
    }

    return 0;
}

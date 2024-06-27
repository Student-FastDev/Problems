#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    string letters;
    cin >> letters;

    unordered_map<char, int> letterCount;
    for (char c : letters) {
        letterCount[c]++;
    }

    bool canMakeOIJ = letterCount['O'] >= 1 && letterCount['I'] >= 1 && letterCount['J'] >= 1;

    bool canMakeEJOI = letterCount['E'] >= 1 && letterCount['J'] >= 1 && letterCount['O'] >= 1 && letterCount['I'] >= 1;

    bool canMakeIOI = letterCount['I'] >= 2 && letterCount['O'] >= 1;

    cout << (canMakeOIJ ? 'T' : 'N');
    cout << (canMakeEJOI ? 'T' : 'N');
    cout << (canMakeIOI ? 'T' : 'N');
    cout << endl;

    return 0;
}

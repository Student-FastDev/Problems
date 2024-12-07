#include <iostream>
#include <vector>
#include <string>
using namespace std;

string generateWord(const vector<int>& prefixArray) {
    int N = prefixArray.size();
    string resultString(N, 'a');

    for (int i = 1; i < N; ++i) {
        if (prefixArray[i] > 0) {
            resultString[i] = resultString[prefixArray[i] - 1];
        } else {
            resultString[i] = 'b';
        }
    }

    vector<int> computedPrefix(N, 0);
    for (int i = 1, k = 0; i < N; ++i) {
        while (k > 0 && resultString[i] != resultString[k]) {
            k = computedPrefix[k - 1];
        }
        if (resultString[i] == resultString[k]) {
            ++k;
        }
        computedPrefix[i] = k;

        if (computedPrefix[i] != prefixArray[i]) {
            return "NIE";
        }
    }

    return resultString;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> prefixArray(N);
        for (int i = 0; i < N; ++i) {
            cin >> prefixArray[i];
        }

        string resultString = generateWord(prefixArray);
        if (resultString == "NIE") {
            cout << "NIE" << endl;
        } else {
            cout << "TAK" << endl;
            cout << resultString << endl;
        }
    }
    return 0;
}

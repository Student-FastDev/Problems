#include <bits/stdc++.h>
using namespace std;

vector<long long> values;
string inputString, resultString;
long long number;
char charMapping[10];

int main() {
    charMapping[2] = 'A';
    charMapping[3] = 'D';
    charMapping[4] = 'G';
    charMapping[5] = 'J';
    charMapping[6] = 'M';
    charMapping[7] = 'P';
    charMapping[8] = 'T';
    charMapping[9] = 'W';

    cin >> inputString >> number;
    number--;

    while (!inputString.empty()) {
        if (inputString.back() == '7' || inputString.back() == '9') {
            resultString.push_back(charMapping[inputString.back() - '0'] + number % 4);
            number /= 4;
        } else {
            resultString.push_back(charMapping[inputString.back() - '0'] + number % 3);
            number /= 3;
        }
        inputString.pop_back();
    }

    reverse(resultString.begin(), resultString.end());
    cout << resultString;

    return 0;
}

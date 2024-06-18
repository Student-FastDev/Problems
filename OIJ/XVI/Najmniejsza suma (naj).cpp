#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

long long minSum(vector<int>& digits, int K) {
    sort(digits.begin(), digits.end());

    vector<string> numbers(K, "");
    int index = 0;

    for (int i = 0; i < digits.size(); ++i) {
        if (digits[i] > 0) {
            numbers[index] += to_string(digits[i]);
            digits.erase(digits.begin() + i);
            index = (index + 1) % K;
            --i;
            if (index == 0) break;
        }
    }

    for (int digit : digits) {
        numbers[index] += to_string(digit);
        index = (index + 1) % K;
    }

    long long totalSum = 0;
    for (string& number : numbers) {
        totalSum += stoll(number);
    }

    return totalSum;
}

int main() {
    string input;
    int K;
    cin >> input >> K;

    vector<int> digits;
    for (char c : input) {
        digits.push_back(c - '0');
    }

    cout << minSum(digits, K) << endl;

    return 0;
}

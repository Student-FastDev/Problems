#include <iostream>
#include <string>
using namespace std;

int digitSum(const string &num) {
    int sum = 0;
    for (char c : num) {
        sum += c - '0';
    }
    return sum;
}

bool isDivisibleBy9(int sum) {
    return sum % 9 == 0;
}

int main() {
    string N;
    cin >> N;

    int sum = digitSum(N);
    int length = N.length();
    
    for (int i = 0; i < length; ++i) {
        int originalDigit = N[i] - '0';
        for (int newDigit = 0; newDigit <= 9; ++newDigit) {
            if (newDigit != originalDigit) {
                // Unikamy wiodących zer
                if (i == 0 && newDigit == 0) {
                    continue;
                }

                int newSum = sum - originalDigit + newDigit;
                if (isDivisibleBy9(newSum)) {
                    N[i] = newDigit + '0';
                    cout << N << endl;
                    return 0;
                }
            }
        }
    }

    cout << N << endl;
    return 0;
}

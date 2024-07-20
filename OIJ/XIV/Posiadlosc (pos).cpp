#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

int digit_sum(ull number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int max_digit_sum(ull A, ull B) {
    string A_str = to_string(A);
    string B_str = to_string(B);
    int max_sum = digit_sum(B);

    for (size_t i = 0; i < A_str.size(); ++i) {
        if (A_str[i] == '9') continue;

        string candidate = A_str;
        candidate[i] = '9';
        for (size_t j = i + 1; j < candidate.size(); ++j) {
            candidate[j] = '9';
        }

        ull candidate_num = stoull(candidate);
        if (candidate_num >= A && candidate_num <= B) {
            max_sum = max(max_sum, digit_sum(candidate_num));
        }
    }

    for (size_t i = 0; i < B_str.size(); ++i) {
        if (B_str[i] == '0') continue;

        string candidate = B_str;
        candidate[i] = (B_str[i] - 1);
        for (size_t j = i + 1; j < candidate.size(); ++j) {
            candidate[j] = '9';
        }

        ull candidate_num = stoull(candidate);
        if (candidate_num >= A && candidate_num <= B) {
            max_sum = max(max_sum, digit_sum(candidate_num));
        }
    }

    return max_sum;
}

int main() {
    ull A, B;
    cin >> A >> B;

    cout << max_digit_sum(A, B) << endl;

    return 0;
}

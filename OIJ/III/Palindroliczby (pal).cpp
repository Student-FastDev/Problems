#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindrome(const string& s) {
    int l = 0;
    int r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

pair<string, int> divideStringByBase(const string& num, int base) {
    string result;
    int remainder = 0;
    for (char digit : num) {
        int current = remainder * 10 + (digit - '0');
        result += (current / base) + '0';
        remainder = current % base;
    }
    result.erase(0, result.find_first_not_of('0'));
    if (result.empty()) {
        result = "0";
    }
    return {result, remainder};
}

string convertToBase(const string& num, int base) {
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    string number = num;
    
    while (number != "0") {
        auto [next_number, remainder] = divideStringByBase(number, base);
        result += digits[remainder];
        number = next_number;
    }
    
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string n;
    cin >> n;

    bool found = false;
    for (int base = 2; base <= 10; ++base) {
        string representation = convertToBase(n, base);
        if (isPalindrome(representation)) {
            found = true;
            cout << base << " " << representation << endl;
        }
    }

    if (!found) {
        cout << "NIE" << endl;
    }

    return 0;
}

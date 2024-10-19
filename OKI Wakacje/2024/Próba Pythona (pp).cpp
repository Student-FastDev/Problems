#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    string input;
    getline(cin, input);

    vector<string> numbers;
    string current;
    
    for (char ch : input) {
        if (isdigit(ch) || ch == '.' || ch == '-' || ch == '_') {
            if (ch != '_') {
                current += ch;
            } else if (!current.empty()) {
                numbers.push_back(current);
                current.clear();
            }
        } else {
            if (!current.empty()) {
                numbers.push_back(current);
                current.clear();
            }
        }
    }
    if (!current.empty()) {
        numbers.push_back(current);
    }
    
    bool first = true;
    for (const string& num : numbers) {
        long long intValue;
        double doubleValue;
        bool isInteger = num.find('.') == string::npos;
        if (isInteger) {
            intValue = stoll(num);
            intValue += 1;
        } else {
            doubleValue = stod(num);
            doubleValue -= 1;
        }

        if (!first) {
            cout << "|";
        }
        first = false;

        stringstream ss;
        if (isInteger) {
            ss << showpos << fixed << setprecision(2) << static_cast<double>(intValue);
        } else {
            ss << showpos << fixed << setprecision(2) << doubleValue;
        }
        string formatted = ss.str();
        
        size_t pos = formatted.find('.');
        
        if (pos == string::npos) {
            pos = formatted.length();
        }
        
        if (pos < 4) {
            formatted.insert(1, 4 - pos, '0');
        }

        cout << formatted;
        if (!isInteger) {
            cout << "f";
        }
    }
    cout << endl;

    return 0;
}
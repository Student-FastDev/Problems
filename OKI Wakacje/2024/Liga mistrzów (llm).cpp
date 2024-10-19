#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string name;
    int goals, matches;

    cin >> name >> goals >> matches;

    double average = static_cast<double>(goals) / matches;

    stringstream ss;
    ss << fixed << setprecision(2) << average;

    string formatted_average = ss.str();

    if (formatted_average.find('.') != string::npos) {
        while (formatted_average.back() == '0') {
            formatted_average.pop_back();
        }
        if (formatted_average.back() == '.') {
            formatted_average.pop_back();
        }
    }

    cout << name << " strzela srednio " << formatted_average << " gola na mecz." << endl;

    return 0;
}
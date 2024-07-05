#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> jewelry(n);

    for(int i = 0; i < n; ++i) {
        cin >> jewelry[i];
    }

    sort(jewelry.begin(), jewelry.end(), [](const string &a, const string &b) {
        if (a.length() == b.length())
            return a < b;
        return a.length() < b.length();
    });

    for(const auto &item : jewelry) {
        cout << item << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> scores(n);
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
    }


    int max_score = *max_element(scores.begin(), scores.end());

    for (int i = 0; i < n; ++i) {
        if (scores[i] == max_score) {
            cout << char('A' + i);
        }
    }

    return 0;
}

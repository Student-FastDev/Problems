#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkNow(const vector<int>& candidate, const vector<pair<pair<int, int>, vector<int>>>& constraintsArray) {
    for (const auto& constraint : constraintsArray) {
        int A = 0, B = 0;
        const auto& target = constraint.second;

        for (int i = 0; i < candidate.size(); ++i) {
            if (candidate[i] == target[i]) {
                A += candidate[i];
            }
        }

        for (int i = 0; i < candidate.size(); ++i) {
            for (int j = 0; j < candidate.size(); ++j) {
                if (i != j && candidate[i] == target[j]) {
                    B += candidate[i];
                }
            }
        }

        if (A != constraint.first.first || B != constraint.first.second) {
            return false;
        }
    }

    return true;
}

int main() {
    int U;
    cin >> U;

    vector<pair<pair<int, int>, vector<int>>> constraintsArray;

    for (int i = 0; i < U; ++i) {
        int A, B;
        cin >> A >> B;

        vector<int> sequence(U);
        for (int j = 0; j < U; ++j) {
            cin >> sequence[j];
        }

        constraintsArray.push_back({{A, B}, sequence});
    }

    vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    do {
        vector<int> candidate(digits.begin(), digits.begin() + U);

        if (checkNow(candidate, constraintsArray)) {
            for (int i = 0; i < U; ++i) {
                cout << candidate[i] << " ";
            }
            cout << endl;
            return 0;
        }

    } while (next_permutation(digits.begin(), digits.end()));

    return 0;
}

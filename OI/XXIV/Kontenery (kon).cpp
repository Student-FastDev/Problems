#include <bits/stdc++.h>
using namespace std;

void processContainers(int numPositions, int numOperations, vector<tuple<int, int, int>>& operations) {
    int sqrtN = sqrt(numPositions) + 1;
    vector<int> ramp(numPositions, 0);
    vector<vector<int>> smallDiSums(sqrtN, vector<int>(numPositions + 1, 0));

    for (auto& operation : operations) {
        int A, L, D;
        tie(A, L, D) = operation;
        if (D >= sqrtN) {
            for (int i = 0; i < L; ++i) {
                int position = A - 1 + i * D;
                if (position < numPositions) {
                    ramp[position] += 1;
                }
            }
        } else {
            smallDiSums[D][A - 1] += 1;
            if (A - 1 + L * D < numPositions) {
                smallDiSums[D][A - 1 + L * D] -= 1;
            }
        }
    }

    for (int D = 1; D < sqrtN; ++D) {
        vector<int> tempRamp(numPositions, 0);
        for (int i = 0; i < numPositions; ++i) {
            if (i >= D) tempRamp[i] += tempRamp[i - D];
            tempRamp[i] += smallDiSums[D][i];
            ramp[i] += tempRamp[i];
        }
    }

    for (int i = 0; i < numPositions; ++i) {
        cout << ramp[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int numPositions, numOperations;
    cin >> numPositions >> numOperations;
    vector<tuple<int, int, int>> operations(numOperations);

    for (int i = 0; i < numOperations; ++i) {
        int A, L, D;
        cin >> A >> L >> D;
        operations[i] = make_tuple(A, L, D);
    }

    processContainers(numPositions, numOperations, operations);
    return 0;
}

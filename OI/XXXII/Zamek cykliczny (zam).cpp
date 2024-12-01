#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int checkVal = 15;

bool edgeCases(string S, int N) {
    if (S == "1") {
        cout << 0 << endl;
        return true;
    }

    bool isPowerOfTen = true;
    int oneCount = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] != '1' && S[i] != '0') {
            isPowerOfTen = false;
            break;
        }
        else if(S[i] == '1' && oneCount > 0) {
            isPowerOfTen = false;
            break;
        }
        else if(S[i] == '1') {
            oneCount++;
        }
    }

    if (isPowerOfTen) {
        cout << 1 << endl;
        return true;
    }

    return false;
}

int calculateFullMaxPoint(string S, int N) {
    for (int i = N - 1; i >= 0; i--) {
        if (S[i] != '9') {
            return i;
        }
    }
    return -1;
}

int calculateSteps(string S, int N) {
    int maxPoint = calculateFullMaxPoint(S, N);
    int stepsAmount = 0;

    for (int i = 0; i <= maxPoint; i++) {
        if (S[i] != '0') {
            stepsAmount += '9' - S[i];
            stepsAmount++;
        }
    }

    return stepsAmount + 2;
}

long long subtractStringsAsNumbers(string original, string modified) {
    long long originalValue = stoll(original);
    long long modifiedValue = stoll(modified);

    return modifiedValue - originalValue;
}

int main() {
    string S;
    cin >> S;

    int N = S.length();

    if (edgeCases(S, N)) {
        return 0;
    }

    int bestOption = 1e9;

    for (int i = 0; i < min(N, checkVal); i++) {
        string modifiedS = S;
        string lastPartModified = "";
        string lastPartNormal = "";

        for (int j = N-i-1; j < N; j++) {
            modifiedS[j] = '9';
            lastPartModified += modifiedS[j];
        }
        
        for (int j = N-i-1; j < N; j++) {
            lastPartNormal += S[j];
        }
        
        int stepsForModified = calculateSteps(modifiedS, N);
        long long differenceSum = subtractStringsAsNumbers(lastPartNormal, lastPartModified);

        int totalSteps = stepsForModified + differenceSum;
        
        if(totalSteps < 0) {
            continue;
        }

        bestOption = min(bestOption, totalSteps);
    }

    bestOption = min(bestOption, calculateSteps(S, N));
    cout << bestOption << endl;

    return 0;
}

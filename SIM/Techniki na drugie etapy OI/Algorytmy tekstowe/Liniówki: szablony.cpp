#include <bits/stdc++.h>
using namespace std;

inline int readS(char *a) {
    int length = 0;
    register char c = getchar_unlocked();
    while (c < 33) c = getchar_unlocked();
    while (c > 32) {
        a[length++] = c;
        c = getchar_unlocked();
    }
    a[length] = '\0';
    return length;
}

vector<int> computePrefixFunction(const string &S) {
    int N = S.size();
    vector<int> P(N, 0);
    int lengthValue = 0;
    int i = 1;
    while (i < N) {
        if (S[i] == S[lengthValue]) {
            lengthValue++;
            P[i] = lengthValue;
            i++;
        } else {
            if (lengthValue != 0) {
                lengthValue = P[lengthValue - 1];
            } else {
                P[i] = 0;
                i++;
            }
        }
    }
    return P;
}

vector<int> searchFunction(const string &patternValue, const string &textValue) {
    int N = textValue.length();
    int m = patternValue.length();
    vector<int> longestPrefix = computePrefixFunction(patternValue);
    vector<int> resultValue;

    int i = 0, j = 0;
    while (i < N) {
        if (textValue[i] == patternValue[j]) {
            i++;
            j++;
            if (j == m) {
                resultValue.push_back(i - j);
                j = longestPrefix[j - 1];
            }
        } else {
            if (j != 0) {
                j = longestPrefix[j - 1];
            } else {
                i++;
            }
        }
    }
    return resultValue;
}

bool isTemplateValid(const string &S, int lengthValue) {
    string patternValue = S.substr(0, lengthValue);
    vector<int> occurrencesArray = searchFunction(patternValue, S);
    int goodUpToIndex = -1;

    for (int pos : occurrencesArray) {
        if (pos > goodUpToIndex + 1) {
            return false;
        }
        goodUpToIndex = pos + lengthValue - 1;
    }

    return goodUpToIndex >= S.size() - 1;
}

int main() {
    char S[1000000];
    int len = readS(S);
    string str(S, len);

    vector<int> P = computePrefixFunction(str);
    int N = str.size();
    vector<int> candidates;
    int k = N;
    while (k > 0) {
        candidates.push_back(k);
        k = P[k - 1];
    }
    reverse(candidates.begin(), candidates.end());

    int lastChecked = 0;
    for (int lengthValue : candidates) {
        if (lengthValue < 2 * lastChecked) {
            continue;
        }
        if (isTemplateValid(str, lengthValue)) {
            printf("%d\n", lengthValue);
            return 0;
        }
        lastChecked = lengthValue;
    }
    printf("%d\n", N);
    return 0;
}

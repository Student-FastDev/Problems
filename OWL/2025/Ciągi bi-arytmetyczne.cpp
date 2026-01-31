#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

bool check(vector<int> valuesArray, int nodeValue) {
    valuesArray.push_back(nodeValue);
    sort(valuesArray.begin(), valuesArray.end());

    bool isPossible = true;
    int lastDifference = valuesArray[1] - valuesArray[0];

    for (int i = 2; i < valuesArray.size(); i++) {
        if (valuesArray[i] - valuesArray[i - 1] != lastDifference) {
            isPossible = false;
            break;
        }
    }

    return isPossible;
}

bool solve(vector<int>& valuesArray, int N) {
    int firstDifference = -1;
    int nodeValue = valuesArray[0];

    firstDifference = valuesArray[1] - valuesArray[0];

    vector<int> arithmeticFirst;
    vector<int> arithmeticSecond;

    vector<int> arithmeticFirstFixed;
    vector<int> arithmeticSecondFixed;

    int searchValue = nodeValue + firstDifference;
    for (int i = 1; i < N; i++) {
        if (valuesArray[i] == searchValue) {
            arithmeticFirst.push_back(valuesArray[i]);
            searchValue += firstDifference;
        } else {
            arithmeticSecond.push_back(valuesArray[i]);
        }
    }

    reverse(arithmeticFirst.begin(), arithmeticFirst.end());
    int doNotAdd = !arithmeticFirst.empty() ? arithmeticFirst[0] : -1;

    searchValue = nodeValue + firstDifference;
    for (int i = 1; i < N; i++) {
        if (valuesArray[i] == searchValue && valuesArray[i] != doNotAdd) {
            arithmeticFirstFixed.push_back(valuesArray[i]);
            searchValue += firstDifference;
        } else {
            arithmeticSecondFixed.push_back(valuesArray[i]);
        }
    }

    reverse(arithmeticFirstFixed.begin(), arithmeticFirstFixed.end());
    bool isGood = check(arithmeticSecond, nodeValue);
    bool isGoodFixed = check(arithmeticSecondFixed, nodeValue);

    if (isGood) {
        cout << "TAK\n";
        for (int i = 0; i < arithmeticFirst.size(); i++) cout << arithmeticFirst[i] << " ";
        cout << nodeValue << " ";
        for (int i = 0; i < arithmeticSecond.size(); i++) cout << arithmeticSecond[i] << " ";
        cout << "\n";
    } else if (isGoodFixed) {
        cout << "TAK\n";
        for (int i = 0; i < arithmeticFirstFixed.size(); i++) cout << arithmeticFirstFixed[i] << " ";
        cout << nodeValue << " ";
        for (int i = 0; i < arithmeticSecondFixed.size(); i++) cout << arithmeticSecondFixed[i] << " ";
        cout << "\n";
    }

    return isGood || isGoodFixed;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<int> numberArray;
    for (int i = 0; i < N; i++) {
        int tempValue;
        cin >> tempValue;
        numberArray.push_back(tempValue);
    }

    sort(numberArray.begin(), numberArray.end());

    int lastDifference = -1;
    int differenceNumber = 0;
    for (int i = 1; i < N; i++) {
        int currentDifference = abs(numberArray[i] - numberArray[i - 1]);
        if (currentDifference != lastDifference) {
            lastDifference = currentDifference;
            differenceNumber++;
        }
    }

    if (differenceNumber <= 2) {
        cout << "TAK\n";
        for (int i = 0; i < N; i++) {
            cout << numberArray[i] << " ";
        }
        cout << "\n";
        return;
    }

    if (solve(numberArray, N)) {
        return;
    }

    reverse(numberArray.begin(), numberArray.end());
    if (solve(numberArray, N)) {
        return;
    } else {
        cout << "NIE\n";
    }
}

int main() {
    cin.tie()->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
}

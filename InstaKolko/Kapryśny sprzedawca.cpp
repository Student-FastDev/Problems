#include <iostream>
#include <deque>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    deque<int> queArray;
    for (int i = 1; i <= N; ++i) {
        queArray.push_back(i);
    }

    vector<int> numberArray;

    bool sendToBack = false;
    while (!queArray.empty()) {
        if (sendToBack) {
            int person = queArray.front();
            queArray.pop_front();
            queArray.push_back(person);
        } else {
            numberArray.push_back(queArray.front());
            queArray.pop_front();
        }
        sendToBack = !sendToBack;
    }

    for (int i = 0; i < numberArray.size(); ++i) {
        cout << numberArray[i] << " ";
    }

    return 0;
}

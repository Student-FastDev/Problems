#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    vector<int> sequenceArray(N);

    for (int i = 0; i < N; ++i) {
        cin >> sequenceArray[i];
    }

    int candidateMen = -1, count = 0;

    for (int num : sequenceArray) {
        if (count == 0) {
            candidateMen = num;
            count = 1;
        } else if (num == candidateMen) {
            count++;
        } else {
            count--;
        }
    }

    count = 0;
    for (int num : sequenceArray) {
        if (num == candidateMen) {
            count++;
        }
    }

    if (count > N / 2) {
        cout << candidateMen << endl;
    } else {
        cout << "xd" << endl;
    }

    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    double sum = 0;
    double sumWeights = 0;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        sum += a * b;
        sumWeights += b;
    }

    double average = sum / sumWeights;

    if (average >= 4.75) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }

    return 0;
}
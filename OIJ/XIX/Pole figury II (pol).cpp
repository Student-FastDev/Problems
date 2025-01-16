#include <bits/stdc++.h>
using namespace std;

void calculateCoordinates(const string& direction, vector<int>& x, vector<int>& y) {
    int tempX = 0, tempY = 0;
    x.push_back(tempX);
    y.push_back(tempY);

    for (char move : direction) {
        if (move == 'P') tempX++;
        if (move == 'L') tempX--;
        if (move == 'G') tempY++;
        if (move == 'D') tempY--;
        x.push_back(tempX);
        y.push_back(tempY);
    }

    x.push_back(x[0]);
    y.push_back(y[0]);
}

long long calculateArea(const vector<int>& x, const vector<int>& y) {
    long long sumValue = 0;
    int n = x.size();

    for (int i = 0; i < n - 1; i++) {
        sumValue += x[i] * y[i + 1] - y[i] * x[i + 1];
    }

    return abs(sumValue) / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string direction;
    cin >> direction;

    vector<int> x, y;
    calculateCoordinates(direction, x, y);
    
    cout << calculateArea(x, y) << "\n";

    return 0;
}

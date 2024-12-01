#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

double getAngle(int rX, int rY, int X, int Y) {
    return atan2(Y - rY, X - rX);
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int rX, rY, N, M;
        cin >> rX >> rY >> N >> M;

        unordered_map<double, int> angleCount;
        for (int i = 0; i < M; ++i) {
            int X, Y;
            cin >> X >> Y;
            double angle = getAngle(rX, rY, X, Y);
            angleCount[angle]++;
        }

        vector<int> countsArray;
        for (const auto& [angle, count] : angleCount) {
            countsArray.push_back(count);
        }

        sort(countsArray.rbegin(), countsArray.rend());

        int maxExhibits = 0;
        for (int i = 0; i < min(N, (int)countsArray.size()); ++i) {
            maxExhibits += countsArray[i];
        }

        cout << maxExhibits << endl;
    }

    return 0;
}

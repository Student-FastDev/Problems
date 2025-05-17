#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int X, Y;
};

bool canCoverKPoints(int side, int K, const vector<Point>& points) {
    int N = points.size();

    vector<Point> sortedPoints = points;
    sort(sortedPoints.begin(), sortedPoints.end(), [](const Point& a, const Point& b) {
        return a.X < b.X;
    });

    for (int i = 0; i < N; ++i) {
        int xMin = sortedPoints[i].X;
        int xMax = xMin + side;

        vector<int> y_values;
        for (int j = i; j < N && sortedPoints[j].X <= xMax; ++j) {
            y_values.push_back(sortedPoints[j].Y);
        }

        sort(y_values.begin(), y_values.end());
        for (int j = 0, k = 0; j < y_values.size(); ++j) {
            while (k < y_values.size() && y_values[k] <= y_values[j] + side) {
                k++;
            }
            if (k - j >= K) return true;
        }
    }
    return false;
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<Point> points(N);

    for (int i = 0; i < N; ++i) {
        cin >> points[i].X >> points[i].Y;
    }

    int left = 0, right = 1e9, result = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (canCoverKPoints(mid, K, points)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << result << endl;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

struct Point {

  long long x, y, z;

  double distance;

  Point(long long x, long long y, long long z) : x(x), y(y), z(z) {

    distance = sqrt(x * x + y * y + z * z);
  }
};

bool comparePoints(const Point &a, const Point &b) {

  return a.distance < b.distance;
}

int main() {

  long long t;

  cin >> t;

  vector points;

  for (long long i = 0; i < t; ++i) {

    long long x, y, z;

    cin >> x >> y >> z;

    points.push_back(Point(x, y, z));
  }

  sort(points.begin(), points.end(), comparePoints);

  for (const auto &point : points) {

    cout << point.x << " " << point.y << " " << point.z << endl;
  }

  return 0;
}
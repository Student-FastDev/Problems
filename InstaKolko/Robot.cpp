#include <bits/stdc++.h>

using namespace std;

struct Point {

  long long x, y;
};

string determineTurn(const Point &A, const Point &B, const Point &C) {

  long long dx1 = B.x - A.x;

  long long dy1 = B.y - A.y;

  long long dx2 = C.x - B.x;

  long long dy2 = C.y - B.y;

  long long crossProduct = dx1 * dy2 - dy1 * dx2;

  if (crossProduct > 0) {

    return "L";

  } else if (crossProduct < 0) {

    return "P";

  } else {

    return "C";
  }
}

int main() {

  int n;

  cin >> n;

  vector points(n);

  for (int i = 0; i < n; ++i) {

    cin >> points[i].x >> points[i].y;
  }

  for (int i = 1; i < n - 1; ++i) {

    cout << determineTurn(points[i - 1], points[i], points[i + 1]) << endl;
  }

  return 0;
}
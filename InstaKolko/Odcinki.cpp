#include <bits/stdc++.h>

using namespace std;

struct Point {

  long long x, y;
};

int orientation(Point p, Point q, Point r) {

  long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (val == 0)
    return 0;

  return (val > 0) ? 1 : 2;
}

bool onSegment(Point p, Point q, Point r) {

  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&

      q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))

    return true;

  return false;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {

  int o1 = orientation(p1, q1, p2);

  int o2 = orientation(p1, q1, q2);

  int o3 = orientation(p2, q2, p1);

  int o4 = orientation(p2, q2, q1);

  if (o1 != o2 && o3 != o4)

    return true;

  if (o1 == 0 && onSegment(p1, p2, q1))
    return true;

  if (o2 == 0 && onSegment(p1, q2, q1))
    return true;

  if (o3 == 0 && onSegment(p2, p1, q2))
    return true;

  if (o4 == 0 && onSegment(p2, q1, q2))
    return true;

  return false;
}

int main() {

  int t;

  cin >> t;

  for (int i = 0; i < t; i++) {

    Point p0, p1, p2, p3;

    cin >> p0.x >> p0.y >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

    if (doIntersect(p0, p1, p2, p3)) {

      cout << "TAK" << endl;

    } else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}
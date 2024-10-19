#include <bits/stdc++.h>

using namespace std;

struct Point {

  int x, y;
};

bool areCollinear(Point A, Point B, Point C) {

  return (B.x - A.x) * (C.y - A.y) == (B.y - A.y) * (C.x - A.x);
}

int main() {

  int t;

  cin >> t;

  for (int i = 0; i < t; i++) {

    Point A, B, C;

    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;

    if (areCollinear(A, B, C)) {

      cout << "TAK" << endl;

    } else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}
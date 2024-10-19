#include <bits/stdc++.h>

using namespace std;

struct Point {

  double x, y;
};

int main() {

  Point A, B;

  cin >> A.x >> A.y >> B.x >> B.y;

  Point middle;

  middle.x = (A.x + B.x) / 2.0;

  middle.y = (A.y + B.y) / 2.0;

  cout << fixed << setprecision(2);

  cout << middle.x << " " << middle.y << endl;

  return 0;
}
#include <bits/stdc++.h>

using namespace std;

struct fourElements {

  int x, y, z, w;

  fourElements(int _x, int _y, int _z, int _w) {

    x = _x;

    y = _y;

    z = _z;

    w = _w;
  }
};

void pairSort(vector &vectors) {

  int n = vectors.size();

  for (int gap = n / 2; gap > 0; gap /= 2) {

    for (int i = gap; i < n; i++) {

      fourElements temp = vectors[i];

      int j;

      for (j = i;
           j >= gap &&
           (vectors[j - gap].x > temp.x ||
            (vectors[j - gap].x == temp.x && vectors[j - gap].y > temp.y) ||
            (vectors[j - gap].x == temp.x && vectors[j - gap].y == temp.y &&
             vectors[j - gap].z > temp.z) ||
            (vectors[j - gap].x == temp.x && vectors[j - gap].y == temp.y &&
             vectors[j - gap].z == temp.z && vectors[j - gap].w > temp.w));
           j -= gap) {

        vectors[j] = vectors[j - gap];
      }

      vectors[j] = temp;
    }
  }
}

int main() {

  int n;

  cin >> n;

  vector vectors;

  for (int i = 0; i < n; i++) {

    int x, y, z, w;

    cin >> x >> y >> z >> w;

    vectors.push_back(fourElements(x, y, z, w));
  }

  pairSort(vectors);

  for (const auto &vec : vectors) {

    cout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << endl;
  }

  return 0;
}
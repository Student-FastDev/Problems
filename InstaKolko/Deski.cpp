#include <bits/stdc++.h>

using namespace std;

struct boardStructure {

  int a, b;
};

bool checkIfAllBoardsDown(const vector &boardArray, const vector &nailArray,
                          int lastNailIndex, vector &coverage) {

  fill(coverage.begin(), coverage.end(), 0);

  for (int i = 0; i <= lastNailIndex; ++i) {

    coverage[nailArray[i]] = 1;
  }

  for (int i = 1; i < coverage.size(); ++i) {

    coverage[i] += coverage[i - 1];
  }

  for (const auto &board : boardArray) {

    if (coverage[board.b] - (board.a > 0 ? coverage[board.a - 1] : 0) == 0) {

      return false;
    }
  }

  return true;
}

int main() {

  ios_base::sync_with_stdio(0);

  cin.tie(0);

  cout.tie(0);

  int N, M;

  cin >> N >> M;

  vector boardArray(N);

  int maxPosition = 0;

  for (int i = 0; i < N; ++i) {

    cin >> boardArray[i].a >> boardArray[i].b;

    maxPosition = max(maxPosition, boardArray[i].b);
  }

  vector nailArray(M);

  for (int i = 0; i < M; ++i) {

    cin >> nailArray[i];

    maxPosition = max(maxPosition, nailArray[i]);
  }

  vector coverage(maxPosition + 1, 0);

  int left = 0, right = M - 1, result = -1;

  while (left <= right) {

    int middle = (left + right) / 2;

    if (checkIfAllBoardsDown(boardArray, nailArray, middle, coverage)) {

      result = middle + 1;

      right = middle - 1;

    } else {

      left = middle + 1;
    }
  }

  cout << result << endl;

  return 0;
}
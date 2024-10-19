#include <bits/stdc++.h>

using namespace std;

void performSwap(vector &positions, char move) {

  switch (move) {

  case 'A':
    swap(positions[0], positions[1]);
    break;

  case 'B':
    swap(positions[0], positions[2]);
    break;

  case 'C':
    swap(positions[0], positions[3]);
    break;

  case 'D':
    swap(positions[0], positions[4]);
    break;

  case 'E':
    swap(positions[1], positions[2]);
    break;

  case 'F':
    swap(positions[1], positions[3]);
    break;

  case 'G':
    swap(positions[1], positions[4]);
    break;

  case 'H':
    swap(positions[2], positions[3]);
    break;

  case 'I':
    swap(positions[2], positions[4]);
    break;

  case 'J':
    swap(positions[3], positions[4]);
    break;
  }
}

int main() {

  int N;

  cin >> N;

  vector > moves(N);

  for (int i = 0; i < N; ++i) {

    char moveType;

    long long repetitions;

    cin >> moveType >> repetitions;

    moves[i] = make_pair(moveType, repetitions);
  }

  vector positions = {1, 2, 3, 4, 5};

  for (const auto &move : moves) {

    char moveType = move.first;

    long long repetitions = move.second;

    for (long long i = 0; i < repetitions % 2; ++i) {

      performSwap(positions, moveType);
    }
  }

  for (int i = 0; i < 5; ++i) {

    if (positions[i] == 1) {

      cout << (i + 1) << endl;

      break;
    }
  }

  return 0;
}
#include <bits/stdc++.h>

using namespace std;

long long collatzProblem(long long N, int score) {

  if (N == 1) {

    return score;
  }

  if (N % 2 == 0) {

    return collatzProblem(N / 2, score + 1);

  }

  else {

    return collatzProblem((N * 3) + 1, score + 1);
  }

  return 0;
}

int main() {

  long long N;

  cin >> N;

  cout << collatzProblem(N, 0);

  return 0;
}
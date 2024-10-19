#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

vector neighbourList[MAX_N];

bool visitedList[MAX_N];

void dfs(int W) {

  visitedList[W] = true;

  for (auto i : neighbourList[W]) {

    if (!visitedList[i]) {

      dfs(i);
    }
  }
}

int main()

{

  int N;

  cin >> N;

  for (int i = 0; i < N; i++) {

    int A;

    cin >> A;

    for (int j = 0; j < A; j++) {

      int B;

      cin >> B;

      neighbourList[i].push_back(B);
    }
  }

  dfs(0);

  bool isTrue = true;

  for (int i = 0; i < N; i++) {

    if (visitedList[i] == false) {

      isTrue = false;

      break;
    }
  }

  if (isTrue) {

    cout << "SPOJNY" << endl;

  }

  else {

    cout << "NIE" << endl;
  }

  return 0;
}
#include <bits/stdc++.h>

using namespace std;

int main() {
  int N;
  string S;
  cin >> N >> S;

  int rmIndex = -1;

  for (int i = 0; i < N - 1; i++) {
    if (S[i + 1] < S[i]) {
      if (rmIndex == -1) {
        rmIndex = i;
      }
    }
  }

  if (rmIndex == -1) {
    rmIndex = N - 1;
  }

  string outputText = "";

  for (int i = 0; i < N; i++) {
    if (i != rmIndex) {
      outputText += S[i];
    }
  }

  cout << outputText << endl;

  return 0;
}
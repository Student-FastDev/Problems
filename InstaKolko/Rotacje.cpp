#include <bits/stdc++.h>

using namespace std;

int main() {
  string S;
  long long N;

  cin >> S >> N;

  N = N % S.length();

  string endString = "";
  string startString = "";

  for (int i = 0; i < N; i++) {
    startString += S[i];
  }

  for (int i = N; i < S.length(); i++) {
    endString += S[i];
  }

  cout << endString + startString << endl;

  return 0;
}
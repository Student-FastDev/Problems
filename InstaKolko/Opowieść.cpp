#include <bits/stdc++.h>

using namespace std;

bool countArray[256];

int main()

{

  int N;

  string S;

  cin >> N >> S;

  int countSentence = 0;

  for (int i = 0; i < N; i++) {

    if (S[i] >= 'A' && S[i] <= 'Z') {

      countArray[S[i]] = true;

      if (countArray[S[i] + 32] == true) {

        countSentence++;
      }

    }

    else if (S[i] >= 'a' && S[i] <= 'z') {

      countArray[S[i]] = true;

      if (countArray[S[i] - 32] == true) {

        countSentence++;
      }
    }
  }

  cout << countSentence << endl;

  return 0;
}
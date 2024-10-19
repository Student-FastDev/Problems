#include <bits/stdc++.h>

using namespace std;

bool checkBooks(long long Q, long long N, long long booksArray[], long long K) {

  long long compAmount = 1;

  long long booksSum = 0;

  for (long long i = 0; i < N; i++) {

    if (booksArray[i] > Q) {

      return false;
    }

    if (booksSum + booksArray[i] <= Q) {

      booksSum += booksArray[i];

    } else {

      compAmount++;

      booksSum = booksArray[i];
    }
  }

  return compAmount <= K;
}

int main() {

  long long Z;

  cin >> Z;

  for (long long i = 0; i < Z; i++) {

    long long N, K;

    cin >> N >> K;

    long long booksArray[N];

    long long booksSum = 0;

    long long maxBookWeight = 0;

    for (long long i = 0; i < N; i++) {

      cin >> booksArray[i];

      booksSum += booksArray[i];

      if (booksArray[i] > maxBookWeight) {

        maxBookWeight = booksArray[i];
      }
    }

    long long start = maxBookWeight;

    long long end = booksSum;

    long long result = -1;

    while (start <= end) {

      long long middle = (start + end) / 2;

      if (checkBooks(middle, N, booksArray, K)) {

        result = middle;

        end = middle - 1;

      } else {

        start = middle + 1;
      }
    }

    cout << result << endl;
  }

  return 0;
}
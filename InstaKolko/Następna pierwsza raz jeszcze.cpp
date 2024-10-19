#include <bits/stdc++.h>

using namespace std;

const int MAX_NUM = 2000000;

bool primeNumbers[MAX_NUM];

int higherPrime[MAX_NUM];

int main()

{

  for (int i = 2; i * i < MAX_NUM; i++) {

    if (!primeNumbers[i]) {

      for (int j = i * i; j < MAX_NUM; j += i) {

        primeNumbers[j] = true;
      }
    }
  }

  int higherPrimeNumber = MAX_NUM;

  for (int i = MAX_NUM - 1; i >= 1; i--) {

    if (primeNumbers[i]) {

      higherPrime[i] = higherPrimeNumber;

    }

    else {

      higherPrime[i] = higherPrimeNumber;

      higherPrimeNumber = i;
    }
  }

  int N;

  cin >> N;

  for (int i = 0; i < N; i++) {

    int a;

    cin >> a;

    cout << higherPrime[a] << endl;
  }

  return 0;
}
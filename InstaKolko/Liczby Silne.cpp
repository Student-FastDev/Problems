#include <bits/stdc++.h>

using namespace std;

// Obliczanie silni.

unsigned long long factorial(long long n) {

  if (n == 0 || n == 1) {

    return 1;
  }

  unsigned long long result = 1;

  for (long long i = 2; i <= n; ++i) {

    result *= i;
  }

  return result;
}

// Rekurencyjne obliczanie sum silni.

void findStrongNumbers(long long index, unsigned long long currentSum,
                       vector &factorials, vector &strongNumbers,
                       unsigned long long maxValue) {

  // Wieksze niz 15! - maxValue

  if (currentSum > maxValue) {

    return;
  }

  strongNumbers.push_back(currentSum);

  // Dalsze rekurencje...

  for (long long i = index; i < factorials.size(); ++i) {

    findStrongNumbers(i + 1, currentSum + factorials[i], factorials,
                      strongNumbers, maxValue);
  }
}

int main() {

  // Obliczanie silni do 14. - Silnia z 15 jest poza naszym limitem (15! >
  // 10**13)

  vector factorials;

  for (long long i = 1; i <= 14; ++i) {

    factorials.push_back(factorial(i));
  }

  unsigned long long maxValue = factorials.back();

  vector strongNumbers;

  findStrongNumbers(0, 0, factorials, strongNumbers, maxValue);

  // Musimy posortowac, nie wiemy w jakiej kolejnosci.

  sort(strongNumbers.begin(), strongNumbers.end());

  long long N;

  cin >> N;

  // Binary Search dla kazdego zapytania po naszym preprocesie.

  for (long long i = 0; i < N; i++) {

    long long A, B;

    cin >> A >> B;

    long long start = 0;

    long long end = strongNumbers.size() - 1;

    long long result = -1;

    while (start <= end) {

      long long middle = (start + end) / 2;

      if (strongNumbers[middle] >= A) {

        result = middle;

        end = middle - 1;

      }

      else {

        start = middle + 1;
      }
    }

    // Nie ma takiej.

    if (strongNumbers[result] > B) {

      cout << 0 << endl;

      continue;

    }

    // Obliczanie sumy.

    else {

      long long sumNum = 0;

      for (long long j = result; strongNumbers[j] <= B; j++) {

        sumNum += strongNumbers[j];
      }

      // Wynik.

      cout << sumNum << endl;

      continue;
    }
  }

  return 0;
}
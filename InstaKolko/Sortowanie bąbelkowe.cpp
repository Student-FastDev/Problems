#include <bits/stdc++.h>

using namespace std;

void bubbleSort(long long arr[], long long size) {

  for (long long i = 0; i < size - 1; i++) {

    for (long long j = 0; j < size - i - 1; j++) {

      if (arr[j] > arr[j + 1]) {

        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

int main() {

  long long N;

  cin >> N;

  long long numbers[N];

  for (long long i = 0; i < N; i++) {

    cin >> numbers[i];
  }

  bubbleSort(numbers, N);

  for (long long i = 0; i < N; i++) {

    cout << numbers[i] << " ";
  }

  return 0;
}
#include <bits/stdc++.h>

using namespace std;

mt19937 rng(static_cast(time(0)));

void quicksort(vector &arr, long long left, long long right) {

  if (left >= right)
    return;

  uniform_int_distribution dist(left, right);

  long long pivotIndex = dist(rng);

  long long pivot = arr[pivotIndex];

  long long i = left, j = left, k = right;

  while (j <= k) {

    if (arr[j] < pivot) {

      swap(arr[i], arr[j]);

      i++;

      j++;

    } else if (arr[j] > pivot) {

      swap(arr[j], arr[k]);

      k--;

    } else {

      j++;
    }
  }

  quicksort(arr, left, i - 1);

  quicksort(arr, k + 1, right);
}

int main() {

  ios_base::sync_with_stdio(0);

  cin.tie(0);

  cout.tie(0);

  long long N;

  cin >> N;

  vector numberArray(N);

  for (long long i = 0; i < N; i++) {

    cin >> numberArray[i];
  }

  quicksort(numberArray, 0, N - 1);

  for (long long num : numberArray) {

    cout << num << " ";
  }

  cout << endl;

  return 0;
}
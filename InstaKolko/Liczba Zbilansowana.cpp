#include <bits/stdc++.h>

using namespace std;

int findSmallestBalancedNumber(int n, vector &sequence) {

  sort(sequence.begin(), sequence.end());

  unordered_map odd_count;

  unordered_map even_count;

  for (int num : sequence) {

    if (num % 2 == 0) {

      even_count[num]++;

    } else {

      odd_count[num]++;
    }
  }

  vector unique_sequence(sequence.begin(), sequence.end());

  unique_sequence.erase(unique(unique_sequence.begin(), unique_sequence.end()),
                        unique_sequence.end());

  for (size_t i = 1; i < unique_sequence.size(); ++i) {

    odd_count[unique_sequence[i]] += odd_count[unique_sequence[i - 1]];

    even_count[unique_sequence[i]] += even_count[unique_sequence[i - 1]];
  }

  int min_diff = INT_MAX;

  int smallest_balanced_number = -1;

  for (int num : sequence) {

    int diff = abs(odd_count[num] - even_count[num]);

    if (diff < min_diff ||
        (diff == min_diff && num < smallest_balanced_number)) {

      min_diff = diff;

      smallest_balanced_number = num;
    }
  }

  return smallest_balanced_number;
}

int main() {

  int n;

  cin >> n;

  vector sequence(n);

  for (int i = 0; i < n; ++i) {

    cin >> sequence[i];
  }

  cout << findSmallestBalancedNumber(n, sequence) << endl;

  return 0;
}
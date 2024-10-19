#include <bits/stdc++.h>

using namespace std;

int main() {

  string poem;

  cin >> poem;

  int q;

  cin >> q;

  vector > queries(q);

  for (int i = 0; i < q; ++i) {

    int a, b;

    cin >> a >> b;

    queries[i] = {a - 1, b - 1};
  }

  int n = poem.size();

  vector > prefix_counts(26, vector(n + 1, 0));

  for (int i = 0; i < n; ++i) {

    int char_index = poem[i] - 'a';

    for (int j = 0; j < 26; ++j) {

      prefix_counts[j][i + 1] = prefix_counts[j][i];
    }

    prefix_counts[char_index][i + 1] += 1;
  }

  string result;

  for (const auto &query : queries) {

    int a = query.first;

    int b = query.second;

    int max_count = 0;

    char max_char = 'a';

    for (int j = 0; j < 26; ++j) {

      int count = prefix_counts[j][b + 1] - prefix_counts[j][a];

      if (count > max_count) {

        max_count = count;

        max_char = 'a' + j;

      } else if (count == max_count && 'a' + j < max_char) {

        max_char = 'a' + j;
      }
    }

    result += max_char;
  }

  cout << result << endl;

  return 0;
}
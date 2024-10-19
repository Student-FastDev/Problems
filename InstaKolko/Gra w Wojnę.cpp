#include <bits/stdc++.h>

using namespace std;

int main() {

  int N, M;

  cin >> N >> M;

  queue firstCards;

  queue secondCards;

  for (int i = 0; i < N; ++i) {

    int card;

    cin >> card;

    firstCards.push(card);
  }

  for (int i = 0; i < M; ++i) {

    int card;

    cin >> card;

    secondCards.push(card);
  }

  stack warFirst;

  stack warSecond;

  while (!firstCards.empty() && !secondCards.empty()) {

    if (firstCards.front() > secondCards.front()) {

      warFirst.push(firstCards.front());

      warSecond.push(secondCards.front());

      firstCards.pop();

      secondCards.pop();

      while (!warFirst.empty()) {

        firstCards.push(warFirst.top());

        warFirst.pop();
      }

      while (!warSecond.empty()) {

        firstCards.push(warSecond.top());

        warSecond.pop();
      }

    }

    else if (firstCards.front() < secondCards.front()) {

      warFirst.push(firstCards.front());

      warSecond.push(secondCards.front());

      firstCards.pop();

      secondCards.pop();

      while (!warSecond.empty()) {

        secondCards.push(warSecond.top());

        warSecond.pop();
      }

      while (!warFirst.empty()) {

        secondCards.push(warFirst.top());

        warFirst.pop();
      }

    }

    else {

      warFirst.push(firstCards.front());

      warSecond.push(secondCards.front());

      firstCards.pop();

      secondCards.pop();

      if (firstCards.empty() || secondCards.empty()) {

        break;
      }

      warFirst.push(firstCards.front());

      warSecond.push(secondCards.front());

      firstCards.pop();

      secondCards.pop();
    }
  }

  if (firstCards.empty() && secondCards.empty()) {

    cout << "remis" << endl;

  } else if (secondCards.empty()) {

    cout << "Bitosia" << endl;

  } else {

    cout << "Bitek" << endl;
  }

  return 0;
}
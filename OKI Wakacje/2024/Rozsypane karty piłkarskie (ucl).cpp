#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Card {
    string club;
    int number;
    string name;
    string country;
};

bool compareCards(const Card &a, const Card &b) {
    if (a.club != b.club)
        return a.club < b.club;
    if (a.country != b.country)
        return a.country < b.country;
    return a.name < b.name;
}

int main() {
    int n;
    cin >> n;

    vector<Card> cards(n);

    for (int i = 0; i < n; ++i) {
        cin >> cards[i].club >> cards[i].number >> cards[i].name >> cards[i].country;
    }

    sort(cards.begin(), cards.end(), compareCards);

    for (int i = 0; i < n; ++i) {
        cout << cards[i].club << " " << cards[i].number << " " << cards[i].name << " " << cards[i].country << endl;
    }

    return 0;
}
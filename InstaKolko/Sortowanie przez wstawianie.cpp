#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numCards;
    cin >> numCards;
    
    vector<long long> cards(numCards);
    for (int i = 0; i < numCards; i++) {
        cin >> cards[i];
    }
    
    for (int i = 1; i < numCards; i++) {
        long long key = cards[i];
        int j = i - 1;

        while (j >= 0 && cards[j] > key) {
            cards[j + 1] = cards[j];
            j--;
        }
        cards[j + 1] = key;
    }
    
    for (int i = 0; i < numCards; i++) {
        cout << cards[i] << " ";
    }
    cout << endl;

    return 0;
}

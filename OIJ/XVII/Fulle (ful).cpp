#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    string S;
    cin >> S;
    
    unordered_map<char, int> cardMap;
    
    int doubleCard = 0;
    int tripleCard = 0;
    int quadraCard = 0;
    for(int i = 0; i < S.length(); i++) {
        cardMap[S[i]]++;
        if(cardMap[S[i]] == 2) {
            doubleCard++;
        }
        else if (cardMap[S[i]] == 3) {
            doubleCard--;
            tripleCard++;
        }
        else if (cardMap[S[i]] == 4) {
            tripleCard--;
            quadraCard++;
        }
    }
    
    int maxFull = 0;
    
    for(int i = 0; i <= tripleCard; i++) {
        for(int j = 0; j <= quadraCard; j++) {
            maxFull = max(maxFull, min(doubleCard + tripleCard - i + 2 * (quadraCard - j), i + j));
        }
    }
    
    cout << maxFull;
    
}

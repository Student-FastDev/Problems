#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string S, K;
    cin >> S >> K;

    long long requiredLenght;
    if(K.length() % 2 == 0) {
        requiredLenght = K.length()/2;
    }
    else {
        requiredLenght = K.length()/2+1;
    }

    unordered_map<char,long long> limitCharacters;
    for(long long i = 0; i < K.length(); i++) {
        limitCharacters[K[i]]++;
    }

    unordered_map<char,long long> currentCharacters;
    long long left = 0;
    long long finalScore = 0;
    for(long long right = 0; right < S.length(); right++) {
        currentCharacters[S[right]]++;
        while(currentCharacters[S[right]] > limitCharacters[S[right]]) {
            currentCharacters[S[left]]--;
            left++;
        }
        if(right - left + 1 < requiredLenght) {
            continue;
        }
        finalScore += ((right-left+1) - requiredLenght) + 1;
    }

    cout << finalScore;

    return 0;
}

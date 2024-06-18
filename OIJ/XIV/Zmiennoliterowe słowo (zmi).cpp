#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    string S;
    cin >> S;
    
    int changeAmount = 0;
    char lastCharacter = S[0];
    for(int i = 1; i < S.length(); i++) {
        if(S[i] == lastCharacter) {
            changeAmount++;
        }
        lastCharacter = S[i];
    }
    
    cout << changeAmount;

    return 0;
}
